#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

int split(const std::string &str,const std::string &delims,std::vector<std::string> *output){
    size_t first = 0;
    while(first != str.size()){
        const auto second = str.find_first_of(delims,first);
        if(first != second){
            output->emplace_back(str.data() + first,
                                 str.data() + (second == std::string::npos ? str.size() : second));
            if(second == std::string::npos)
                break;
        }
        first = second + 1;       
    }
    return output->size();
}


std::vector<std::string> split(const std::string &str){
    std::vector<std::string> output;
    split(str,delims,&output);
    return std::move(output);
}
int main(){
    std::cout <<"dd";
}
