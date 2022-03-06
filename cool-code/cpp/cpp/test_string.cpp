#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
std::string_view str(){
    std::string s = "12345";
    std::string_view r = s;
    return std::string(r);
}

int main(){
#if 0
    std::string separator = ", ";
    std::stringstream os;
    for(int i = 0; i < 10; i++){
        os << std::to_string(i) << separator;
    }
    std::string result = os.str();
    std::string_view r = result;
    std::cout <<r<<" size : "<<r.length()<< std::endl;
    if (!result.empty()) {
        //result.erase(result.length() - separator.length(), separator.length());
        r.remove_suffix(separator.length());
        std::cout <<r<<" no empty,size : "<<r.length()<< std::endl;
    }
    std::cout <<r<<" size : "<<r.length()<< std::endl;
#endif
    auto s = str();
    std::cout <<s<< std::endl;
}


