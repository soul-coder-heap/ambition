#include <iostream>
#include <unordered_map>
#include <bitset>
#include <string>
#include <utility>
#include <map>
#include <vector>
struct KEY{
    std::string first;
    std::string second;
    /*bool operator()(const KEY& other)const {
        return this->first == other.first;//) && lhs.second.equal(rhs.second); 
    }*/

};
struct KeyHash{
    std::size_t operator()(const KEY& k) const{
        return (std::hash<std::string>()(k.first) ^ (std::hash<std::string>()(k.second) << 1));
        //return std::hash<std::string>()("520");
    }
};
struct KeyEqual{
    bool operator()(const KEY& lhs,const KEY& rhs)const {
        return lhs.first == rhs.first;//) && lhs.second.equal(rhs.second); 
    }
};

int main(){
    std::unordered_map<std::string,std::string> ml;
    std::unordered_map<int,std::string> m2 = {
        {1,"bichen"},
        {2,"yuwei"},
        {3,"yangliu"}
    };
    std::unordered_map<int,std::string> m3 = m2;
    std::unordered_map<int,std::string> m4 = std::move(m2);
    //range construct
    std::vector<std::pair<std::bitset<8>,int>> v = {
        {0x12,1},
        {0x01,-2}
    };
    std::unordered_map<std::bitset<8>,double> m5(v.begin(),v.end());
    //construct 
    std::unordered_map<KEY,std::string,KeyHash,KeyEqual> m6 = {
        {{"John","Doe"},"example"},
        {{"Mary","Sue"},"another"}
    };
    
    auto m = std::hash<std::string>()("520");
    std::cout <<"m : " <<m<< std::endl;
}


