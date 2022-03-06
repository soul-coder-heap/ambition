#include <iostream>

static int i = 10;
class A{};
class B{
    virtual void test() = 0;
};

int main(){
    static int j = 0;
    std::cout <<sizeof(i)<< std::endl;
    std::cout <<sizeof(&i)<< std::endl;
    std::cout <<sizeof(j)<< std::endl;
    std::cout <<sizeof(A)<< std::endl;
    std::cout <<sizeof(B)<< std::endl;
    int arr[] = {1,2,3,4,5,4};
    auto p = arr;
    std::cout <<sizeof(arr)<<", "<<sizeof(p)<<", void* "<<sizeof(void*)<<std::endl;
    //Bit mode:2;
    return 0;
}
