#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

template<typename T>
class Singleton{
public:
    template<typename ...Args>
    static T* Instance(Args &&... args ){
        if(m_pInstance == nullptr){
            m_pInstance = new T(std::forward<Args>(args)...);
        }
        return m_pInstance;
    }
    static T* GetInstance(){
        if(m_pInstance == nullptr){
            throw std::logic_error("the instance is not init,please inittializes the instance first.");
        }
        return m_pInstance;
    }
    static void DestroyInstance(){
        delete m_pInstance;
        m_pInstance = nullptr;
    }
    
    Singleton() = delete;
    ~Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton &operator = (const Singleton&) = delete;
private:
    static T* m_pInstance;
};


