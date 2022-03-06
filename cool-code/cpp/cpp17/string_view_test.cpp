#include <string_view>
#include <string>
#include <iostream>
int main(){
    // Regular strings
    std::string_view cppstr{"foo"};
    // Wide strings
    std::wstring_view wcstr{L"bza"};
    char array[]{'q','a','l'};
    std::string_view array_v(array,std::size(array));
    const char* arr = "aaaa123";
    std::string_view arr_v(arr);
    std::string vv = "swds";
    std::string_view v = vv;
    std::string v1 = v; 
    ///std::cout <<cppstr<< std::endl; 
    ///std::cout <<wcstr<<std::endl;
    ///std::cout <<array_v<< std::endl;
}
