#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

void quickSort(vector<int> &arr, int start, int end) {
    if(start >= end) return;    // 只有一个元素的数组，直接返回
    int pivot = arr[start]; // 基准值
    int left = start;       // 左指针
    int right = end;        // 右指针
    while(left < right) {   // 只要左右指针没有相遇，就一直循环
        while(left < right && arr[right] >= pivot) --right; // 右指针向左移动，直到找到比pivot小的元素
        arr[left] = arr[right];     // 将右指针所指元素放到左指针所指的位置
        while(left < right && arr[left] <= pivot) ++left;   // 左指针向右移动，直到找到比pivot大的元素
        arr[right] = arr[left];     // 将左指针所指元素放到右指针所指的位置
    }
    arr[left] = pivot;  // 将pivot放到相遇的位置
    quickSort(arr, start, left - 1);
    quickSort(arr, left + 1, end);
}

int main() {
    vector<int> arr = {2, 4, 8, 10, 7, 6, 5, 3, 9, 1};
    quickSort(arr, 0, arr.size() - 1);
    // 注意下面的ostream_iterator是iterator头文件中的，不是algorithm头文件中的
    // 因为ostream_iterator是一个类，而不是一个类的对象，所以不能直接用<<输出
    // 而是需要用ostream_iterator<int>这种形式
    // 否则会报错：
    // error: invalid use of incomplete type ‘ostream_iterator<int>’
    // copy_n是algorithm头文件中的一个函数，可以用来拷贝n个元素
    copy_n(arr.begin(), arr.size(), ostream_iterator<int>(cout, " "));  // 输出排序后的数组
    return 0;
}