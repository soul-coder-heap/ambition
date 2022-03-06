#include <iostream>
union A{
    int a;
    char b;
};
int main(){
    A a;
    a.a = 0x12345678;
    if(a.b == 0x12) std::cout << "big"<< std::endl;
    if(a.b == 0x78) std::cout << "little" << std::endl;
}
