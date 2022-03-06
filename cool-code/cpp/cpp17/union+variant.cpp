#include <variant>
#include <string>
#include <map>
#include <cassert>
#include <iostream>
int main(){
    std::variant<int,float> v,w; 
    v = 12 ;  // v包含int 
    int i = std::get<int>(v);
    std::cout <<"i = "<<i<< std::endl;
    w = std::get<int>(v); 
    //std::cout <<"w = gte<int>(v) = "<<w<< std::endl;
    w = std::get<0>(v);  //与前一行相同的效果    
    w = v;  //与上一行相同的效果
    std::map<int,std::string> st;
    st[0] = 20;
    st[1] = "https:///www.baidu.com";
    std::variant <std::string, std::map<int,std::string> > complex;
    complex = st;

}
