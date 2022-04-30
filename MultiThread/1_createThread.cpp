#include <iostream>
#include <thread>

using namespace std;

void proc(int a) {
    cout << "我是子线程，传入参数为: " << a << endl;
    cout << "子线程中显示子线程id为: " << this_thread::get_id() << endl;
}

// 需要在Linux平台这样编译：
// g++ -std=c++11 -o test createThread.cpp -lpthread
// 注意不是gcc
// windows的多线程似乎复杂得多，面试寄了看来没啥办法
int main()
{
    cout << "我是主线程" << endl;
    int a = 9;
    
    // 第一个参数为函数名，第二个参数为该函数的第一个参数，如果该函数接收多个参数就依次写在后面
    // 此时线程开始执行
    std::thread th2(proc, ref(a));  // 这个不能写在条件变量里面，否则下面会提示未声明

    cout << "主线程中显示子线程id为: " << th2.get_id() << endl;
    // 此时主线程被阻塞直到子线程执行完毕
    th2.join();
    return 0;
}

/*
输出：
我是主线程
主线程中显示子线程id为: 140640194221824
我是子线程，传入参数为: 9
子线程中显示子线程id为: 140640194221824
*/