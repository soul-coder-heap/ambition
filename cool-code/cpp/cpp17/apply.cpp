#include <chrono>
#include <thread>
#include <functional>
#include <string>
#include <iostream>
#include <tuple>
template <typename Func, typename Ret = std::invoke_result_t<Func>, typename... T>
static inline Ret apply(Func && func, T...&& args){
    //(std::cout <<...<<args) << std::endl;
    auto t = std::make_tuple(std::forward(args...));  
    if constexpr(std::is_void_v<Ret>){
        func(t);
    }else{
        return func(t);
    }
}

int main(){
    std::make_tuple(122,342134,124,23423421.12343,323412343.42314);
    auto func = [](){};

}