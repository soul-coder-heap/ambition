//#include <format>
#include <iostream>
#include <string_view>
#include <string>
#define AD_SEVER(str) \
    do                \
        std::cout <<str<< std::endl;\
    while(0)
int main(){
    std::string ss = "wwASFDafaFafaFafafsafsafsa";
    std::string_view s = ss;
    AD_SEVER(ss);
    AD_SEVER(s);
}
