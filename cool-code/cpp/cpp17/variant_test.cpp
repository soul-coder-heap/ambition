#include <variant>
#include <string>
#include <iostream>
#include <cassert>

int main(){
    std::variant<int,double> v{12};
    assert(std::get<0>(v) == 12);
    assert(std::get<int>(v) == 12);
    v = 1.2;
    std::cout <<std::get<1>(v)<< std::endl;
}

