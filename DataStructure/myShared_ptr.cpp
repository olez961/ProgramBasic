#include <iostream>

template <typename T>
class myShared_ptr
{
public:
    myShared_ptr(T* p = nullptr) : _p(p), _ref(new int(1))  // 初始化构造函数
    {
        std::cout << "myShared_ptr()" << std::endl; // 构造函数输出
    }

    myShared_ptr(const myShared_ptr& rhs) : _p(rhs._p), _ref(rhs._ref)  // 拷贝构造函数
    {
        ++*_ref;    // 引用计数加1
        std::cout << "myShared_ptr(const myShared_ptr& rhs)" << std::endl; // 拷贝构造函数输出
    }

    myShared_ptr& operator=(const myShared_ptr& rhs)    // 拷贝赋值运算符
    {
        ++*rhs._ref;    // 引用计数加1
        --*_ref;    // 引用计数减1
        if (*_ref == 0)    // 引用计数为0
        {
            delete _p;    // 释放指针
            delete _ref;    // 释放引用计数
        }
        _p = rhs._p;    // 指针拷贝
        _ref = rhs._ref;    // 引用计数拷贝
        std::cout << "myShared_ptr& operator=(const myShared_ptr& rhs)" << std::endl; // 拷贝赋值运算符输出
        return *this;
    }

    ~myShared_ptr() // 析构函数
    {
        --*_ref;    // 引用计数减1
        if (*_ref == 0)    // 引用计数为0
        {
            delete _p;    // 释放指针
            delete _ref;    // 释放引用计数
        }
        std::cout << "~myShared_ptr()" << std::endl; // 析构函数输出
    }

    T& operator*()  // 解引用运算符
    {
        return *_p; // 返回指针所指对象
    }

    T* operator->() // 解指针运算符
    {
        return _p; // 返回指针
    }
private:
    T* _p;    // 指针
    int* _ref;    // 引用计数
};

int main()
{
    myShared_ptr<int> p1(new int(10));
    myShared_ptr<int> p2(p1);
    myShared_ptr<int> p3(p2);
    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    std::cout << *p3 << std::endl;
    return 0;
}