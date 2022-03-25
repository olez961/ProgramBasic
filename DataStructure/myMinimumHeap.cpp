#include <vector>
#include <iostream>

using namespace std;

template <class T>
class myMinimumHeap {
protected:
    int len;
    vector<T> heap;
public:
    myMinimumHeap(): len(0) {}

    myMinimumHeap(const T t) {
        heap.push_back(t);
        len = 1;
    }

    void push(const T t) {
        heap.push_back(t);
        ++len;
        for(int i = (len - 1) / 2; i >= 0; --i) {
            min_heapify(heap, i, len);
        }
    }

    void pop() {
        heap[0] = heap[--len];
        heap.pop_back();
        min_heapify(heap, 0, len);
    }

    T top() {
        return heap[0];
    }

    bool empty() {
        return len > 0;
    }

    void min_heapify(vector<T> &heap, int start, int end) {
        int dad = start;
        int son = dad * 2 + 1;
        while(son < end) {
            if(son + 1 < end && heap[son] > heap[son+1]) {
                ++son;
            }
            if(heap[dad] < heap[son])   return;
            swap(heap[dad], heap[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }

    size_t size() {
        return this->len;
    }

    void traverse() {
        cout << "For now, the heap is: ";
        for(auto &i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
	myMinimumHeap<int> iheap;

	iheap.push(1);
	iheap.push(3);
	iheap.push(5);
	iheap.push(7);

	cout << "The len of heap is: " << iheap.size() << endl;
	cout << "The first element of heap is: " << iheap.top() << endl;
	
    iheap.traverse();
	iheap.pop();	cout << "After poping, the first element is: " << iheap.top() << endl;
    iheap.traverse();
	iheap.pop();	cout << "After poping, the first element is: " << iheap.top() << endl;
    iheap.traverse();
	iheap.pop();	cout << "After poping, the first element is: " << iheap.top() << endl;
    iheap.traverse();
	cout << "The len of heap is: " << iheap.size() << endl;

	return 0;
}