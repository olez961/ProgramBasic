#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;

void proc1(int a)
{
    unique_lock<mutex> g1(m, defer_lock);   // 第二个参数表示初始化了一个没有加锁的mutex
    cout << "xxxxxxxx" << endl;
    g1.lock();  // 手动加锁，注意，不是m.lock()，因为m已经被g1接管了
    cout << "proc1函数正在改写a" << endl;
    cout << "原始a为: " << a << endl;
    cout << "现在a为: " << a + 2 << endl;
    g1.unlock();    // 临时解锁
    cout << "xxxxxx" << endl;
    g1.lock();
    cout << "xxxxxx" << endl;
}   // 自动解锁

void proc2(int a)
{
    // 尝试加锁一次，但如果没有锁定成功，会立即返回
    // 不会阻塞在那里，且不会再次尝试锁操作
    unique_lock<mutex> g2(m, try_to_lock);
    // unique_lock<mutex> g3(move(g2)); //所有权转移，此时由g3来管理互斥量m
    if(g2.owns_lock()) {    // 锁成功
        cout << "proc2函数正在改写a" << endl;
        cout << "原始a为: " << a << endl;
        cout << "现在a为: " << a + 1 << endl;
    } else {    // 锁失败则执行这段语句
        cout << "..." << endl;
    }
}   // 自动解锁

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
这里是proc2先抢到了锁，这是我没有想到的
输出：
xxxxxxxx
proc2函数正在改写a
原始a为: 0
现在a为: 1
proc1函数正在改写a
原始a为: 0
现在a为: 2
xxxxxx
xxxxxx
*/