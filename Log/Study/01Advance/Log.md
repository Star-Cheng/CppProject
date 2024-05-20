# C++核心编程

## 1. 内存分区模型

+ 代码区: 存放代码, 特点: 共享, 可读
+ 全局区: 全局变量、静态变量、全局const常量和字符串常量存放于此, 该区域的数据在程序结束之后由操作系统释放
+ 栈区: 有编译器自动分配释放, 存放函数的参数值, 局部变量, 不要返回局部变量的地址
+ 堆区: 有程序员分配释放, 若程序员不是放， 程序结束时由操作系统回收, 利用new开辟堆区空间, 利用delete释放堆区空间

## 2. 引用

### 2.1 引用的基本使用

1. 作用: 给变量起别名
2. 语法: 数据类型 &别名 = 原名

```C++
#include <iostream>
using namespace std;
int main()
{
    int a = 10;
    int &b = a;
    cout << a << endl;
    cout << b << endl;
    b = 20;
    cout << a << endl;
    cout << b << endl;
    return 0;
}
```

### 2.2 引用的注意事项

 1. 引用必须要初始化: int &b; // 错误
 2. 引用在初始化后, 不可以改变

### 2.3 引用做函数参数

1. 作用: 函数传参时, 可以利用引用的技术让形参修饰实参
2. 优点: 可以简化指针修改实参

```C++
#include <iostream>
using namespace std;
// 交换函数
// 1. 值传递
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
// 2. 地址传递
void swap_add(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// 3. 引用传递
void swap_ref(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
int main()
{
    int a = 10;
    int b = 20;
    swap(a, b); // 值传递, 形参不会修饰实参
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    swap_add(&a, &b); // 地址传递, 形参会修饰实参
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    swap_ref(a, b); // 引用传递, 形参会修饰实参
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    return 0;
}
```

### 2.4 引用做函数返回值

1. 作用: 减少函数返回值个数, 减少函数调用
2. 注意: 不要返回局部变量引用
3. 函数调用作为左值

```C++
#include <iostream>
using namespace std;
// 1. 不要返回局部变量的引用
int &test01()
{
    int a = 10;
    return a; // error
}
// 2. 函数的调用可以作为左值
int &test02()
{
    static int a = 10;
    return a;
}
int main()
{
    // int &ref = test01();
    // cout << ref << endl;  // error

    int &ref2 = test02();
    cout << "ref2 = " << ref2 << endl;
    cout << "ref2 = " << ref2 << endl;
    test02() = 1000;  // 如果函数的返回值是引用, 这个函数调用可以作为左
    cout << "ref2 = " << ref2 << endl;
    cout << "ref2 = " << ref2 << endl;
    return 0;
}
```

### 2.5 引用的本质

1. 本质引用的本质在C++内部实现是一个指针常量

```C++
#include <iostream>
using namespace std;
int main()
{
    int a = 10;
    int &ref = a;
    // 自动转换为 int * const ref = &a;
    ref = 20;
    cout << "a: " << a << endl;
    cout << "ref: " << ref << endl;
}
```

### 2.6 常量引用

1. 作用: 常量引用主要用来修饰形参, 防止误操作

```C++
#include <iostream>
using namespace std;
void showValue(int &a)
{
    cout << "a = " << a << endl;
    a = 1000;
}
void showValue2(const int &a)
{
    cout << "a = " << a << endl;
    // a = 1000;  // 加入const之后值变为可读, 不可以修改
}
int main()
{
    int a = 10;
    int &ref = a;         // 引用必须引一块合法的内存空间
    const int &ref2 = 10; // 加上const: int temp=10; const int & ref2=temp;
    // ref2 = 10;  // 加入const之后值变为可读, 不可以修改
    showValue2(a);
    cout << "a = " << a << endl;
    showValue(a);
    cout << "a = " << a << endl;
}
```

## 3. 函数提高

### 3.1 函数默认参数

#### 3.1.1 默认参数注意事项

1. 如果某个位置已经有了默认参数, 那么从这个位置往后, 从左到右必须要有默认值
2. 函数声明和函数实现只能有一个有默认参数

### 3.2 函数占位参数

```C++
void func(int a, int = 10) // 占位参数也可以有默认参数
{
    cout << "this is func" << endl;
}
```

### 3.3 函数重载

#### 3.3.1 函数重载概述

