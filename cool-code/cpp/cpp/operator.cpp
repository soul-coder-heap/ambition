#include <iostream>
#include <optional>
#include <string>
using namespace std;
struct myint {
    size_t pos{0};
    std::string str{"110"};
    //friend std::istream& operator >>(istream &in,myint& da);
    //friend std::ostream& operator <<(ostream &out,const myint& da);
    myint(){
        std::cout <<"1construct"<< std::endl;
    }
    myint(const myint &d){
        std::cout <<"2construct"<< std::endl;
    }
    myint(myint && d){
        std::cout <<"3construct"<< std::endl;
    }
    ~myint(){
        std::cout <<"distruct"<< std::endl;
    }
    std::istream& operator >>(istream &in){
        in >> this->pos>>this->str;
        return in;
    }
    std::ostream& operator <<(ostream &out){
        out << this->pos <<","<<this->str;
        return out;
    }
};
std::optional<myint> getValue(int i){
    if(i >= 0)
        return myint();
    else
        return {};
}

std::istream& operator >>(istream &in,myint& da){
    in >> da.pos>>da.str;
    return in;
}
std::ostream& operator <<(ostream &out,const myint& da){
    out << da.pos <<","<<da.str;
    return out;
}
int main(){
    //auto re = getValue(1);
    //if(re) std::cout <<"getvalue(1) : "<<*re<<"\n";
    //re = getValue(-1);
    //if(!re) std::cout <<"nothing"<< "\n";
    myint b;
    // std::cout <<b<<"\n";
    //std::cin >>b;
    //std::cout <<b<<"\n";
    auto fn = [&b](){
        std::cout << b << std::endl;
    };
    fn();
}

