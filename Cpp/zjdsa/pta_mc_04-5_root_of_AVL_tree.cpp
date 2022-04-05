/*
given a sequence of insertions, you are supposed to tell the root of 
the resulting AVL tree.
Input Specification:
Each input file contains one test case. For each case, the first line contains 
a positive integer N (≤20) which is the total number of keys to be inserted. 
Then N distinct integer keys are given in the next line. All the numbers in 
a line are separated by a space.

Output Specification:
For each test case, print the root of the resulting AVL tree in one line.
*/
#include<iostream>
using namespace std;

constexpr int kMaxNum = 20, kMaxLen = 32;

typedef int DataType;
typedef int TreePtr;

class TNode {
friend class AVLTree;
private:
    DataType data;
    int height = -1;
    TreePtr lchild = -1, rchild = -1;
};

class AVLTree {
public:
    AVLTree(){}
    void insert(DataType x);/*The logic of insert() can be optimized;*/
    DataType top();
private:
    TreePtr _insert(TreePtr ptr, DataType x);
    TreePtr rotate_left(TreePtr ptr);
    TreePtr rotate_right(TreePtr ptr);
    TreePtr rotate_left_right(TreePtr ptr);
    TreePtr rotate_right_left(TreePtr ptr);
    int getHeight(TreePtr ptr);
    int getFBlc(TreePtr ptr);

    int size = 0;
    TreePtr entry = 0;
    TNode list[kMaxLen];
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N;
    cin >> N;
    AVLTree avlTree;
    int tmp;
    for (int i = 0; i < N; ++i){
        cin >> tmp;
        avlTree.insert(tmp);//need initialize height and child ptr;
    }
    cout << avlTree.top();
    return 0;
}

/*
Sample Input 1:
5
88 70 61 96 120
Sample Output 1:
70
Sample Input 2:
7
88 70 61 96 120 90 65
Sample Output 2:
88
*/

void AVLTree::insert(DataType x){
    if (size == 0){
        _insert(-1, x);
        return;
    }
    else if (x < list[entry].data)
        list[entry].lchild = _insert(list[entry].lchild, x);
    else
        list[entry].rchild = _insert(list[entry].rchild, x);
    if ( getFBlc(entry) > 1){
        if (x < list[entry].data){
            if (x < list[list[entry].lchild].data) entry = rotate_left(entry);
            else entry = rotate_left_right(entry);
        }
        else {
            if (x >= list[list[entry].rchild].data) entry = rotate_right(entry);
            else entry = rotate_right_left(entry);
        }
    }
    //update height should be after rotating;
    list[entry].height = getHeight(entry);
    return;
}

TreePtr AVLTree::_insert(TreePtr ptr, DataType x){
    // if (ptr >= 0){
    if (ptr < 0){
        TNode &crt = list[size++];
        crt.data = x;
        crt.height = 0;
        return size - 1;
    }
    int next = -1;
    if (x < list[ptr].data){
        next = list[ptr].lchild;
        list[ptr].lchild = _insert(next, x);
    }
    else {
        next = list[ptr].rchild;
        list[ptr].rchild = _insert(next, x);
    }
    /*check factor-of-Balance and rotate*/
    int nPtr = ptr;
    if ( getFBlc(ptr) > 1){
        if (x < list[ptr].data){
            if (x < list[next].data) nPtr = rotate_left(ptr);
            else nPtr = rotate_left_right(ptr);
        }
        else {
            if (x >= list[next].data) nPtr = rotate_right(ptr);
            else nPtr = rotate_right_left(ptr);
        }
    }
    //update height should be after rotating;
    list[nPtr].height = getHeight(nPtr);
    // }
    return nPtr;
}

TreePtr AVLTree::rotate_left(TreePtr ptr){
    TreePtr leftChild = list[ptr].lchild;
    list[ptr].lchild = list[leftChild].rchild;
    list[leftChild].rchild = ptr;
    /*height should be updated after rotation;*/
    list[ptr].height = getHeight(ptr);//child will be at top of ptr,
    list[leftChild].height = getHeight(leftChild);//so it should be update later;
    return leftChild;
}

TreePtr AVLTree::rotate_right(TreePtr ptr){
    TreePtr rightChild = list[ptr].rchild;
    list[ptr].rchild = list[rightChild].lchild;
    list[rightChild].lchild = ptr;
    list[ptr].height = getHeight(ptr);
    list[rightChild].height = getHeight(rightChild);
    return rightChild;
}

TreePtr AVLTree::rotate_left_right(TreePtr ptr){
    list[ptr].lchild = rotate_right(list[ptr].lchild);
    return rotate_left(ptr);
}
TreePtr AVLTree::rotate_right_left(TreePtr ptr){
    list[ptr].rchild = rotate_left(list[ptr].rchild);
    return rotate_right(ptr);
}

DataType AVLTree::top(){
    return list[entry].data;
}

inline int max(int a, int b){
    return a > b ? a : b;
}

int AVLTree::getHeight(TreePtr ptr){
    int left = list[ptr].lchild != -1 ? list[list[ptr].lchild].height : -1;
    int right = list[ptr].rchild != -1 ? list[list[ptr].rchild].height : -1;
    return left > right ? left + 1 : right + 1;
}

int AVLTree::getFBlc(TreePtr ptr){
    int left = list[ptr].lchild != -1 ? list[list[ptr].lchild].height : -1;
    int right = list[ptr].rchild != -1 ? list[list[ptr].rchild].height : -1;
    int res = left - right;
    if (res < 0) res = -res;
    return res;
}