#include <iostream>
#include <memory>
#include <optional>
#include <atomic>
template<typename T>
class queue{
public:
    queue(int size):max(size+1){
        std::shared_ptr<T> temp(new T[max],[](T* p){
            delete []p;
            std::cout <<"distruct"<< std::endl;
        });
        _queue = std::move(temp);
    }
    void push(T && data){
        if(!full()){
            len++;
            _queue.get()[b_pos] = data;
            b_pos = (b_pos + 1)%max;
      
        }else{
            std::cerr <<"current queue is full..."<< std::endl;
        }
    }
    std::optional<T> pop(){
        if(!empty()){
            len--;
            auto t = _queue.get()[a_pos];
            a_pos = (a_pos + 1) % max;
            return std::move(t);
        }else{
            return {};
        }
    }

    bool empty(){
        bool sign = false;
        if(len == 0)
            sign = true;
        return sign;
    }
    bool full(){
        bool sign = false;
        auto next = (b_pos + 1) % max;
        if(next == a_pos)
            sign = true;
        return sign;
    }
    int length(){
        return len;
    }
    int size(){
        return max;
    }
private:
    std::shared_ptr<T> _queue;
    int max{0};
    int len{0};
    int b_pos{0};
    int a_pos{0};
};
int main(){
    queue<int> q(10);
    for(int i = 0; i < 11; i++)
        q.push(std::move(i));
    for(int i = 0; i < 13; i++){
        auto v = q.pop();
        if(v) std::cout <<"pop value : "<<*v<< std::endl;
        else std::cout <<"啥都不是"<< std::endl;
    }
    std::cout <<"len = "<<q.size()<< std::endl;
}