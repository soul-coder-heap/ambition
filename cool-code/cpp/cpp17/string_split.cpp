#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string_view>

std::vector<std::string> split(const std::string &,const std::string &);
int split(const std::string &,const std::string &,std::vector<std::string> *);


std::vector<std::string> split(const std::string &str,const std::string &delims){
    std::vector<std::string> output;
    split(str,delims,&output);
    return std::move(output);
}

//use string::find_first_of
int split(const std::string &str,const std::string &delims,std::vector<std::string> *output){
    std::size_t first = 0;
    while(first < str.size()) {
        const auto second = str.find_first_of(delims,first); //find first of delims pos
        if(first != second) {
            output->emplace_back(str.data() + first,
                                 str.data() + (second == std::string::npos ? str.size() : second));   
        }
        if(second == std::string::npos){
            break;
        }
        first = second + 1;
    }
    return output->size();
}
/*
std::vector<std::string_view> split(std::string_view str,std::string_view delims,bool empty_field){
    std::vector<std::string_view> output;
    split(std::move(str),std::move(delims),empty_field,&output);
    return output;
}
*/

int main(){
    std::string ml = "12 dfsaf efar errgaga waefaw war  awe eawae ea  ra ra";
    auto output = split(ml," ");
    std::cout <<ml<<"\n";
    int i = 1;
    for(const auto &m:output){
        std::cout <<i<<". "<<m<< "  lenth = "<<m.length()<<"\n";
        i++;
    }
    std::cout <<"output size : ";
    std::cout << output.size() << std::endl;
}
