#include <iostream>
#include <math.h>
bool juage(int a,int b,int c){
    if(a < b && b < c){
    for(int i = 2; i < b; i++){
        if(a % i == 0 && b % i == 0)
            return false;
        if(b % i == 0 && c % i == 0)
            return false;
        if(a % i == 0 && c % i == 0)
            return false;
    }}
    return true;
}
int main(){
    int a;
    int b;
    std::cin >> a;
    std::cin >> b;
    int min = a * a;
    int max = b * b;
//    if(a < 1 || b > 200 )
    bool sign = false;
    for(int i = a; i < b;i++){
        for(int j = i + 1; j <= b;j++){
            auto v = i * i + j* j;
            if(v > min && v < max){
                int re = pow(v,0.5);
                if(re * re != v){continue;}       
                if(juage(i,j,re)){
                    sign = true;                   
                   // std::cout <<i<<"\t"<<j<<"\t"<<re<<std::endl;
                    std::cout <<i<<" "<<j<<" "<<re<<std::endl;
                }
            }
        }
    }
    if(!sign){
        std::cout <<"NA"<<std::endl;
    }
}
