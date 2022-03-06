#include <iostream>
#include <memory>
#include <string_view>
#include <string>
#include <functional>
template<typename T>
std::shared_ptr<T> make_shared_array(size_t size){
    return std::shared_ptr<T>(new T[size],[](T* p){
        delete []p;
        std::cout <<"release array."<< std::endl;
    });
}
int main(){
    std::string a{"ce shi"};
    std::string_view b = a;
    std::shared_ptr<int[]> arr(new int[100],[](int *p){
        std::cout <<"release array"<< std::endl;
        delete []p;
    });
    auto arrInt = make_shared_array<int>(100);
    std::unique_ptr<int[],void(*)(int *)> pt(new int[100],[](int *p){delete []p;std::cout <<"ffffff"<< std::endl;});
    std::unique_ptr<int[],std::function<void(int *)>> ptt(new int[100],[&](int *p){delete []p;std::cout <<"rrrrrrrrr"<< std::endl;});
   
    auto sh_aar = std::make_shared<int []>(100);
    auto un_aar = std::make_unique<int []>(100);

    sh_aar[99] = 12;
    un_aar[99] = 122;
    
    std::cout <<sh_aar[99]<<"  "<<un_aar[99]<< std::endl;
    return 0;
}
