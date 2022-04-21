#include "myAVLtree.h"
#include <iostream>

using namespace std;

int main() {
    myAVLtree tree(10);
    tree.insert(5);
    tree.print();
    for(int i = 0; i < 16; ++i) {
        tree.insert((i * 2));
        tree.print();
        cout << "the height of the tree is: " << tree.getHeight() << endl;
    }
    for(int i = 0; i < 16; ++i) {
        tree.insert((i * 2 + 1));
        tree.print();
        cout << "the height of the tree is: " << tree.getHeight() << endl;
    }
    system("pause");
    return 0;
}