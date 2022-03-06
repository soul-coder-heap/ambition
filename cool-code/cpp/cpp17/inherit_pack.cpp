#include <iostream>
//正数序列定义
template <int...>
struct IndexSeq{};

//继承方式，开始展开参数包
template<int N,int... Indexes>
struct MakeIndexes : MakeIndexes<N-1,N-1,Indexes...>{};

//模板特化，中止展开参数包的条件
template<int... Indexes>
struct MakeIndexes<0,Indexes...>{
    typedef IndexSeq<Indexes...> type;
};
namespace oo{
    template<int...>
    struct IndexSeq{};

    template<int N,int ... Indexes>
    struct MakeIndexes{
        using type = MakeIndexes<N-1,N-1,Indexes...>::type;
    };
    template<int... Indexes>
    struct MakeIndexes<0,Indexes>
    {
        using type = IndexSeq<Indexes...>;
    };
    template<int ... Indexes,>
};
int main(){
    using T = MakeIndexes<3>::type;
    std::cout <<typeid(T).name()<< std::endl;
    return 0;
}
