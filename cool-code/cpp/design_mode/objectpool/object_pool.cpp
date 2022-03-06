#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <tuple>

using namespace std;

const static int MaxObjectNum = 10;

template<typename T>
class ObjectPool{
    template<typename... Args>
    using Constructor = std::function<std::shared_ptr<T>(Args...)>;
public:
    ObjectPool():needClear(false){}
    ~ObjectPool(){
        needClear = true;
    }
    //创建对象
    template<typename ...Args>
    void Init(size_t numeric,Args&& ...args){
        if(num < 0 || num > MaxObjectNum)
            throw std::logic_error("object num out of range.");
        auto constructName = typeid()
    }
private:
    std::multimap<std::string,std::shared_ptr<T>> m_object_map;
    bool needClear;
};
