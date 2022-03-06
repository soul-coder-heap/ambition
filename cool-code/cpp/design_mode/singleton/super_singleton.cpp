#include "super_singleton.h"
#include <iostream>
#include <string>
using namespace std;
//template<typename T> T* Singleton<T>::m_pInstance = nullptr;

struct A{
    A(const string &){std::cout <<"lvaue"<< std::endl;}
    A(const string &,const string &){std::cout <<"lvaue,rvalue"<< std::endl;}
    A(string &&){std::cout <<"rvalue"<< std::endl;}
    void fun(){
        std::cout<<"hahahahahahahah"<< std::endl;
    }
};

int main(){
    string str = "sb";
    auto v = Singleton<A>::Instance(str);
    v->fun();
    auto &nv = v;
    nv->fun();
}
