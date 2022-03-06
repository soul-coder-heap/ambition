#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <optional>

template<typename T>
class Singleton{
public:
    template<typename ...Args>
    static auto Instance(Args &&... args ){
        static std::unique_ptr<T,void(*)(T*)> m(new T(std::forward<Args>(args)...),[](T *t){
            delete t;
            std::cout <<"distruct T type"<< std::endl;
        });
        return std::move(m);
    }
    Singleton() = delete;
    ~Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton &operator = (const Singleton&) = delete;
};


