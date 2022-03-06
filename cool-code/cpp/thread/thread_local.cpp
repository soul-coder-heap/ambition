#include <thread>
#include <iostream>
/*thread_local */  static thread_local int i = 0;
void f(int newval){
    i = newval;
    std::cout <<"f addr = "<<&i<< " value = "<< i << std::endl;
}
void g() {
    std::cout <<"g addr = "<<&i<< " value = "<< i << std::endl;
}
void threadfun(int id){
    f(id);
    ++i;
    g();
}
void threadfun1(int *p){
    *p =421;
}
struct my_class{
    my_class(){
        std::cout <<"hello"<< std::endl;
    }
    ~my_class(){
        std::cout <<"goodbey"<< std::endl;
    }
    int i = 0;
    static my_class gettsl(){
        static thread_local my_class tsl;
        return tsl;
    }
};
void dd(int i){
    ++my_class::gettsl().i;
    std::cout <<"current thread id = "<<std::this_thread::get_id() <<" p addr = "<<&(my_class::gettsl())<< " p.i val = "<<my_class::gettsl().i <<std::endl;;
}
void do_something(){
    for(int i = 0; i < 100 ; i++)
    dd(i);
}

int main(){
    i = 9;
    //std::thread(threadfun,1).join();
    //std::thread(threadfun,2).join();
    //std::thread(threadfun,3).join();
    //std::thread(f,i).join();
    //std::thread(threadfun1,&i).join();
    std::thread(do_something).join();
    //std::cout <<"main addr " <<&i<<"  value = "<<i<< std::endl;
}
