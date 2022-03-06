#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <future>
float Q_rsqrt(float number){    
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    x2 = number * 0.5F;
    y = number;
    i  = * (long *  ) &y;
    i  = 0x5f3759df - ( i >> 1  ); // what the fuck?
    y  = * ( float *  ) &i;
    y  = y * ( threehalfs - ( x2 * y * y  )  );// 1st iteration
    y   = y * ( threehalfs - ( x2 * y * y  )  ); // 2nd iteration, this can be removed
    return 1/y;
}
//const double eps = 1e-8;
const double eps = 1e-1;
//#define Equ(a,b) ((fabs((a) - (b))) <= (eps))
int main(){
    int num = 0;
    /*
    for(double i = 1; i < 1000; i++){
        auto re = fabs(sqrt(i) - Q_rsqrt(i));
        std::cout <<re<< std::endl;
        if(re < 0.0001) num++;
    }
    std::cout <<"total same result : "<<num<< std::endl;
    */
    auto re = std::async([](){
        auto start = std::chrono::system_clock::now();
        for(int i = 1; i < 100000; i ++){
            auto re = Q_rsqrt(i);
            std:: cout <<re<< std::endl;;
        }
        auto end = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout <<"Q_rsqrt time cost : "<<ms<< std::endl;
    });
    auto re1 = std::async([](){
        auto start = std::chrono::system_clock::now();
        for(int i = 1; i < 100000; i ++){
            auto re = sqrt(i);
            std:: cout <<re<< std::endl;;
        }
        auto end = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout <<"sqrt time cost : "<<ms<< std::endl;
    });
    re.get();
    re1.get();


}

