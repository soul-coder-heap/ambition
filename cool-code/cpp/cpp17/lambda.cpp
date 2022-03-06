/*************************************************************************
	> File Name: lambda.cpp
	> Author: yafeng.zhao 
	> Mail: 1841531744@qq.com
	> Created Time: 六  7/24 10:30:16 2021
 ************************************************************************/

#include <iostream>
#include <memory>
#include <tuple>
#include <array>
#include <algorithm>
#include <numeric>
[[deprecated]]
void old_method();

[[deprecated("use new_method instead")]]
void legacy_method();

template<typename Array, std::size_t... I>
decltype(auto) a2t_impl(const Array& a, std::integer_sequence<std::size_t, I...>) {
  return std::make_tuple(a[I]...);
}

template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
decltype(auto) a2t(const std::array<T, N>& a) {
  return a2t_impl(a, Indices());
}

auto f(int i) {
    std::cout <<i<<"void f"<< std::endl;
     return i;
}

template<typename T>
auto& f(T& t){
    std::cout <<t<<"template f"<< std::endl;
    return t;
}

// variable template
template<class T>
const T pi = T(3.1415926535897932385);
template<class T>
const T e = T(2.7182818284590452353);

constexpr int factorial(int n){
    if(n <= 1){
        return 1;
    }else{
        return n + factorial(n - 1);
    }
}
template <typename First, typename... Args>
auto sum(const First first, const Args... args) -> decltype(first) {
      const auto values = {first, args...};
        return std::accumulate(values.begin(), values.end(), First{0});
}


template<typename ...Args> auto sum(Args ...args)
{
    return (args + ...);
}

int main(){
    std::cout <<sum(124,5,4,53,465,635)<< std::endl;
    std::cout <<"factorial(10) : "<<factorial(10)<< std::endl;
    std::cout <<"pi"<<pi<float><< std::endl;
    std::cout <<"e"<<e<double><< std::endl;
    f(123);
    int x = 1;
    //int& yy = f(x);
    auto g = [](auto &x) ->auto &{return f(x);};
    //int& zz = g(x); 
    auto f = [&r = x, x = x * 10]{
        std::cout <<__func__<<", r = "<<r<<", x = "<< x<<std::endl;
        ++r;
        return r + x;
    };
    f();
    std::cout <<__func__<<", x = "<< x<<std::endl;


	auto tup = a2t(std::array<int,7>{12,134,546,5,456,23,3});
    std::cout <<std::get<5>(tup)<< std::endl;
    auto identity = [](auto x) {return x;};
    auto i = identity(100);
    auto s = identity("struggle");
    std::cout <<i<<", "<<s<< std::endl;
    auto generator = [x=0]() mutable {return x++;};
    auto a = generator();
    auto b = generator();
    auto c = generator();
    std::cout <<a<<", "<<b<<", "<<c<< std::endl;
    auto p = std::make_unique<int>(1);
    std::cout <<*p<< std::endl;
    //auto task1 = [p = std::move(p)]{*p = 5;};
    auto task2 = [ptr = std::move(p)](int val) {*ptr = val;return *ptr;};
    auto p1 = task2(100);
    std::cout <<p1<< std::endl;
}
