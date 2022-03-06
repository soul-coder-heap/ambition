#include <string>
#include <vector>
#include <iostream>
class A{
    public:
    //static const std::vector<std::string> a{"12","123","127"};
    static std::vector<std::string> a;//{"12","123","127"};
    static const int i{12};
};
std::vector<std::string> A::a = {"10", "11", "12"};
int main(){
    std::cout <<A::i<< std::endl;
    std::cout <<A::a.size()<< std::endl;
}
