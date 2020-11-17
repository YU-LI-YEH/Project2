#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;
template <class T> class stack;
template <class T> class queue;
class FCR;

template <class T>
class link {
    friend class stack <T>;
    friend class queue <T>;
    friend class FCR;
    public:
        link(T& x) : value(x), next(nullptr){}
        ~link(){}
    private:
        T value;
        link <T> *next;
};

class adjnode {
    friend class FCR;
    public:
        adjnode() : r(0), c(0){}
        adjnode(int rr, int cc) : r(rr), c(cc){}
        ~adjnode(){}
    private:
        int r, c;
};

template <class T>
class stack{
    friend class FCR;
    public:
        stack() : topp(nullptr), my_size(0){}
        ~stack(){}
        void push(T& n){
            link <T> *tmp = new link <T>(n);
            if (empty()){
                topp = tmp;
            }
            else {
                tmp->next = topp;
                topp = tmp;
            }
            my_size++;
        }
        void pop(){
            if (empty())
                return;
            link <T> *deletenode = topp;
            topp = topp->next;
            delete deletenode;
            my_size--;
        }
        bool empty(){
            return topp == nullptr;
        }
        T& top(){
            return topp->value;
        }
        int size(){
            return my_size;
        }
        void clean(){
            if (empty())
                return;
            link <adjnode> *newtop;
            while (!empty()){
                newtop = topp->next;
                delete topp;
                topp = newtop;
            }
            my_size = 0;
        }
    private:
        link <T> *topp;
        int my_size;
};

template <class T>
class queue{
    friend class FCR;
    public:
        queue() : first(nullptr), last(nullptr), my_size(0){}
        ~queue(){}
        void push (T& n){
            link <T> *tmp = new link <T> (n);
            if (empty()){
                first = tmp;
                last = tmp;
            }
            else {
                last->next = tmp;
                last = tmp;
            }
            my_size++;
        }
        void pop (){
            if (empty())
                return;
            link <T> *deletenode = first;
            first = first->next;
            delete deletenode;
            my_size--;
        }
        bool empty (){
            return first == nullptr;
        }
        T& front(){
            return first->value;
        }
        int size(){
            return my_size;
        }
    private:
        link <T> *first;
        link <T> *last;
        int my_size;
};

class ElementNode{
    friend class FCR;
    public:
        ElementNode(){}
        ElementNode(int rr, int cc, char d) : r(rr), c(cc), data(d), distance_to_R(0){}
        ~ElementNode(){}
    private:
        int r, c;
        char data;
        int distance_to_R;
        queue <adjnode> adjlist;
        adjnode parent;
};

class FCR{
    public:
        FCR() : m(0), n(0), B(0){}
        ~FCR(){}
        void read(){
            ifstream rdfile;
            rdfile.open("floor.data", ios::in);
            if (!rdfile){
                cout << "error";
            }
            rdfile >> m >> n >> B;
            matrix = new ElementNode *[m * n];
            char d;
            for (int i = 0; i < m; i++){
                for (int j = 0; j <  n; j++){
                    rdfile >> d;
                    ElementNode *tmp;
                    if (d == '0'){
                        tmp = new ElementNode(i, j, '#');
                    }
                    else if (d == '1'){
                        tmp = new ElementNode(i, j, '$');
                    }
                    else{
                        tmp = new ElementNode(i, j, 'R');
                        R.r = i;
                        R.c = j;
                    }
                    *(matrix + i * n + j) = temp;
                }
            }
            rdfile.close();
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    if((*(matrix + i * n + j))->data != '$'){     
                        if(i != 0 && i != m - 1 && j != 0 && j != n - 1){
                            if((*(matrix + i * n + j + 1))->data != '$'){
                                adjnode adjn(i, j + 1);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                            }
                            if((*(matrix + (i - 1) * n + j))->data != '$'){
                                adjnode adjn(i - 1, j);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                             }
                            if((*(matrix + i * n + j - 1))->data != '$'){
                                adjnode adjn(i, j - 1);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                            }
                            if((*(matrix + (i + 1) * n + j))->data != '$'){
                                adjnode adjn(i + 1, j);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                            }
                        }
                        else{
                            if((i == 0 && j == 0) || (i == 0 && j == n - 1) || (i == m - 1 && j == 0) || (i == m - 1 && j == n - 1)){}
                            else if(i == 0){
                                adjnode adjn(i + 1, j);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                            }
                            else if(i == m - 1){
                                adjnode adjn(i - 1, j);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                            }
                            else if(j == 0){
                                adjnode adjn(i, j + 1);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                            }
                            else if(j == n - 1){
                                adjnode adjn(i, j - 1);
                                (*(matrix + i * n + j))->adjlist.push(adjn);
                            }
                        }  
                    }
                }
            }      
        }
        void BFS_FindDisranceToR(){
            visited = new bool *[m];
            int disc = 0;    
            link <adjnode> *curr;
            for(int i = 0; i < m; i++)
                visited[i] = new bool [n];      
            for(int i = 0;i < m; i++){
                for(int j = 0; j < n; j++){
                    visited[i][j] = false;
                }
            }
        
            queue <adjnode> q;
            visited[R.r][R.c] = true;
            matrix[n * R.r + R.c]->distance_to_R = disc;
            q.push(R);
            while(!q.empty()){
                adjnode node = q.front();  
                q.pop(); 
                for(curr = matrix[n * node.r + node.c]->adjlist.first; curr != nullptr; curr = curr->next){
                    if(visited[curr->value.r][curr->value.c] == false){
                        visited[curr->value.r][curr->value.c] = true;             
                        matrix[n * curr->value.r + curr->value.c]->distance_to_R = matrix[n * node.r + node.c]->distance_to_R + 1;
                        matrix[n * curr->value.r + curr->value.c]->parent = node;
                        q.push(curr->value);
                    }
                }
            }
            //cout << maxdis << endl;
            for(int i = 0; i < m; i++)
                delete[] visited[i];
            delete []visited;
        }
