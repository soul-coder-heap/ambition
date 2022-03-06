#include <iostream>
#include <string>
#include <initializer_list>
template <class... T>
void f(T... args)
{
	auto len = sizeof...(args);
	for(int i = 0; i < len; i++)
		std::cout <<i<< "\t";
	std::cout <<"\n";
}
void print(){
	std::cout <<"empty"<< std::endl;
}
template <typename T>
void print(T t){
		std::cout <<"last elem : "<<t<< std::endl;
}
template<class T,class... Args>
void print(T head,Args ...args){
	std::cout <<"parameter : "<<head<< "\t\t";
	print(args...);
}
// use type_traits
template<std::size_t I = 0,typename Tuple>
typename std::enable_if<I == std::tuple_size<Tuple>::value>::type print_tp(Tuple t){
	std::cout <<"what"<< std::endl;
}
template<std::size_t I = 0,typename Tuple>
typename std::enable_if<I < std::tuple_size<Tuple>::value>::type print_tp(Tuple t){
	std::cout <<std::get<I>(t)<< std::endl;
	print_tp<I + 1>(t);
}
template<typename ...Args>
void printtp(Args ...args){
	print_tp(std::make_tuple(args...));
}

// ,逗号表达式，非递归方式
template<typename T>
void printarg(T t){
	std::cout <<t<< std::endl;
}
template<typename ... Args>
void expand(Args ... args){
	int arr [] = {(printarg(args),1)...};
	for(int i = 0; i < sizeof...(args);i++)
		std::cout <<i<<" : "<<arr[i]<< std::endl;
}
/*
template<typename ...Args>
void expand2(Args ...args){
	std::initializer_list<int>{([&]{std::cout << args << std::endl;}(), 0)...};
}
*/
template<class ...Args>
void printfold(Args && ...args){
	(std::cout << ... << args) << std::endl;
}
//template<typename ...Args>
template<typename ...Args> struct Sum;
template<typename First,typename ... Rest>
struct Sum<First,Rest...>
{	
	enum{value = Sum<First>::value + Sum<Rest...>::value};
};
template<typename Last>
struct Sum<Last>
{
	enum{value = sizeof(Last)};
};

int main(){
	print();
	print(1,2345,67);
	print("1","3","qwf","q");
	print(1,3/4,"qwf","q");
	print(1,2,"3",4.4,"string");
	printtp(1,2,"3",4.4,"string");
	expand(1,2,3);
	printfold("1","w");
	static_assert(Sum<int,double,short>::value == 14,"int,double,short size = 14");
}
