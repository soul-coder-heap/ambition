#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
std::string _removeTab(const std::string &str) {
    std::string strCopy = str;
    {
        auto begin = std::chrono::system_clock::now();
        strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\t'), strCopy.end());
        strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\r'), strCopy.end());
        strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\n'), strCopy.end());
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - begin).count()<<"ns\t size : ";
        std::cout <<strCopy.length()<< std::endl;
    }
    std::string strCopy1(str.length(), '\0');
    {
        auto begin = std::chrono::system_clock::now();
        size_t j = 0;
        for(size_t i = 0; i < str.size(); i++ ){
            const auto &elem = str[i];
            if(elem != '\r' && elem != '\t' && elem != '\n'){
                strCopy1[j++] = elem;        
            }
        }
        strCopy1.resize(j);
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - begin).count()<<"ns\t size : ";
        std::cout <<strCopy1.length()<< std::endl;
    }
    std::cout <<"compare : "<<int(strCopy1.compare(strCopy)) <<"\n";
    return strCopy1;
}
int main (){
    std::string s1 = "asdasdsadaderaaaaaaaaaaaaASDDDDDDDDDDDD\raa\taaaaaa\rawergffffffff34563645bb7v54777777777777777777777777777777777777777777777777777777777777777777777777777\r\t\n\t\n\r\t\t\tt\ttt77777777777777777777777777777777777aasdsadas\tSDADADSAsaDDDDRDASSD\raSDWAda\nghbdghdfghbdfghdfghd";
    std::string s2 = "disssssssssssssssss\tssss\tsssssssssssssss\tadasd\rasad\n12334";
    for(int i = 0; i < 1000; i++){
        s1 += s2;
    }
    _removeTab(s1);
}
