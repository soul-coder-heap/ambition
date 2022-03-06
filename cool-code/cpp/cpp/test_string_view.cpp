#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

class Input{
public:
    std::string a;
    std::string b;
    Input(){
        a = "xxxxxxxxxxxxx";
        b = "yyyy\ty\ny\ryyyyyyy";
    }
};
class Demo{
public:
    std::string_view a;
    std::string b;
    std::string _removeTab(const std::string &s){
        std::string strCopy = s; 
        strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\t'), strCopy.end());
        strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\r'), strCopy.end());
        strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\n'), strCopy.end());
        return strCopy;
    }
    void setValue(const Input &lr){
        a = lr.a;
        b = std::move(_removeTab(lr.b));
    }
};


int main(){
    int x = 100;
    int y = 0;
    std::string s;
    s = x + "-" + std::to_string(x);
    Input in;
    Demo d;
    d.setValue(in);
    std::cout <<d.a<<"\n"<<d.b<<std::endl;
}
