#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <functional>
#include <string>
class fixed_thread_pool{
public:
    explicit fixed_thread_pool(size_t thread_count):data_(std::make_shared<data>()){
        //static uint64_t num = 0;
        for(size_t i = 0; i < thread_count; ++i){
            std::thread([data = data_]{
                std::unique_lock<std::mutex> lk(data->mtx_);
                for(;;){
                    if(!data->tasks_.empty()){
                        auto current = std::move(data->tasks_.front());
                        data->tasks_.pop();
                        lk.unlock();
                        current();  // execute function
                        //std::cout <<num++<<",get task and exec..."<< std::endl;
                        lk.lock();
                    }else if(data->is_shutdown_){
                        break;
                    }else{
                        data->cond_.wait(lk);
                    }   
                }
            }).detach();
        }
    }
    fixed_thread_pool() = default;
    fixed_thread_pool(fixed_thread_pool&&) = default;
    ~fixed_thread_pool(){
        if((bool)data_){
            std::lock_guard<std::mutex> lk(data_->mtx_);
            data_->is_shutdown_ = true;
        }
        data_->cond_.notify_all();
        std::cout <<"distruct threadpool"<< std::endl;
    }
    template<class F>
    void execute(F && task){
        {
            std::lock_guard<std::mutex> lk(data_->mtx_);
            std::cout <<"insert task"<< std::endl;
            data_->tasks_.emplace(std::forward<F>(task));
        }
        data_->cond_.notify_one();
    }
    template<class F,class ...Args>
    auto execute(F && f,Args&& ...args)->std::future<decltype(f(args...))>{
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f),std::forward<Args>(args)...)
        );
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lk(data_->mtx_);
            std::cout <<"inset task, add to para"<< std::endl;
            data_->tasks_.emplace([task](){
                (*task)();
            });
        }
        data_->cond_.notify_one();
        return res;
    }
private:
    struct data{
        std::mutex mtx_;
        std::condition_variable cond_;
        bool is_shutdown_ = false;
        std::queue<std::function<void()>> tasks_;
    };
    std::shared_ptr<data> data_;

};

int main(){
    fixed_thread_pool thp{16};
    int value = 100;
    auto lam = [](int n,std::string s){
        int value = 0;
        for(int i = 0; i < n; i++){
            std::cout <<i + value <<".  "<<s<< std::endl;
        }
    };
    
    auto lam1 = [](){std::cout <<"没有感情的学习机器"<< std::endl;};
    thp.execute(lam,10,"mobcv");
    thp.execute(lam1);
}
