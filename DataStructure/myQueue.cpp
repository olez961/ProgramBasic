//#include <bits/stdc++.h>
#include <deque>
#include <iostream>
using namespace std;

template <typename T>
class MyQueue {
protected:
	deque<T> c;
public:
	bool empty() const { return c.empty(); }
	size_t size() const { return c.size(); }
	T front() { return c.front(); }
	T back() { return c.back(); }
	void push(const T& x) { c.push_back(x); }
	void pop() { c.pop_front(); }
};

template <typename T>
bool operator==(MyQueue<T>& x, MyQueue<T>& y) {
	return x.c == y.c;
}

template <typename T>
bool operator<(MyQueue<T>& x, MyQueue<T>& y) {
	return x.c < y.c;
}

int main() {
	MyQueue<int> iqueue;

	iqueue.push(1);
	iqueue.push(3);
	iqueue.push(5);
	iqueue.push(7);

	cout << "The size of queue is: " << iqueue.size() << endl;
	cout << "The first element of queue is: " << iqueue.front() << endl;
	
	iqueue.pop();	cout << "After poping, the first element is: " << iqueue.front() << endl;
	iqueue.pop();	cout << "After poping, the first element is: " << iqueue.front() << endl;
	iqueue.pop();	cout << "After poping, the first element is: " << iqueue.front() << endl;
	cout << "The size of queue is: " << iqueue.size() << endl;

	return 0;
}

