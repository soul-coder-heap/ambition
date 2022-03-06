#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <vector>
#include <iomanip>
#include <sstream>

bool judge(uint64_t i){
    std::vector<uint32_t> v;
    while(i){
        auto t = i % 10;
        v.emplace_back(t);
        i /= 10;
    }
    int len = v.size();
    int r = len / 2 + 1;
    for(int i = 0; i < r - 1; i++){
        if(v[i] != v[len - 1 - i])
            return false;
    }
    return true;
}

void dict(std::vector<uint64_t> & v){
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    auto n = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24 * 365 * 1000)); 
    std::cout << std::put_time(std::localtime(&n),"%Y%m%d") << std::endl;;
    n = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24 * 365 *500)); 
    std::cout << std::put_time(std::localtime(&n),"%Y%m%d") << std::endl;;
    n = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24 * 365 *300)); 
    std::cout << std::put_time(std::localtime(&n),"%Y%m%d") << std::endl;;
    uint64_t d = 24 * 365 * 500;
    n = std::chrono::system_clock::to_time_t(now + std::chrono::hours(d)); 
    std::cout << std::put_time(std::localtime(&n),"%Y%m%d") << std::endl;;
    
    char ch[100];
    std::string ss;
    for(uint64_t i = 0; i < 1/*2000 * 3658*/; i++) {
        auto next = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24 * i)); 
        std::strftime(ch,sizeof(ch),"%Y%m%d",std::localtime(&next));
        ss = ch;
        memset(ch,0,100);
        auto vl = atoi(ss.c_str());
        if(judge(vl)){
            v.emplace_back(vl);
        }
    }  
}
class date{
private:
    uint64_t year {2020};
    uint64_t month {2};
    uint64_t day {2};
    uint64_t len {0};
    std::vector<uint64_t> week{31,29,31,30,31,30,31,31,30,31,30,31};
public:
    date() = default;
    date(uint64_t _y,uint64_t _m,uint64_t _d):year(_y),month(_m),day(_d){
        std:: cout <<"please check init execption..."<< std::endl;
    }
    void djudge(){
        std::stringstream ss;
        ss << year;
        if(month < 10) ss <<"0"<<month;
        else ss << month;
        if(day < 10) ss <<"0"<<day;
        else ss << day;
        std::string tt = ss.str();
        uint64_t value = std::atoi(tt.c_str());
        if(judge(value)){
            this->show();
            len++;
        }
    }
    void show(){
        static int i = 1;
        std::stringstream ss;
        ss << year;
        ss << "-";
        if(month < 10) ss <<"0"<<month;
        else ss << month;
        ss << "-";
        if(day < 10) ss <<"0"<<day;
        else ss << day;
        std::cout <<ss.str()<< '\t';
        if(i % 8 == 0) std::cout << std::endl;
        i++;
    }
    date& operator++(){        
        if((year % 4 == 0 && year % 100 != 0)|| (year % 400 == 0)){
            week[1] = 29;
        }else{
            week[1] = 28;
        }
        if(week[month - 1] >= day){
            day++;
            if(week[month - 1] + 1 == day){
                day = 1;
                month++;
                if(month == 13){
                    month = 1;
                    year++;
                }
            }
        }
        return *this;
    }
    uint64_t getlen(){
        return this->len;
    }
};


int main(){
    /*  std::vector<uint64_t> v;
    dict(v);
    for(int i = 1; i <= v.size();i++  ){
        std::cout <<i<<"."<<v[i-1]<< "\t";
        if(i % 8 == 0) std::cout <<"\n";
    }     
    std::cout <<"\n************************************"<< std::endl;
    std::cout <<"*2020-02-02 之后5000年共"<<v.size()<<"个对称日*"<< std::endl;
    std::cout <<"************************************"<< std::endl;
    
    */
    uint32_t yt = 5000;
    date d;
    for(int i = 0; i < 365 * yt; i++){
        d.djudge();
        ++d;
    }
    std::cout << "\n2020-02-02 之后的"<<yt<<"年共计"<<d.getlen()<<"个对称日"<<std::endl;
    return 0;
}
