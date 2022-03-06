#include "singleton.h"
#include <iostream>
#include <string>
using namespace std;
template<typename T> T* Singleton<T>::m_pInstance = nullptr;

struct A{
    A(const string &){std::cout <<"lvaue"<< std::endl;}
    A(string &&){std::cout <<"rvalue"<< std::endl;}
};

int main(){
    string str = "sb";
    Singleton<A>::Instance(str);
}