1. 作用: 函数名可以相同, 提高复用性
2. 重载条件: 函数名相同, 参数不同, 函数体相同
3. 注意事项: 函数的返回值不可以作为函数重载条件

```C++
#include <iostream>
using namespace std;
// 函数重载的满足条件
// 1. 同一个作用域下
// 2. 函数名称相同
// 3. 函数的参数类型不同, 或者个数不同, 或者顺序不同

void func()
{
    cout << "Hello World" << endl;
}
void func(int a, double b)
{
    cout << "int double World!!!" << endl;
}
void func(double a, int b)
{
    cout << "double int World!!!" << endl;
}

int main()
{
    func();
    func(10, 3.14);
    func(10., 3);
}
```

#### 3.3.2 函数重载的注意事项

1. 引用作为函数重载条件
2. 函数重载碰到默认参数

```C++
#include <iostream>
using namespace std;
// 函数重在的注意事项
// 1. 引用作为重载的条件
void func(int &a)
{
    cout << "func(int &a)" << endl;
}
void func(const int &a)
{
    cout << "func(const int &a" << endl;
}
// 2. 函数重载碰到默认参数
void func2(int a, int b = 10)
{
    cout << "func2(int a, int b =10)" << endl;
}
void func2(int a)
{
    cout << "func2(int a)" << endl;
}

int main()
{
    int a = 10;
    func(a);  // 调用func(int &a)
    func(10); // 调用func(const int &a)
    // func2(10);  // error, 函数重载碰到默认参数
}
```

## 4. 类和对象

### 4.1 封装

#### 4.1.1 封装的意义

1. 将属性和行为作为一个整体
2. 将属性和行为加以权限控制
    1. public : 公有权限, 成员在类内可以访问, 类外可以访问
    2. private : 私有权限, 类内可以访问, 类外不可以访问, 儿子不可以访问父亲的私有的内容
    3. protected : 保护权限, 类内可以访问, 类外不可以访问, 儿子也可以访问父亲保护的内容

```C++
#include <iostream>
using namespace std;
// 设计一个圆类, 求圆的周长
const double pi = 3.14;
// class代表设计一个类
class Circle
{
    // 访问权限
public: // 公共权限
    // 类中的属性和行为统一称为成员
    // 属性: 成员属性、成员变量
    double radius; // 半径
    // 行为: 成员函数、成员方法
    double getArea()
    {
        return pi * radius * radius;
    }
    double getPerimeter()
    {
        return 2 * pi * radius;
    }
};
int main()
{
    // 通过圆类, 创建具体的圆
    Circle c1;
    c1.radius = 10;
    cout << "圆的面积是:" << c1.getArea() << endl;
    cout << "圆的周长是:" << c1.getPerimeter() << endl;
    return 0;
}
```

```C++
#include <iostream>
using namespace std;
#include <string>
// class代表设计一个类
class Person
{
public: // 公共权限
    string name;

protected: // 保护权限
    string car;

private: // 私有权限
    int password;

public:
    void func()
    {
        name = "xingming";
        car = "xiaomi su7";
        password = 123456;
        cout << "name: " << name << endl;
        cout << "car: " << car << endl;
        cout << "password: " << password << endl;
    }
};
int main()
{
    Person p1;
    p1.name = "xiaoming";
    // p1.car = "xiaomi su7";  // 保护权限内容, 在类外访问不到
    // p1.password = 123456;  // 私有权限内容, 在类外访问不到
    p1.func();
    return 0;
}
```

#### 4.1.2 struct和class的区别

1. struct默认权限为公共
2. class默认权限为私有

```C++
#include <iostream>
using namespace std;
#include <string>
class c1
{
    int m_a; // 默认权限是私有
};
struct c2
{
    int m_a; // 默认权限是公共
};
int main()
{
    // struct和class的区别
    // 1. struct默认权限为公共
    // 2. class默认权限为私有
    c1 c1;
    c2 c2;
    // c1.m_a = 10;  // 错误
    c2.m_a = 10; // 正确
    return 0;
}
```

#### 4.1.3 成员属性设置为私有

1. 将所有成员属性设置私有, 可以自己控制读写权限
2. 对于写权限, 我们可以检测数据的有效性

