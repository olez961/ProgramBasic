#include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class MyStack {
protected:
	vector<T> c;
public:
	// 以下完全利用Sequence c的操作，完成stack的操作
	bool empty() const { return c.empty(); }
	size_t size() const { return c.size(); }
	T top() { return c.back(); }
	const T top() const { return c.back(); }
	void push(const T& x) { c.push_back(x); }
	void pop() { c.pop_back(); }
};

template <class T>
bool operator==(const MyStack<T>& x, const MyStack<T>& y)
{
	return x.c == y.c;
}


template <class T>
bool operator<(const MyStack<T>& x, const MyStack<T>& y)
{
	return x.c < y.c;
}

int main()
{
	MyStack<int> istack;
	istack.push(1);
	istack.push(3);	
	istack.push(5);
	istack.push(7);

	cout << istack.size() << endl;
	cout << istack.top() << endl;

	istack.pop();	cout << istack.top() << endl;
	istack.pop();	cout << istack.top() << endl;
	istack.pop();	cout << istack.top() << endl;
	cout << istack.size() << endl;

	return 0;
}
