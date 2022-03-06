#include <thread>
#include <iostream>
#include <string>
#include <mutex>
std::mutex cout_mutex;
void thread_func(const std::string &threadnum){
    int x = 1;
    //static thread_local int x = 1;
    for(int i = 0;i < 4; i++){
        x++;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout <<threadnum<<" : "<<x<< std::endl;
    }

}
int main(){
    std::thread(thread_func,"1").join();
    std::thread(thread_func,"2").join();
    std::thread(thread_func,"3").join();
}
