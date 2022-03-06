export module demo.cppcon;
namespace CppCon{
    auto GetSay(){
        return "welecome to cppcon 2019!";
    }
    export auto GetHelp(){
        return GetSay();
    }
}
