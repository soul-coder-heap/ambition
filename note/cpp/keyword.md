## const

* 修饰变量
* 修饰指针，pointer to const/const pointer
* 修饰引用
* 修饰成员函数

## static
* 修饰普通变量，改变变量的存储区域和生命期，全局区(静态区),main之前分配空间
* 修饰普通函数，函数可见范围， python _func 作用雷同
* 修饰成员变量，属于类所有的对象
* 修饰成员函数，属于类所有，改函数内只能访问类静态成员
## volatile
* 类型修饰符，编译器不对改关键字修饰的类型进行优化
* 访问都从内存中取出
* const、指针可以被 volatile 修饰
## sizeof()
* 空类 1
* 空类含有virtual函数，sizeof(void*) =  4/8
* sizeof 对数组，数组大小
* sizeof 对指针，指针大小
## \#pragma pack(n)
* 设定结构体、联合体以n字节对齐

    ```
    #pragma pack(push)  // 保存对齐状态
    #pragma pack(4)     // 设定为 4 字节对齐

    struct test
    {
        char m1;
        double m4;
        int m3;
    };

    #pragma pack(pop)   // 恢复对齐状态
    ```
## 位域
* 数据成员内包含二进制位
* 位域与内存有关

## extern "C"
* 被 extern "C" 包含的函数或者变量按照C语言方式编译链接
* 使C++按照C的方式处理代码，避免C++因符号修饰不能链接C库

    ```
    #ifdef __cplusplus
    extern "C" {
    #endif

    void *memset(void *, int, size_t);

    #ifdef __cplusplus
    }
    #endif
   ```
## struct、typedef struct
* typedef struct Student S;

## struct、class
* s数据结构实现体，c对象实现体
* 继承权限\数据权限 struct 默认是 public ,class private

## union
* 联合是节省空间得一种特殊类，可以有多个数据成员，但是任意时刻只有一个有值
* 默认权限是public
* 可以又构造析构函数
* 不能有引用类型，不能继承/被继承，不能有虚函数

## explicit(显式关键字)
* explicit 修饰构造函数时，可以防止隐式转换和复制初始化
* explicit 修饰转换函数时，可以防止隐式转换

    ```
    struct B
    {
	    explicit B(int) {}
	    explicit operator bool() const { return true; }
    };

    ```

## friend
* 能访问私有成员
* 破坏封装性
* 友元关系不可传递
* 友元关系单向性

## using 
* 引入命名空间
* 定义类型别名 `typedef int I; using I = int;`

## ::范围解析
* 全局作用域符
* 类作用域符
* 命名空间

## 成员初始化列表
* 更高效：少了一次调用默认构造函数的过程。
* 有些场合必须要用初始化列表：
    * 常量成员，因为常量只能初始化不能赋值，所以必须放在初始化列表里面
    * 引用类型，引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面
    * 没有默认构造函数的类类型，因为使用初始化列表可以不必调用默认构造函数来初始化    

## initializer_list
* 用化括号初始化一个对象，接受的参数应该是 initializer_list

## virtual 函数位置
* 虚函数表指针，属于对象实例。new 构造的堆区，实例化的在栈区
* 虚函数表在只读数据段(.rodata)，常量区
* 虚函数代码在代码段(.text), 代码区

## 只能在堆/栈创建对象
* 私有化析构，只能在堆上
* 私有化构造和析构函数，只能在栈
