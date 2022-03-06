#include <future>
#include <thread>
#include <iostream>
#include <functional>
#include <chrono>
#include <experimental/coroutine>

struct Task{
    struct promise_type{
        auto get_return_object(){return Task{};}
        auto initial_suspend(){return std::experimental::suspend_never{};}
        auto final_suspend(){return std::experimental::suspend_never{};}
        void unhandled_exception(){std::terminate();}
        void return_void(){}
    };
};
//普通异步函数
using call_back = std::function<void(int)>;
void AddCall(int init,call_back f){
    std::thread([init,f](){
        //std::this_thread::sleep_for(std::chrono::second(5));
        f(init + 1000);
    }).detach();
}
struct AddAWaitable{
    AddAWaitable(int init):_init(init){}
    bool await_ready() const {return false;}
    int await_resume(){return _result;}
    void await_suspend(std::experimental::coroutine_handle<> handle){
        auto f = [handle,this](int value) mutable{
            _result = value;
            handle.resume();
        };
    }
    int _result;
    int _init;
};
//协程
Task AddCoroutine(int init,call_back f){
    std::cout <<"xxxxx"<< std::endl;
    int ret = co_await AddAWaitable(init);
    ret = co_await AddAWaitable(ret);
    ret = co_await AddAWaitable(ret);
    f(ret);
    std::cout <<"add process"<< std::endl;
}


int main(){
    //AddCall(10,[](int value){std::cout <<"get result from async"<< std::endl;});
    std::cout <<"start"<< std::endl;
    AddCoroutine(10,[](int value){std::cout <<"get result from coroutine"<< std::endl;});
    std::cout <<"end"<< std::endl;
}
