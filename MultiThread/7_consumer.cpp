#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unistd.h>
#include <condition_variable>

using namespace std;

// 
struct CacheData
{
    int id;
    string data;
};

queue<CacheData> Q;
const int MAX_CACHEDATA_LENGTH = 10;

mutex m;
condition_variable condConsumer;
condition_variable condProducer;

int ID = 1;

void ConsumerActor()
{
    unique_lock<mutex> lockerConsumer(m);
    cout << "[" << this_thread::get_id() << "] 获取了锁" <<endl;
    while(Q.empty()) {
        cout << "因为队列为空，所以消费者Sleep" << endl;
        cout << "[" << this_thread::get_id() << "] 不再持有锁" <<endl;
        // 
        condConsumer.wait(lockerConsumer);
        cout << "[" << this_thread::get_id() << "] Wake，重新获取了锁" <<endl;
    }
    sleep(5);
    cout << "[" << this_thread::get_id() << "]";
    CacheData temp = Q.front();
    cout << " - ID: " << temp.id << " DATA: " << temp.data << endl;
    Q.pop();
    condProducer.notify_one();
    cout << "[" << this_thread::get_id() << "] 释放了锁\n" <<endl;
}

void ProducerActor()
{
    unique_lock<mutex> lockerProducer(m);
    cout << "[" << this_thread::get_id() << "] 获取了锁" <<endl;
    while(Q.size() >= MAX_CACHEDATA_LENGTH)
    {
        cout << "因为队列为满，所以生产者Sleep" << endl;
        cout << "[" << this_thread::get_id() << "] 不再持有锁" <<endl;
        // 
        condProducer.wait(lockerProducer);
        cout << "[" << this_thread::get_id() << "] Wake，重新获取了锁" <<endl;
    }
    sleep(3);
    cout << "[" << this_thread::get_id() << "] ";
    CacheData temp;
    temp.id = ID++;
    temp.data = "*****";
    cout << " + ID: " << temp.id << " Data: " << temp.data << endl;
    Q.push(temp);
    condConsumer.notify_one();
    cout << "[" << this_thread::get_id() << "] 释放了锁\n" <<endl;
}

void ConsumerTask()
{
    while(1)
    {
        ConsumerActor();
    }
}

void ProducerTask()
{
    while(1)
    {
        ProducerActor();
    }
}

void Dispatch(int ConsumerNum, int ProducerNum)
{
    vector<thread> thsC;
    for(int i = 0; i < ConsumerNum; ++i)
    {
        thsC.push_back(thread(ConsumerTask));
    }

    vector<thread> thsP;
    for(int j = 0; j < ProducerNum; ++j)
    {
        thsP.push_back(thread(ProducerTask));
    }

    for(int i = 0; i < ConsumerNum; ++i)
    {
        if(thsC[i].joinable())
        {
            thsC[i].join();
        }
    }

    for(int j = 0; j < ProducerNum; ++j)
    {
        if(thsC[j].joinable())
        {
            thsC[j].join();
        }
    }
}

int main()
{
    Dispatch(1, 5);
    return 0;
}