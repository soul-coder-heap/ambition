#include <optional>
#include <string>
#include <iostream>
#include <variant>
#include <type_traits>
#include <tuple>
#include <any>

// C++ return multiple value

// 1.returned value,reference parameter
bool func(const std::string& in,std::string& out1,std::string& out2){
    if(in.size() == 0) return false;
    out1 = "hello";
    out2 = "world";
    return true;
}
// 2.tuple
std::tuple<bool,std::string,std::string> func(const std::string& in){
    if(in.size() == 0)
        return std::make_tuple(false,"","");
    return std::make_tuple(true,"hello0","world0");
}
// 3.pair
namespace pair{
    struct Out{
        std::string out1{};
        std::string out2{};
    };
}
std::pair<bool,pair::Out> func1(const std::string& in){
    pair::Out o;
    if(in.size() == 0){return {false,o};}
    o.out1 = "hello1";
    o.out2 = "world1";
    return {true,o};
}
// 4.optional
std::optional<pair::Out> func2(const std::string& in){
    pair::Out o;
    if(in.size() == 0) return std::nullopt;
    o.out1 = "hello2";
    o.out2 = "world2";
    return {o};
}
// 5.variant
std::variant<bool,pair::Out> func3(const std::string& in){
    std::variant<bool,pair::Out> re;
    if(in.size() == 0){
        re = bool{};
    }else{
        pair::Out o;
        o.out1 = "hello3";
        o.out2 = "world3";
        re = o;
    }
    return {re};
}
// 5. any
std::any func4(const std::string& in){
    if(in.size() == 0) return bool{};
    pair::Out o;
    o.out1 = "hello4";
    o.out2 = "world4";
    return {o};
}
int main(){
    std::string s1,s2;
    int status = func("hi",s1,s2);
    if(status){
        std::cout <<s1<< std::endl;
        std::cout <<s2<< std::endl;
    }
    //tuple返回，结构化绑定 c++17
    if(auto [status,out1,out2] = func("hi");status){
        std::cout <<out1<< std::endl;
        std::cout <<out2<< std::endl;
    }
    //pair返回，结构化绑定
    if(auto [status,o] = func1("hi");status){
        std::cout << o.out1 << std::endl;
        std::cout << o.out2 << std::endl;
    }
    //optional 返回
    if(auto ret = func2("hi");ret.has_value()){
        std::cout <<ret->out1<< std::endl;
        std::cout <<ret->out2<< std::endl;
    } 
    //variant
    if(auto ret = func3("hi");!std::get_if<bool>(&ret)){
        std::cout <<std::get<pair::Out>(ret).out1 << std::endl;
        std::cout <<std::get<pair::Out>(ret).out2 << std::endl;
    }
    //any
    if(auto ret = func4("hi");ret.type() != typeid(bool)){
        auto o = std::any_cast<pair::Out>(ret);
        std::cout << o.out1 << std::endl;
        std::cout << o.out2 << std::endl;
    } 
}