```C++
#include <iostream>
using namespace std;
#include <string>
// 成员属性设置为私有
// 1. 可以自己控制读写权限
// 2. 对于写可以检测数据有效性
class Person
{
private:
    string m_Name;  // 可读可写
    int m_Age = 18; // 只读
    string m_ido;   // 只写
public:
    void setName(string name)
    {
        m_Name = name;
    }
    string getName()
    {
        return m_Name;
    }
    int getAge()
    {
        return m_Age;
    }
    void setido(string ido)
    {
        m_ido = ido;
    }
};
int main()
{
    Person p;
    p.setName("xiaoming");
    p.setido("xiaohong");
    cout << "name: " << p.getName() << endl;
    cout << "age: " << p.getAge() << endl;
}
```

### 4.2 对象的初始化和清理

#### 4.2.1 构造函数和析构函数

1. 构造函数: 对象创建时调用
    1. 构造函数, 没有返回值也不写void
    2. 函数名称与类名相同
    3. 构造函数可以有参数, 因此可以发生重载
    4. 程序在调用对象时候会自动调用构造, 无需手动调用, 而且只会调用一次
2. 析构函数: 对象销毁时调用
    1. 析构函数, 没有返回值也不写void
    2. 函数名称与类名相同, 前面加~
    3. 析构函数没有参数, 因此不能发生重载
    4. 程序在销毁对象时候会自动调用析构, 无需手动调用, 而且只会调用一次

```C++
#include <iostream>
using namespace std;
// 对象的初始化和清理
// 1. 构造函数 进行初始化操作
class Person
{
public:
    // 1. 构造函数
    // 构造函数, 没有返回值也不写void
    // 函数名称与类名相同
    // 构造函数可以有参数, 因此可以发生重载
    // 程序在调用对象时候会自动调用构造, 无需手动调用, 而且只会调用一次
    Person()
    {
        cout << "Person的构造函数" << endl;
    }
    // 2. 析构函数
    // 析构函数, 没有返回值也不写void
    // 函数名称与类名相同, 前面加~
    // 析构函数没有参数, 因此不能发生重载
    // 程序在销毁对象时候会自动调用析构, 无需手动调用, 而且只会调用一次
    ~Person()
    {
        cout << "Person的析构函数" << endl;
    }
};

int main()
{
    Person p;
    return 0;
}
```

#### 4.2.2 构造函数的分类及作用

1. 分类方式
    1. 无参构造函数
    2. 有参构造函数
2. 三种调用方式
    1. 括号法
    2. 显示法
    3. 隐式转换法

```C++
#include <iostream>
using namespace std;
// 1. 构造函数的分类及调用
// 分类: 无参构造(默认构造)和有参构造

class Person
{
public:
    Person() // 1. 构造函数
    {
        cout << "Person的无参构造函数" << endl;
    }
    Person(int a) // 2. 有参构造函数
    {
        age = a;
        cout << "Person的有参构造函数" << endl;
    }
    Person(const Person &p) // 3. 拷贝构造函数
    {
        age = p.age;
        cout << "Person的拷贝构造函数" << endl;
    }
    ~Person() // 4. 析构函数
    {
        cout << "Person的析构函数" << endl;
    }
    int age;
};
// 调用
void test01()
{
    // 1. 括号法
    Person p1;     // 默认构造函数调用
    Person p2(10); // 有参构造函数调用
    Person p3(p2); // 拷贝构造函数调用
    // 注意事项: 调用默认构造函数时, 不要加()

    // 2. 显示法
    Person p4 = Person();   // 无参构造
    Person p5 = Person(10); // 有参构造
    Person p6 = p5;         // 拷贝构造
    // 注意事项1
    Person(10); // 匿名对象, 特点: 当前行执行结束后系统会立即回收掉匿名对象
    // 注意事项2: 不要利用拷贝构造函数来初始化匿名对象
    Person(p7); // error, 编译器会认为Person(p7) == Person p7;

    // 3. 隐式转换法
    Person p8 = 10; // 相当于Person p8 = Person(10);
    Person p9 = p8; // 相当于Person p9 = Person(p8);
}

int main()
{
    test01();
    return 0;
}
```

#### 4.2.3 拷贝构造函数调用时机

1. 拷贝构造函数调用时机的三种情况
    1. 使用一个已经创建完毕的对象来初始化一个新对象
    2. 值传递的方式给函数参数传值
    3. 以值方式返回局部对象

