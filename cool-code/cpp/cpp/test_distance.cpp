#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
std::vector<int64_t> bucket_offset(100);
std::vettor<int64_t> buckets(101);
uint64_t _count{0};
uint64_t _sample_sum{0};
void add(int64_t n){
    auto pos = bucket_offset.size();
    auto low = std::lower_bound(bucket_offset.begin(),bucket_offset.end(),n);
    if(low != bucket_offset.end()){
        pos = std::distance(bucket_offset.begin(),low);
    }
    buckets.at(pos)++;
    _count++;
    _sample_sum += n;
}
void new_offsets(int size){
    bucket_offset.resize(eize);
    if(size == 0){
        return;
    }
    int64_t last = 1;
    bucket_offset[0] = last;
    for(int i = 1; i < size; i++){
        int64_t next = last + 1;
        bucket_offset[i] = next;
        last = next;
    }
}
int main(int argc,char **argv){
    
}