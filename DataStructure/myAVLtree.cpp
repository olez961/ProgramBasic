#include "myAVLtree.h"

myAVLtree::myAVLtree(int num)
{
    root = nullptr;
    size = num;
}

myAVLtree::~myAVLtree()
{
    destroy(root);
}

void myAVLtree::preOrder()
{
    preOrder(root);
}

void myAVLtree::preOrder(myAVLtreeNode *node)
{
    if(node) {
        std::cout << node->key << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

void myAVLtree::inOrder()
{
    inOrder(root);
}

void myAVLtree::inOrder(myAVLtreeNode *node)
{
    if(node) {
        inOrder(node->left);
        std::cout << node->key << " ";
        inOrder(node->right);
    }
}

void myAVLtree::insert(int key)
{
    //std::cout << "prepare to insert: " << key << std::endl;
    root = insert(root, key);
}

myAVLtreeNode *myAVLtree::insert(myAVLtreeNode *node, int key)
{
    if(!node) { // 若插入结点为空则创建新结点插入结点
        node = new myAVLtreeNode(key);  // 创建新结点
        //std::cout << "get a new node: " << key << std::endl;
        return node;
    }
    if(key < node->key) {   // 左子树
        node->left = insert(node->left, key);   // 左子树递归
    } else {
        node->right = insert(node->right, key);
    }
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);
    // 注意以下每种情况都是特例，仅当失衡的时候，才需要进行旋转
    if(balance > 1 && key < node->left->key) {  // 左左
        return rightRotate(node);   // 右旋
    } else if(balance < -1 && key > node->right->key) { // 右右
        return leftRotate(node);    // 左旋
    } else if(balance > 1 && key > node->left->key) {   // 左右
        node->left = leftRotate(node->left);    // 左左
        return rightRotate(node);   // 右旋
    } else if(balance < -1 && key < node->right->key) { // 右左
        node->right = rightRotate(node->right); // 右右
        return leftRotate(node);    // 左旋
    }
    //adjust(node);   // 调整，感觉应该是要更新一些东西的
    return node;
}

bool myAVLtree::remove(int key)
{
    if(!root) {
        return false;
    } else {
        root = remove(root, key);
        return true;
    }
}

bool myAVLtree::find(int key)
{
    if(!root) {
        return false;
    } else {
        return find(root, key);
    }
}

int myAVLtree::getHeight()
{
    return getHeight(root);
}

int myAVLtree::getHeight(myAVLtreeNode *node)
{
    if(!node) {
        return 0;
    } else {
        return node->height;
    }
}

int myAVLtree::getBalance(myAVLtreeNode *node)
{
    if(!node) {
        return 0;
    } else {
        return getHeight(node->left) - getHeight(node->right);
    }
}

// 左旋
myAVLtreeNode *myAVLtree::leftRotate(myAVLtreeNode *node)
{
    myAVLtreeNode *right = node->right;     // 右子树
    myAVLtreeNode *rightleft = right->left; // 右子树的左子树
    right->left = node;         // 右子树的左子树指向原来的根节点
    node->right = rightleft;    // 根节点的右子树指向右子树的左子树

    // 更新高度
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    right->height = 1 + std::max(getHeight(right->left), getHeight(right->right));

    return right;   // 返回新的根节点
}

// 右旋
myAVLtreeNode *myAVLtree::rightRotate(myAVLtreeNode *node)
{
    myAVLtreeNode *left = node->left;   // 左子树
    myAVLtreeNode *leftright = left->right; // 左子树的右子树
    left->right = node;         // 左子树的右子树指向原来的根节点
    node->left = leftright;     // 根节点的左子树指向左子树的右子树

    // 更新高度
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    left->height = 1 + std::max(getHeight(left->left), getHeight(left->right));

    return left;    // 返回新的根节点
}

// LR型调整，左子树的右节点插入导致失衡，先左旋再右旋
myAVLtreeNode *myAVLtree::lrRotate(myAVLtreeNode *node)
{
    node->left = leftRotate(node->left);   // 左旋
    return rightRotate(node);   // 右旋
}

// RL型调整，右子树的左节点插入导致失衡，先右节点右旋再左旋
myAVLtreeNode *myAVLtree::rlRotate(myAVLtreeNode *node)
{
    node->right = rightRotate(node->right);   // 右旋
    return leftRotate(node);   // 左旋
}

myAVLtreeNode *myAVLtree::remove(myAVLtreeNode *node, int key)
{
    if(!node) {
        return nullptr;
    }
    if(key < node->key) {
        node->left = remove(node->left, key);
    } else if(key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if(!node->left && !node->right) {
            delete node;
            return nullptr;
        } else if(!node->left) {
            myAVLtreeNode *temp = node;
            node = node->right;
            delete temp;
        } else if(!node->right) {
            myAVLtreeNode *temp = node;
            node = node->left;
            delete temp;
        } else {
            myAVLtreeNode *temp = node->right;
            while(temp->left) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }
    // 更新高度
    if(!node) {
        return nullptr;
    }
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    // 调整
    int balance = getBalance(node); // 获取平衡因子
    if(balance > 1 && getBalance(node->left) >= 0) {    // LL型
        return rightRotate(node);   // 右旋
    } else if(balance < -1 && getBalance(node->right) <= 0) {   // RR型
        return leftRotate(node);    // 左旋
    } else if(balance > 1 && getBalance(node->left) < 0) {  // LR型
        node->left = leftRotate(node->left);    // 左旋
        return rightRotate(node);   // 右旋
    } else if(balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;    // 返回新的根节点
}

myAVLtreeNode *myAVLtree::find(myAVLtreeNode *node, int key)
{
    if(!node) {
        return nullptr;
    }
    if(key < node->key) {
        return find(node->left, key);
    } else if(key > node->key) {
        return find(node->right, key);
    } else {
        return node;
    }
}

void myAVLtree::destroy(myAVLtreeNode *node)
{
    if(!node) { // 递归终止条件
        return;
    }
    destroy(node->left);    // 递归删除左子树
    destroy(node->right);   // 递归删除右子树
    delete node;    // 删除根节点
}

void myAVLtree::print(myAVLtreeNode *node)
{
    inOrder(node);
    std::cout << std::endl;
}

void myAVLtree::print()
{
    print(this->root);
}

void myAVLtree::adjust(myAVLtreeNode *node)
{
    if(!node) {
        return;
    }
    adjust(node->left);
    adjust(node->right);
    // 更新高度
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    // 调整
    int balance = getBalance(node); // 获取平衡因子
    if(balance > 1 && getBalance(node->left) >= 0) {    // LL型
        node = rightRotate(node);   // 右旋
    } else if(balance < -1 && getBalance(node->right) <= 0) {   // RR型
        node = leftRotate(node);    // 左旋
    } else if(balance > 1 && getBalance(node->left) < 0) {  // LR型
        node->left = leftRotate(node->left);    // 左旋
        node = rightRotate(node);   // 右旋
    } else if(balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        node = leftRotate(node);
    }
}