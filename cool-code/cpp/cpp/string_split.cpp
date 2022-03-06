#include <iostream>
#include <string>
#include <algorithm>
#include <string_view>
#include <vector>
int split(const std::string &str, const std::string &delims, std::vector<std::string> *output);
std::vector<std::string> split(const std::string &str, const std::string &delims = " ");

std::vector<std::string> split(const std::string &str, const std::string &delims) {
    std::vector<std::string> output;
    split(str, delims, &output);
    return std::move(output);
}
// uses string::find_first_of
int split(const std::string &str, const std::string &delims, std::vector<std::string> *output) {
    // output.reserve(str.length() / 4);
    size_t first = 0;
    while (first < str.size()) {
        const auto second = str.find_first_of(delims, first);
        if (first != second) {
            output->emplace_back(str.data() + first,
                                 str.data() + (second == std::string::npos ? str.size() : second));
        }
        if (second == std::string::npos)
            break;
        first = second + 1;
    }
    return output->size();
}

int main(){
    std::vector<std::string> vec;
    std::string str = "hello world, I love you, you are a pig";
    std::string delim = " ";
    vec = split(str,delim);
    for(const auto &a:vec){
        std::cout <<a<< std::endl;       
    }
}
