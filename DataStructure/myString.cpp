#include <iostream>
#include <cstring>

using namespace std;

class myString {
public:
    myString(const char *str = nullptr);    // 构造函数
    myString(const myString&);      // 拷贝构造函数
    myString& operator=(const myString&);   // 赋值运算符重载
    ~myString();    // 析构函数

//private:
    char *m_date;   // 存储字符串的数组
    int m_size;     // 存储字符串的大小
};

// 构造函数
// 注意参数的默认值只能在函数声明时设置，不能在函数定义中设置
myString::myString(const char *str) {
    if(str == nullptr) {  // 如果str为空，则创建一个空字符串
        m_date = new char[1];   // 分配一个空字符串
        m_date[0] = '\0';       // 初始化空字符串
        m_size = 0;             // 初始化大小为0
    } else {    // 如果str不为空，则创建一个字符串
        m_size = strlen(str);   // 获取字符串的大小
        m_date = new char[m_size + 1];  // 分配字符串的空间
        strcpy(m_date, str);    // 复制字符串
    }

    cout << "myString(const char *str) called" << endl;
}

// 拷贝构造函数
myString::myString(const myString& str) {   // 拷贝构造函数
    m_size = strlen(str.m_date);        // 获取字符串的大小
    m_date = new char[m_size + 1];      // 分配字符串的空间
    strcpy(m_date, str.m_date);         // 复制字符串

    cout << "myString(const myString& str) called" << endl;
}

// 赋值运算符重载
/*
myString& myString::operator=(const myString& rhs) {    // 赋值运算符重载
    if(this == &rhs) {  // 注意这里是比较地址是否相同
        return *this;   // 如果相同，则返回自身
    }
    
    delete [] m_date;   // 释放原来的字符串
    m_size = rhs.m_size;// 获取字符串的大小
    strcpy(m_date, rhs.m_date); // 复制字符串
    return *this;       // 返回自身
}
*/

// 字符串赋值函数（推荐使用）
// 保证了异常安全性
myString& myString::operator=(const myString& rhs) {    // 赋值运算符重载
    if(this != &rhs) {  // 注意这里是比较地址是否相同
        // 注意这里新建了一个字符串，所以会调用构造函数，结束时调用析构函数
        myString tempStr(rhs);  // 创建一个临时字符串

        delete [] m_date;       // 释放原来的字符串
        m_size = tempStr.m_size;// 获取字符串的大小
        strcpy(m_date, tempStr.m_date); // 复制字符串
    }

    cout << "myString& myString::operator=(const myString& rhs) called" << endl;
    return *this;
}

// 析构函数
myString::~myString() { // 析构函数
    delete [] m_date;   // 释放字符串
    cout << "~myString() called" << endl;
}

int main() {
    myString str1("hello"); // 创建字符串
    myString str2(str1);    // 创建字符串
    myString str3;          // 创建字符串
    str3 = str1;
    cout << str1.m_date << endl;
    cout << str2.m_date << endl;
    cout << str3.m_date << endl;
    return 0;
}