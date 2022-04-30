#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <sys/wait.h>
#include <unistd.h> // 这里面似乎才有sleep函数
//#include <Windows.h>

using namespace std;

double t1(const double a, const double b)
{
    double c = a + b;
    sleep(3);    // 假设t1函数是个复杂的计算过程，需要消耗三秒
    return c;
}

// g++ -std=c++11 -o test 6_async_future.cpp -lpthread
int main()
{
    double a = 2.3;
    double b = 6.7;
    // std::shared_future的get()成员函数是复制数据，其get()可以调用多次
    future<double> fu = async(t1, a, b);    // 创建异步线程，并将线程的执行结果用fu占位
    cout << "正在计算" << endl;
    cout << "计算结果马上准备好，请您耐心等待" << endl;
    cout << "计算结果: " << fu.get() << endl;   // 阻塞主线程，直至异步线程return
    // cout << "计算结果: " << fu.get() << endl;   // 取消该语句注释后运行会报错，因为future对象的get()方法只能调用一次

    return 0;
}

/*
输出：
正在计算
计算结果马上准备好，请您耐心等待
计算结果: 9
*/