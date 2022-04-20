#include <iostream>

class Singleton
{
public:
    static Singleton& getInstance() // 单例模式
    {
        static Singleton instance;
        return instance;
    }
private:
    Singleton() {}  // 私有构造函数
    Singleton(const Singleton&);  // 私有拷贝构造函数
    Singleton& operator=(const Singleton&);  // 私有赋值运算符
};

int main()
{
    Singleton& s1 = Singleton::getInstance();
    std::cout << "s1: " << &s1 << std::endl;

    Singleton& s2 = Singleton::getInstance();
    std::cout << "s2: " << &s2 << std::endl;

    return 0;
}