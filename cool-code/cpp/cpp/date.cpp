#include <iostream>
#include <string>
#include <cstring>
#include <vector>
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
        if(v[i] != v[len - 1 -i])
            return false;
    }
    return true;
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
        std::cout <<"please check init execption..."<< std::endl;
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
    uint32_t yt = 5000;   // count number
    date d;               // 2020-02-02
    for(int i = 0; i < 365 * yt; i++){
        d.djudge();
        ++d;
    }
    std::cout << "\n2020-02-02 之后的"<<yt<<"年共计"<<d.getlen()<<"个对称日"<<std::endl;
    return 0;
}
