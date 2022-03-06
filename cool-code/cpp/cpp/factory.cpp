#include <iostream>
#include <string>
#include <memory>
#include <map>
class Shoes
{
public:
    virtual void Show() = 0;
    virtual ~Shoes() {
        std::cout <<"基类扔掉破鞋"<< std::endl;
    }
};

class NiKeShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
    }
    ~NiKeShoes(){
        std::cout <<"扔掉耐克"<< std::endl;
    }
};

class Clothe
{
public:
    virtual void Show() = 0;
    virtual ~Clothe() {
        std::cout <<"积累扔掉衣服"<< std::endl;
    }
};

class UniqloClothe : public Clothe
{
public:
    void Show()
    {
        std::cout << "我是优衣库衣服，我的广告语：I am Uniqlo" << std::endl;
    }
    ~UniqloClothe(){
        std::cout <<"扔掉优衣库衣服"<< std::endl;
    }
};

// 抽象模板工厂类
// 模板参数：AbstractProduct_t 产品抽象类
template <class AbstractProduct_t>
class AbstractFactory
{
public:
    virtual AbstractProduct_t *CreateProduct() = 0;
    virtual ~AbstractFactory() {}
};

// 具体模板工厂类
// 模板参数：AbstractProduct_t 产品抽象类，ConcreteProduct_t 产品具体类
template <class AbstractProduct_t, class ConcreteProduct_t>
class ConcreteFactory : public AbstractFactory<AbstractProduct_t>
{
public:
    AbstractProduct_t *CreateProduct()
    {
        return new ConcreteProduct_t();
    }
};

// 基类，产品注册模板接口类
// 模板参数 ProductType_t 表示的类是产品抽象类
template <class ProductType_t>
class IProductRegistrar
{
public:
   // 获取产品对象抽象接口
   virtual ProductType_t *CreateProduct() = 0;

protected:
   // 禁止外部构造和虚构, 子类的"内部"的其他函数可以调用
   IProductRegistrar() {}
   virtual ~IProductRegistrar() {}

private:
   // 禁止外部拷贝和赋值操作
   IProductRegistrar(const IProductRegistrar &);
   const IProductRegistrar &operator=(const IProductRegistrar &);
};

// 工厂模板类，用于获取和注册产品对象
// 模板参数 ProductType_t 表示的类是产品抽象类
template <class ProductType_t>
class ProductFactory
{
public:
   // 获取工厂单例，工厂的实例是唯一的
   static ProductFactory<ProductType_t> &Instance()
   {
      static ProductFactory<ProductType_t> instance;
      return instance;
   }
   void RegisterProduct(IProductRegistrar<ProductType_t> *registrar, std::string name)
   {
      m_ProductRegistry[name] = registrar;
   }
   ProductType_t *GetProduct(std::string name)
   {
      // 从map找到已经注册过的产品，并返回产品对象
      if (m_ProductRegistry.find(name) != m_ProductRegistry.end())
      {
         return m_ProductRegistry[name]->CreateProduct();
      }
      std::cerr << "No product found for " << name << std::endl;
      return NULL;
   }
private:
   ProductFactory()=default;
   ~ProductFactory()=default;
   ProductFactory(const ProductFactory &)=default;

private:
   // 保存注册过的产品，key:产品名字 , value:产品类型
   std::map<std::string, IProductRegistrar<ProductType_t> *> m_ProductRegistry;
};

// 产品注册模板类，用于创建具体产品和从工厂里注册产品
// 模板参数 ProductType_t 表示的类是产品抽象类（基类），ProductImpl_t 表示的类是具体产品（产品种类的子类）
template <class ProductType_t, class ProductImpl_t>
class ProductRegistrar : public IProductRegistrar<ProductType_t>
{
public:
   // 构造函数，用于注册产品到工厂，只能显示调用
   explicit ProductRegistrar(std::string name)
   {
      ProductFactory<ProductType_t>::Instance().RegisterProduct(this, name);
   }

   ProductType_t *CreateProduct()
   {
      return new ProductImpl_t();
   }
};

int main()
{
    /*
    std::unique_ptr<ConcreteFactory<Shoes,NiKeShoes>> nikeFactory(new ConcreteFactory<Shoes,NiKeShoes>);
    std::shared_ptr<Shoes> pNiKeShoes;
    pNiKeShoes.reset(nikeFactory->CreateProduct());
    pNiKeShoes->Show();

    std::unique_ptr<ConcreteFactory<Clothe, UniqloClothe>> uniqloFactory(new ConcreteFactory<Clothe,UniqloClothe>);
    std::shared_ptr<Clothe> pUniqloClothe;
    pUniqloClothe.reset(uniqloFactory->CreateProduct());
    pUniqloClothe->Show();
   */
    // 预先注册，需要时直接通过工厂获取
    ProductRegistrar<Shoes,NiKeShoes> pNiKeShoes("NIKE");
    ProductRegistrar<Clothe,UniqloClothe> pUniqloClothe("UNIQLO");

    // shoe
    std::shared_ptr<Shoes> pnshoe;
    pnshoe.reset(ProductFactory<Shoes>::Instance().GetProduct("NIKE"));
    pnshoe->Show();

    return 0;
}

