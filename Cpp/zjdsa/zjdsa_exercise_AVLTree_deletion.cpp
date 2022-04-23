#include<iostream>
#include<queue>
using namespace std;

constexpr int kMaxNum = 20, kMaxLen = 32;

typedef int DataType;
typedef int TreePtr;

constexpr TreePtr NOWHERE = -1;

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
    void traversal();
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
    int getFBlc(TreePtr ptr);//return value contains direction;

    int listSize = 0;
    TreePtr entry = 0;
    TNode list[kMaxLen];//static-linked-list storage;
};

int main(){
    
    AVLTree T;

    T.insert(6);
    T.insert(2);
    T.insert(15);
    T.insert(1);
    T.insert(4);
    T.insert(8);
    T.insert(30);
    T.insert(3);
    T.insert(5);
    T.insert(7);
    T.insert(10);
    T.insert(20);
    T.insert(13);
    T.traversal();



    T.deleteValue(3);
    T.deleteValue(5);
    T.traversal();

    T.deleteValue(7);
    T.traversal();

    return 0;
}

void AVLTree::deleteValue(DataType x){
    entry = _deleteV(entry, x);
    return;
}

TreePtr AVLTree::_deleteV(TreePtr ptr, DataType x){
    if (list[ptr].height == -1)//if empty;
        return ptr;
    //search the place of target to delete;
    if (x < list[ptr].data)
        list[ptr].lchild = _deleteV(list[ptr].lchild, x);
    else if (x > list[ptr].data)
        list[ptr].rchild = _deleteV(list[ptr].rchild, x);
    else {//crt node is x to be deleted;
        if (list[ptr].height == 0){//degree == 0;
            list[ptr].height = list[ptr].lchild = list[ptr].rchild = -1;
        }
        else {//hereafter, at-least one child;
            /*compare which way is higher (deeper),
            substitute crt data with the deeper side's max or min;*/
        
            //fB < 0 : right child is deeper than left;
            //fB > 0 : left is deeper;
            int fB = getFBlc(ptr);
            if (fB > 0){
                TreePtr iLfMax = _findMax(list[ptr].lchild);
                list[ptr].data = list[iLfMax].data;//substitution;
                list[ptr].lchild = _deleteV(list[ptr].lchild, list[ptr].data);
            }
            else {//includes : leftHeight == rightHeight;
                //when equals, take prior to delete from right side;
                TreePtr iRtMin = _findMin(list[ptr].rchild);
                list[ptr].data = list[iRtMin].data;
                list[ptr].rchild = _deleteV(list[ptr].rchild, list[ptr].data);
            }
        }
    }
    //compute factor of Balance;
    //when crt node is a watcher, find "breaker" and rotate relevent nodes;
    TreePtr nPtr = ptr;
    if (list[ptr].data != x){//if to-delete is not crt data;
        int fB = getFBlc(ptr);
        //when abs(fB) is bigger than 1, we define it as un-balanced;
        if (fB > 1){//goto left child, who is deeper;
            if ( getFBlc(list[ptr].lchild) >= 0 )//if left side is deeper; or equal;
                nPtr = rotate_left(ptr);
            else nPtr = rotate_left_right(ptr);
            /*if left height equals to right height,
            Logically, it is no different to perform 
                single-left-rotation or double-left-right-rot;
            Practically, however, perform single rotation is simpler and
                changes the structure less;
            */
        }
        else if (fB < -1){//goto right chlid;
            if ( getFBlc(list[ptr].rchild) <= 0 )//if right side is deeper;
                nPtr = rotate_right(ptr);
            else nPtr = rotate_right_left(ptr);
            //when equal, perform the simpler rotation, ie, single-rot;
        }
        else
            list[ptr].height = getHeight(ptr);
    }
    else nPtr = NOWHERE;//if crt data is deleted, return NOWHERE;
    return nPtr;
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
    int fB = getFBlc(ptr);
    fB *= fB;//used as abs(fB);
    if ( fB > 1 ){
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

void AVLTree::traversal(){
    queue<TreePtr> que;
    que.push(entry);
    while ( !que.empty() ){
        TreePtr crtP = que.front();
        que.pop();
        cout << list[crtP].data << ' ';
        if (list[crtP].lchild != -1) que.push(list[crtP].lchild);
        if (list[crtP].rchild != -1) que.push(list[crtP].rchild);
    }
    cout << endl;
    return;
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
    // if (res < 0) res = -res;
    return res;
}