```C++
#include <iostream>
using namespace std;
// 拷贝构造函数的调用时机

class Person
{
public:
    Person() // 1. 构造函数
    {
        cout << "Person的无参构造函数" << endl;
    }
    Person(int a) // 2. 有参构造函数
    {
        age = a;
        cout << "Person的有参构造函数" << endl;
    }
    Person(const Person &p) // 3. 拷贝构造函数
    {
        age = p.age;
        cout << "Person的拷贝构造函数" << endl;
    }
    ~Person() // 4. 析构函数
    {
        cout << "Person的析构函数" << endl;
    }
    int age;
};
// 1. 使用一个已经创建完毕的对象来初始化一个新对象
void test01()
{
    Person p1(20);
    Person p2(p1);
    cout << "p2 age: " << p2.age << endl;
}
// 2. 值传递的方式给函数参数传值
void doWork(Person p)
{
    p.age = 1000;
}
void test02()
{
    Person p;
    doWork(p);
}
// 3. 以值方式返回局部对象
Person dowWork2()
{
    Person p;
    cout << &p << endl;
    return Person(p);
}
void test03()
{
    Person p = dowWork2();
    cout << &p << endl;
}
int main()
{
    test01();
    test02();
    test03();

    return 0;
}
```

#### 4.2.4 构造函数调用规则

+ 默认情况下, C++编译器至少给一个类添加3个函数
    1. 默认构造函数(无参, 函数体为空)
    2. 默认析构函数(无参, 函数体为空)
    3. 默认拷贝构造函数, 对属性进行值拷贝

+ 拷贝规则
    1. 如果用户定义了有参构造函数, C++不会再提供无参构造函数, 但会提供拷贝构造函数
    2. 如果用户定义了拷贝构造函数, C++不会再提供默认拷贝构造函数

```C++
#include <iostream>
using namespace std;
// 构造函数的调用规则
// 1. 创建一个类, C++编译器会给每一个类都添加至少3个函数
// 默认构造函数(无参, 函数体为空)
// 默认析构函数(无参, 函数体为空)
// 默认拷贝构造函数, 对属性进行值拷贝

// 2. 如果用户定义了有参构造函数, C++不会再提供无参构造函数, 但会提供拷贝构造函数
// 3. 如果用户定义了拷贝构造函数, C++不会再提供默认拷贝构造函数
class Person
{
public:
    Person()
    {
        cout << "默认构造函数" << endl;
    }
    Person(int a)
    {
        cout << "有参构造函数" << endl;
        age = a;
    }
    // Person(const Person &p)
    // {
    //     age = p.age;
    //     cout << "拷贝构造函数" << endl;
    // }
    ~Person()
    {
        cout << "析构函数" << endl;
    }
    int age;
};
void test01()
{
    Person p1;
    p1.age = 10;
    Person p2(p1);
    cout << "p2.age = " << p2.age << endl;
}

void test02()
{
    Person p(18);
    Person p2(p);
    cout << "p.age = " << p.age << endl;
    cout << "p2.age = " << p2.age << endl;
}
int main()
{
    test02();
    return 0;
}
```

#### 4.2.5 深拷贝与浅拷贝

1. 浅拷贝: 简单的复制拷贝
2. 深拷贝: 在读取重新申请空间, 进行拷贝操作

```C++
#include <iostream>
using namespace std;
// 深拷贝与浅拷贝
class Person
{
public:
    Person()
    {
        cout << "Person默认构造函数" << endl;
    }
    Person(int age, int height)
    {
        m_Age = age;
        m_Height = new int(height);
        cout << "Person有参构造函数" << endl;
    }
    Person(const Person &p)
    {
        m_Age = p.m_Age;
        m_Height = p.m_Height;           // 浅拷贝, 编译器默认的操作
        m_Height = new int(*p.m_Height); // 在堆区开辟数据做拷贝操作
        cout << "Person拷贝构造函数" << endl;
    }
    ~Person()
    {
        // 析构代码, 将堆区开辟数据做释放操作
        if (m_Height != NULL)
        {
            delete m_Height;
            m_Height = NULL;
        }
        cout << "Person析构函数" << endl;
    }
    int m_Age;
    int *m_Height;
};
void test01()
{
    Person p1(18, 185);
    cout << "p1.m_Age = " << p1.m_Age << " p1.m_Height = " << *p1.m_Height << endl;
    Person p2(p1);
    cout << "p2.m_Age = " << p2.m_Age << " p2.m_Height = " << *p2.m_Height << endl;
}
int main()
{
    test01();
    return 0;
}
```

