/*************************************************************************
 > File Name: find_number.cpp
 > Author: yafeng.zhao 
 > Mail: wakeup_7am@foxmail.com
 > Created Time: 日 12/26 01:23:09 2021
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
int FindOneNumber(int *a, int length){
    int candidate = a[0];
    int nTimes = 1;
    for(int i = 1; i < length; i++){
        if(nTimes == 0){
            candidate = a[i];
            nTimes = 1;
        }else{
            if(candidate == a[i]){
                nTimes++;
            }else{
                nTimes--;
            }
        }
    }
    return candidate;
}
int main(){
    std::vector<int> vec{1,1,2,3,5,8,1,1,2,1,1,1,1,1,4,5,4,1,1,1,134,3};
    for(auto &n:vec){
        std::cout <<n<<" appear : "<<std::count(vec.begin(), vec.end(), n)<< std::endl;
    }
    std::cout <<"size : "<<vec.size()<<std::endl;
    std::cout <<"more than hlf : "<<FindOneNumber(vec.data(), vec.size())<< std::endl;

    return 0;
}
