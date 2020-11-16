#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;
template <class T> class stack;
template <class T> class queue;
class FCR;

template <classs T>
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