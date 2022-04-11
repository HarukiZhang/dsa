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
    void insert(DataType x);/*The logic of insert() can be optimized;*/
    DataType top();
    void deleteValue(DataType x);
private:
    TreePtr _deleteV(TreePtr ptr, DataType x);
    TreePtr _insert(TreePtr ptr, DataType x);

    TreePtr _find(TreePtr ptr, DataType x);
    TreePtr _findMax(TreePtr ptr);
    TreePtr _findMin(TreePtr ptr);

    TreePtr rotate_left(TreePtr ptr);
    TreePtr rotate_right(TreePtr ptr);
    TreePtr rotate_left_right(TreePtr ptr);
    TreePtr rotate_right_left(TreePtr ptr);
    int getHeight(TreePtr ptr);
    int getFBlc(TreePtr ptr);

    int listSize = 0;
    TreePtr entry = 0;
    TNode list[kMaxLen];//static-linked-list storage;
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
    cout << avlTree.top() << endl;
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

Duplicate value test:
5
88 70 70 61 61
*/

void AVLTree::deleteValue(DataType x){
    entry = _deleteV(entry, x);
    return;
}

TreePtr AVLTree::_deleteV(TreePtr ptr, DataType x){
    if (list[ptr].height = -1)//if empty;
        return ptr;
    if (x < list[ptr].data)
        list[ptr].lchild = _deleteV(list[ptr].lchild, x);
    else if (x > list[ptr].data)
        list[ptr].rchild = _deleteV(list[ptr].rchild, x);
    else {//crt node is x to be deleted;
        if (list[ptr].height == 0){//degree == 0;
            list[ptr].height = list[ptr].lchild = list[ptr].rchild = -1;
        }
        else {
            /*compare which way is higher (deeper),
            substitute with the deeper side's max or min;*/
        }
    }
}

TreePtr AVLTree::_find(TreePtr ptr, DataType x){
    if (list[ptr].height == -1) return -1;
    if (x < list[ptr].data) return _find(list[ptr].lchild, x);
    else if (x > list[ptr].data) return _find(list[ptr].rchild, x);
    else return ptr;
}
TreePtr AVLTree::_findMax(TreePtr ptr){
    if (list[ptr].height == -1) return -1;
    TreePtr i = ptr;
    while (list[i].rchild != -1) i = list[i].rchild;
    return i;
}
TreePtr AVLTree::_findMin(TreePtr ptr){
    if (list[ptr].height == -1) return -1;
    TreePtr i = ptr;
    while (list[i].lchild != -1) i = list[i].lchild;
    return i;
}


void AVLTree::insert(DataType x){
    /*The first insertion is unique: no data in node can be compared;*/
    if (listSize == 0){
        list[entry].data = x;
        list[entry].height = 0;
        ++listSize;
    }
    else entry = _insert(entry, x);
    return;
}

TreePtr AVLTree::_insert(TreePtr ptr, DataType x){
    /*real insertion: insert into rear;*/
    if (ptr == -1){
        list[listSize].data = x;
        list[listSize].height = 0;
        return listSize++;//only increse listSize here, avoiding duplicate increment mistake;
    }
    /*find parent-child relationship*/
    if (x < list[ptr].data){
        list[ptr].lchild = _insert(list[ptr].lchild, x);
    }
    else if (x > list[ptr].data){
        list[ptr].rchild = _insert(list[ptr].rchild, x);
    }
    else {//deal with duplicate value;
        return ptr;//do not insert duplicate;
    }
    /*check factor-of-Balance and rotate*/
    TreePtr nPtr = ptr;
    if ( getFBlc(ptr) > 1){
        if (x < list[ptr].data){
            if (x < list[list[ptr].lchild].data) nPtr = rotate_left(ptr);
            else nPtr = rotate_left_right(ptr);
        }
        else {
            if (x >= list[list[ptr].rchild].data) nPtr = rotate_right(ptr);
            else nPtr = rotate_right_left(ptr);
        }
    }
    else //updating height is needed only when not rotating;
        list[nPtr].height = getHeight(nPtr);
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