#### 4.2.6 初始化列表

+ 语法: 构造函数(): : 属性1(值1), 属性2(值2), 属性3(值3) ... {}

```C++
#include <iostream>
using namespace std;
// 初始化列表
class Person
{
public:
    // Person(int a, int b, int c) // 传统初始化操作
    // {
    //     m_A = a;
    //     m_B = b;
    //     m_C = c;
    // }
    
    Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c) // 列表初始化属性
    {
    }
    int m_A;
    int m_B;
    int m_C;
};
void test01()
{
    Person p(10, 20, 30);
    cout << p.m_A << endl;
    cout << p.m_B << endl;
    cout << p.m_C << endl;
}
int main()
{
    test01();
    return 0;
}
```

#### 4.2.7 类对象作为类成员

```C++
#include <iostream>
using namespace std;
#include <string>
// 初始化列表
class Phone
{
public:
    Phone(string pName)
    {
        m_PName = pName;
        cout << "Phone的构造函数调用" << endl;
    }
    ~Phone()
    {
        cout << "Phone的析构函数调用" << endl;
    }
    string m_PName;
};
class Person
{
public:
    string name;
    Phone m_phone;
    Person(string name, string phone) : name(name), m_phone(phone)
    {
        cout << "Person的构造函数调用" << endl;
    }
    ~Person()
    {
        cout << "Person的析构函数调用" << endl;
    }
};
// 1. 当其他类对象作为本类成员, 构造时先构造类对象, 再构造自身
// 2. 析构时先析构自身, 再析构类对象

void test01()
{
    Person p("张三", "iphone");
    cout << p.name << ":" << p.m_phone.m_PName << endl;
}
int main()
{
    test01();
    return 0;
}
```

### 4.2.8 静态成员

1. 静态成员变量
    1. 所有对象共享一份数据
    2. 在编译阶段分配内存
    3. 类内声明, 类外初始化

2. 静态成员函数
    1. 所有对象共享一个函数
    2. 静态成员函数只能访问静态成员变量

```C++
#include <iostream>
using namespace std;

// 静态成员变量
class Person
{
public:
    // 1. 所有对象共享一份数据
    // 2. 在编译阶段分配内存
    // 3. 类内声明, 类外初始化
    static int m_A;

private:
    static int m_B;
};
int Person::m_A = 100;
int Person::m_B = 200;
void test01()
{
    Person p;
    cout << "p.m_A: " << p.m_A << endl;
    Person p2;
    p2.m_A = 200;
    cout << "p2.m_A: " << p2.m_A << endl;
}
void test02()
{
    // 静态成员变量不属于某一个对象上, 所有对象都共享同一份数据, 因此静态成员变量有两种访问方式
    // 1. 通过对象进行访问
    Person p3;
    cout << "p3.m_A: " << p3.m_A << endl;
    // 2. 通过类名进行访问
    cout << "Person::m_A: " << Person::m_A << endl;
    // 3. 静态成员变量不能通过对象访问
    // cout << "p3.m_B: " << p3.m_B << endl; // error 静态成员变量不能通过对象访问
}
int main()
{
    test01();
    test02();
    return 0;
}
```

```C++
#include <iostream>
using namespace std;

// 静态成员函数
// 1. 所有对象共享一个函数
// 2. 静态成员函数只能访问静态成员变量
class Person
{
public:
    static void func() // 静态成员函数
    {
        m_A = 100; // 静态成员函数可以访问静态成员变量
        // m_B = 200; // 静态成员函数不能访问非静态成员变量
        cout << "static void func调用" << endl;
    }
    static int m_A;
    int m_B;
    // 静态成员函数也是有访问权限的
private:
    static void func2()
    {
        cout << "static void func2调用" << endl;
    }
};
int Person::m_A = 10;
void test01()
{
    // 1. 通过对象访问
    Person p1;
    p1.func();
    cout << p1.m_A << endl;
    // 2. 通过类名访问
    Person::func();
    // Person::func2(); // 静态成员函数不能通过对象访问
}

int main()
{
    test01();
    return 0;
}
```

### 4.3 C++对象模型和this指针

#### 4.3.1 成员变量和成员函数分开存储

+ 只有非静态成员变量才属于类的对象上

```C++

```