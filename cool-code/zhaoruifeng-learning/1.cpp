#include <iostream>
#include <stdio.h>

// 头文件 iostream 包括输入、输出的运算符： std::cin (输入)，std::cout (输出)， 一般用于 cpp 中
// 头文件 stdio.h 包括输入、输出函数：scanf(输入)，printf(输出)，一般在 cpp或者c中都可用（主要在c中），比 cpp 的运算符效率高
// 自行探究为何 c 的输入输出比 cpp 的效率高


/*
 题目：计算1000以内的水仙花数
 水仙花数： 水仙花数（NarcissisticNumber）是指一个n位数，其各位数字的立方和等于它本身
 */

// 计算水仙花的个数，参数是 int 类型，表示最大的范围（题目要求计算1000以内，所以这里函数调用时参数是1000）；返回值是 int 类型，表示该范围内水仙花数的个数
int count_narcissistic_number(int max){
    int count = 0;
    for(int i = 1; i < 10; i++){
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 10; k++) {
                // 根据位数计算数字
                int sum = i * 100 + j * 10 + k;
                // 限定范围， 超过 max 的数字过滤掉
                if(max < sum){
                    continue;
                }else{
                    // 判断是否是水仙花数
                    if(sum == (i * i * i + j * j * j + k * k * k)){
                        count += 1;
                    }      
                }
            }
        }
    }
    // 返回值
    return count;
}

// 输出具体的水仙花数，参数是 int 类型(同上)；返回值为 void 类型，表示没有返回值
void show_narcissistic_number(int max){
    printf("输出 %d 以内的水仙花数：", max);
    for(int i = 1; i < 10; i++){
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 10; k++) {
                int sum = i * 100 + j * 10 + k;
                if(max < sum){
                    continue;
                }else{
                    if(sum == (i * i * i + j * j * j + k * k * k)){
                        printf("%d ", sum);
                    }      
                }
            }
        }
    }
    printf("\n");
}


// 主函数， 一般返回值是 int
int main(){
    int value = 1000;
    // 调用函数计算value 以内水仙花数的个数，该函数有返回值，所以需要用变量 num 接受返回值
    int num = count_narcissistic_number(value);
    printf("计算获得 %d 以内的水仙花数共计 %d 个\n", value, num);

    // 调用函数输出value以内的水仙花数
    show_narcissistic_number(value);

    // main 函数的返回值，正常返回0，返回其他值表示程序运行异常。以后自行探究
    return 0;
}
