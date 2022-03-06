#include <iostream>
#define ADD(a,b)\
        (a+b)
#if 0
#define DO(a,b)\
        a+b;\
        a++;
#endif
#define DO(a,b)\
        do{   \
            a+b;\
            a++;\
            std::cout <<a<<","<<b<< std::endl;\
        }while(0)
#if 0
#define COM(a,b)\
        {         \
            int x;\
            x = a;\
            a = b;\
            b = x;\
        }
#endif
#define COM(a,b)       \
        do{            \
            auto x = a;\
            a = b;     \
            b = x;     \
        }while(0)

#define STR(s)  \
        #s

#define CONS(a,b)  \
        int(a##e##b)


int main(){
    std::cout <<ADD(10,33/2)<< std::endl;
    int a = 12;
    int b = 132;
    DO(a,b);
    std::cout <<a<<","<<b<< std::endl;

    if(a < b)
    {
        COM(a,b);
        std::cout <<"a = "<<a<<",b = "<<b<< std::endl;
    }
    else
    {
        std::cout <<"don't need switch"<< std::endl;
    }

    printf("int value: %s\n",STR(100));
    printf("%d\n",CONS(10,10));
}
