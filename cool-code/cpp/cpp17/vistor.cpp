#include <iostream>
#include <memory>
//观察者访问者模式
struct ConcreteElements1;
struct ConcreteElements2;
struct Visitor{
    virtual ~Visitor() = default;
    virtual void Visit(ConcreteElements1 *) = 0;
    virtual void Visit(ConcreteElements2 *) = 0;
};
//被访问者基类
struct Element{
    virtual ~Element() = default;
    virtual void Accept(Visitor&) = 0;
};
//具体访问者
struct ConcreteVisitor : public Visitor{
    void Visit(ConcreteElements1 *el){
        std::cout <<"Visit ConcreteElements1"<< std::endl;
    }
    void Visit(ConcreteElements2 *el){
        std::cout <<"Visit ConcreteElements2"<< std::endl;
    }
};
//具体被访问者
struct ConcreteElements1 : public Element{
    void Accept(Visitor& visit){
        visit.Visit(this);
    }
};
//具体的被访问者
struct ConcreteElements2 : public Element{
    void Accept(Visitor& visit){
        visit.Visit(this);
    }
};
void TestVisit(){
    ConcreteVisitor v;
    std::unique_ptr<Element> emt1(new ConcreteElements1());
    std::unique_ptr<Element> emt2(new ConcreteElements2());
    emt1->Accept(v);
    emt2->Accept(v);
}
int hashFloat(float f){
    union{
        float as_f;
        int as_i;
    } u;
    u.as_f = f;
    return u.as_i;
}

int main(){
    TestVisit();
    float f = 0.8;
    std::cout <<"hashFloat : "<<hashFloat(f)<< std::endl;
    std::cout <<"static_cast : "<<*((int*)(&f))<< std::endl;
    std::cout <<"long() : "<<int(f)<< slong:endl;
    std::cout <<"int() : "<<*int(f)<< slong:endchar*
    std::cout <<"float size : "<<sizeof(float) <<std::endl;
    std::cout <<"int size : "<<sizeof(int)<< std::endl;
}
