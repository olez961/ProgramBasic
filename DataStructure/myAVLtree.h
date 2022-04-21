#ifndef MYAVLTREE_H
#define MYAVLTREE_H
#include <iostream>
struct myAVLtreeNode
{
    int key;
    int height;
    myAVLtreeNode *left;
    myAVLtreeNode *right;
    myAVLtreeNode(int k) : key(k), height(0), left(nullptr), right(nullptr) {}
};

class myAVLtree
{
public:
    myAVLtree(int num);
    ~myAVLtree();
    void preOrder();
    void inOrder();
    void insert(int key);
    bool remove(int key);
    bool find(int key);
    void print();   // 打印二叉树，注意放在公有函数里面，否则会没办法访问
    int getHeight();
    

protected:
    int getHeight(myAVLtreeNode *node);
    int getBalance(myAVLtreeNode *node);
    myAVLtreeNode *leftRotate(myAVLtreeNode *node);
    myAVLtreeNode *rightRotate(myAVLtreeNode *node);
    myAVLtreeNode *lrRotate(myAVLtreeNode *node);
    myAVLtreeNode *rlRotate(myAVLtreeNode *node);
    myAVLtreeNode *insert(myAVLtreeNode *node, int key);
    myAVLtreeNode *remove(myAVLtreeNode *node, int key);
    myAVLtreeNode *find(myAVLtreeNode *node, int key);
    void preOrder(myAVLtreeNode *node);
    void inOrder(myAVLtreeNode *node);
    void destroy(myAVLtreeNode *node);
    void print(myAVLtreeNode *node);
    void adjust(myAVLtreeNode *node);

private:
    /* data */
    myAVLtreeNode *root;
    int size;   // 这个size不知道有啥用
};

#endif