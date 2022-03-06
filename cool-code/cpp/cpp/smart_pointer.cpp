#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <map>
#include <unordered_map>
#include <chrono>
#include <functional>
#include <map>
#include <unordered_map>
#include <functional>
template <typename T>
std::shared_ptr<T> make_shared_array(size_t size){
    return std::shared_ptr<T>(new T[size], [](auto *p){std::cout <<"release array shared"<< std::endl;delete[] p;p = nullptr;} /*std::default_delete<T[]>()*/);
}

class A{
    //std::shared_ptr
public:
    A(int a, std::string b){ std::cout <<"a : "<<a<<", b : "<<b<< std::endl;
   	pmap = std::make_unique<std::unordered_map<int, std::string>>();
	pmap->insert({a,b});
	//auto map = pmap.get();
	//map[a] = b;
    }
    ~A(){std::cout <<"Relase A"<< std::endl;}
    std::unique_ptr<std::unordered_map<int, std::string>> pmap;
};

int main(){
    //init
    std::shared_ptr<int[]> p(new int[222], [](auto *p){std::cout <<"real444444444444se!"<< std::endl;delete[] p;});
    std::shared_ptr<int[]> p1 = p;
    std::shared_ptr<int[]> ptr;
    int pv = 222;
    int *ps = p.get();
    *(ps + 100) = 1000;
    std::cout <<"ps 444444 : "<<p[100]<< std::endl;
    if(ptr == nullptr)
        std::cerr <<"ptr is null"<< std::endl;
    else
        std::cout <<"ptr point addr: "<<ptr.get()<<"  ptr addr : "<<&ptr<<"  ptr value : "<<*ptr.get()<<"  pv adddr : "<<&pv<< std::endl;

    //std::shared_ptr<int> parr(new int[30000000], [](auto *p){std::cout <<"realse!"<< std::endl;delete []p;});
    std::shared_ptr<int> parr = make_shared_array<int>(30) ;(new int[90], [](auto *p){std::cout <<"realse!"<< std::endl;delete []p;});
    const auto &arr = parr.get();
    arr[1] = 100;
    arr[12] = 122;
    arr[13] = 1002222;
    arr[4] = 102242420;
    for(int i = 0; i < 30; i++)
        std::cout <<i<<" : "<<arr[i]<<",\t";
    std::cout <<"\n";
    auto pp = std::make_shared<int[]>(100);
    pp[8] = 100;
    {
    	auto begin = std::chrono::high_resolution_clock::now();	    
    	std::unique_ptr<int [], /*void(*)(int *)*/std::function<void(int *)>> p1(new int[100], [begin](auto *p){
		delete []p;
    		auto end = std::chrono::high_resolution_clock::now();	    
		std::cout <<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<<"us,unique"<< std::endl;
	});
	p1[99] = 223;

    }
    {
    	auto begin = std::chrono::high_resolution_clock::now();	    
    	std::shared_ptr<int [] /*void(*)(int *)std::function<void(int *)>*/> p1(new int[100], [begin](auto *p){
		delete []p;
    		auto end = std::chrono::high_resolution_clock::now();	    
		std::cout <<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<<"us,shared"<< std::endl;
	});
	p1[99] = 223;

    }
    auto parrq = std::make_unique<int[]>(100);
    parrq[22] = 1234;
    int * ppp = parrq.get();
    std::cout <<"pppp : "<<*(ppp + 22)<< std::endl;
    std::cout <<"pppp22: "<<parrq[22]<< std::endl;

    {
	    std::cout <<"aaaaaaaaaaaaaaaaaaaaa1`"<< std::endl;
	    std::shared_ptr<A> spa(new A{12,"shared"});
	    auto smpa = std::make_shared<A>(12,"make_shared");
	    std::unique_ptr<A> upa(new A{122,"unique"});
	    auto umpa = std::make_unique<A>(122,"make_usssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssnique");
	    std::cout <<"aaaaaaaaaaaaaaaaaaaaa1`"<< std::endl;
	    auto iter = umpa->pmap->find(122);
		
	    std::cout <<iter->first<<" : "<<iter->second<< std::endl;
    
    }

    std::unique_ptr<int []> paaaa;
    paaaa = std::make_unique<int []>(100);	
    paaaa[99] = 1110;
    int *paaaa_ = paaaa.get();

    std::cout <<*(paaaa_ + 99)<< std::endl;

  	using Function = std::function<void(std::string,int)>;
       auto s = [](std::string,int){};
Function f = s;       
}


