#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;    // 实例化m对象，注意这里不是定义变量

// g++ -std=c++11 -o test lock_guard_2.cpp -lpthread
void proc1(int a)
{
    m.lock(); // 手动锁定
    // 此时调用了lock_guard的构造函数，申请锁定m
    // 第二个参数表示构造函数中不再进行互斥量锁定
    // 因此需要提前锁定
    lock_guard<mutex> g1(m, adopt_lock);
    cout << "proc1函数正在改写a: " << endl;
    cout << "原始a为: " << a << endl;
    cout << "现在a为: " << a + 2 << endl;
}// 自动解锁

void proc2(int a)
{
    {
        lock_guard<mutex> g2(m);    // 自动锁定
        cout << "proc2函数正在改写a: " << endl;
        cout << "原始a为: " << a << endl;
        cout << "现在a为: " << a + 1 << endl;
    }   // 通过使用{}来调整作用域范围，可以使得m在合适的地方被解锁
    
    cout << "作用域外的内容3" << endl;
    cout << "作用域外的内容4" << endl;
    cout << "作用域外的内容5" << endl;
}

int main()
{
    int a = 0;
    thread t1(proc1, a);
    thread t2(proc2, a);
    t1.join();
    t2.join();

    return 0;
}

/*
输出：
proc1函数正在改写a: 
原始a为: 0
现在a为: 2
proc2函数正在改写a: 
原始a为: 0
现在a为: 1
作用域外的内容3
作用域外的内容4
作用域外的内容5
*/