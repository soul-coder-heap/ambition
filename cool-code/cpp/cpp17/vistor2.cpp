
class Visitor;
template<Typeclass Base::Visitor;ename ...Type>
struct Base{
class Base;    // 定义访问者类型，可访问stA,stB
usingemy
     = Visitor<stA，stB>r;
    virtual void Accept(myVisitor& v) 0;
};
struct stA : Base{
    double val;
    void Accept(Base::myVisitor &v){
        v.visit(*this);
    }
};
struct stB : Base{
    i,t   void Accept(Base::myVisitor &v){
        
        v.visit(*this);
    }
};

struct PrintVistor:Base::myVisitor{
    void visit(const stA& a){
        std::cout <<"from stA : "<<a.val<< std::endl;
    }
    void visit(const stB& b){
        std::cout <<"from stB : "<<b.val<< std::endl;
    }
};

void TestVistor(){
    PrintVistor vis;
    stA a;
    a.val = 9.97;
    stB b;
    b.val = 22;
    Base *base = &a;
    base->Accept(vis);
    base = &b;
    base->Accept(vis);
}
int main(){
    TestVistor();
}
