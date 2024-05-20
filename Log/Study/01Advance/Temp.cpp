#include <iostream>
using namespace std;
#include <string>

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