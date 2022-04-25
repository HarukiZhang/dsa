#include<iostream>
#include<queue>
using namespace std;

constexpr int kMaxSize = 32;
constexpr int kNoFamily = -1;


typedef int DataType;
typedef int TreePtr;

struct TNode {
    DataType data;
    TreePtr parent = kNoFamily,
        lchild = kNoFamily,
        rchild = kNoFamily;
};

class SplayTree {
public:
    void insert(DataType x);
    TreePtr access(DataType x);
    void erase(DataType x);
    void traversal();
private:
    void _adjust(TreePtr ptr);
    bool _identify(TreePtr ch, TreePtr pr);//return whether ch is pr's left child;
    TreePtr _find(TreePtr ptr, DataType x);
    TreePtr _findMax(TreePtr ptr);
    TreePtr _findMin(TreePtr ptr);
    void rot_left(TreePtr ptr);
    void rot_right(TreePtr ptr);

    void rotate(TreePtr ptr);//testing : uncorrect;

    int lsize = 0;
    TreePtr root = 0;
    TNode list[kMaxSize];
};

int main(){
    SplayTree ST;
    ST.insert(50);
    ST.insert(100);
    ST.insert(1);

    ST.access(100);
    ST.traversal();

    ST.insert(25);
    ST.insert(35);
    ST.insert(40);
    ST.insert(30);

    ST.access(87);
    ST.access(40);

    ST.traversal();

    ST.erase(40);
    ST.traversal();
    
    return 0;
}

void SplayTree::_adjust(TreePtr ptr){
    //do not need to modify root within _adjust();
    TreePtr parent = list[ptr].parent, grandma = list[parent].parent;
    if (parent == root){
        bool isLeft = _identify(ptr, parent);
        if (isLeft)
            rot_left(parent);
        else rot_right(parent);
    }
    else {
        bool isLeft_elder = _identify(parent, grandma);
        bool isLeft_senior = _identify(ptr, parent);
        if (isLeft_elder){
            if (isLeft_senior){//left left
                rot_left(grandma);
                rot_left(parent);
            }
            else {//left right
                rot_right(parent);
                rot_left(grandma);
            }
        }
        else {
            if (isLeft_senior){//right left
                rot_left(parent);
                rot_right(grandma);
            }
            else {//right right
                rot_right(grandma);
                rot_right(parent);
            }
        }
        if (grandma != root)//as long as grandma is not root, recurse;
            _adjust(ptr);
    }
    return;
}

void SplayTree::rot_left(TreePtr ptr){
    //totally 6 pointer should be modified;
    TreePtr leftChild = list[ptr].lchild;
    TreePtr grandMa = list[ptr].parent;
    TreePtr burden = list[leftChild].rchild;
    list[ptr].lchild = burden;//modify my left-pointer;
    list[leftChild].rchild = ptr;//modify my child's right-pointer;
    //modify my child's parent-pointer;
    list[leftChild].parent = grandMa;//if grandMa is -1, just set child's alse as -1;
    list[ptr].parent = leftChild;//modify my parent-ponter;
    if (grandMa != kNoFamily){//as long as ptr != root;
        if ( _identify(ptr, grandMa) )
            list[grandMa].lchild = leftChild;//modify grandma's child-pointer;
        else list[grandMa].rchild = leftChild;
    }
    if (burden != kNoFamily)
        list[burden].parent = ptr;//modify burden's parent-pointer;
    return;
}

void SplayTree::rot_right(TreePtr ptr){
    TreePtr rightChild = list[ptr].rchild;
    TreePtr grandMa = list[ptr].parent;
    TreePtr burden = list[rightChild].lchild;
    list[ptr].rchild = burden;
    list[rightChild].lchild = ptr;
    list[rightChild].parent = grandMa;
    list[ptr].parent = rightChild;
    if (grandMa != kNoFamily){
        if ( _identify(ptr, grandMa) )
            list[grandMa].lchild = rightChild;
        else list[grandMa].rchild = rightChild;
    }
    if (burden != kNoFamily)
        list[burden].parent = ptr;
    return;
}

void SplayTree::rotate(TreePtr ptr){
    TreePtr parent = list[ptr].parent,
        grandma = list[parent].parent,
        burden;
    bool isLf_up = _identify(parent, grandma);
    bool isLf_dw = _identify(ptr, parent);

    if (isLf_dw){
        burden = list[ptr].rchild;
        list[ptr].rchild = parent;
        list[parent].lchild = burden;
    }
    else {
        burden = list[ptr].lchild;
        list[ptr].lchild = parent;
        list[parent].rchild = burden;
    }
    list[ptr].parent = grandma;
    list[parent].parent = ptr;
    if (grandma != kNoFamily){
        if (isLf_up)
            list[grandma].lchild = ptr;
        else list[grandma].rchild = ptr;
    }
    if (burden != kNoFamily)
        list[burden].parent = parent;
    return;
}

bool SplayTree::_identify(TreePtr ch, TreePtr pr){
    return list[pr].lchild == ch;
}

void SplayTree::insert(DataType x){
    if (lsize == 0){
        list[0].data = x;
        ++lsize;
        return;
    }

    TreePtr p = root, last = p;
    bool isLeftChild = true;
    while (p != kNoFamily){
        last = p;
        if (x < list[p].data){
            p = list[p].lchild;
            isLeftChild = true;
        }
        else if (x > list[p].data){
            p = list[p].rchild;
            isLeftChild = false;
        }
        else last = kNoFamily;//if x == data, do not insert it;
    }

    if (last != kNoFamily){
        list[lsize].data = x;
        list[lsize].parent = last;
        if (isLeftChild)
            list[last].lchild = lsize;
        else list[last].rchild = lsize;

        _adjust(lsize);
        root = lsize;

        ++lsize;//increment is most final step;
    }
    return;
}

TreePtr SplayTree::access(DataType x){
    if (lsize == 0){
        cout << "empty" << endl;
        return kNoFamily;
    }
    TreePtr p = root, last = p;
    while (p != kNoFamily){
        last = p;
        if (x < list[p].data)
            p = list[p].lchild;
        else if (x > list[p].data)
            p = list[p].rchild;
        else break;
    }
    if (list[last].data == x){
        _adjust(last);
        return root = last;
    }
    cout << "Not Found" << endl;
    return kNoFamily;
}

void SplayTree::erase(DataType x){
    TreePtr p = root, last = p;
    while (p != kNoFamily){
        last = p;
        if (x < list[p].data)
            p = list[p].lchild;
        else if (x > list[p].data)
            p = list[p].rchild;
        else break;
    }
    if (p == kNoFamily){
        cout << "Not Found When Erasing!" << endl;
        return;
    }
    while (p != kNoFamily){
        if (list[p].lchild != kNoFamily){//at-least has left child;
            TreePtr child = _findMax(list[p].lchild);
            list[p].data = list[child].data;//p.data has been thus erased;
            last = p;
            p = child;
        }
        else if (list[p].rchild == kNoFamily){//do not has any child;
            TreePtr parent = list[p].parent;
            if ( _identify(p, parent) )
                list[parent].lchild = kNoFamily;
            else list[parent].rchild = kNoFamily;
            list[p].parent = list[p].lchild = list[p].rchild = kNoFamily;
            _adjust(parent);
            root = parent;
            break;
        }
        else {//only has right child;
            TreePtr child = _findMin(list[p].rchild);
            list[p].data = list[child].data;
            last = p;
            p = child;
        }
    }
    return;
}

TreePtr SplayTree::_findMax(TreePtr ptr){
    while (list[ptr].rchild != kNoFamily)
        ptr = list[ptr].rchild;
    return ptr;
}
TreePtr SplayTree::_findMin(TreePtr ptr){
    while (list[ptr].lchild != kNoFamily)
        ptr = list[ptr].lchild;
    return ptr;
}

void SplayTree::traversal(){
    queue<TreePtr> que;
    que.push(root);
    while (!que.empty()){
        //take;
        TreePtr p = que.front(); que.pop();
        //output:
        cout << list[p].data << ' ';
        //push;
        if (list[p].lchild != kNoFamily)
            que.push(list[p].lchild);
        if (list[p].rchild != kNoFamily)
            que.push(list[p].rchild);
    }
    cout << endl;
    return;
}

TreePtr SplayTree::_find(TreePtr ptr, DataType x){
    //adjust has to be set within find();
    //so, waht to do if target is not found;
    //how to skip adjust when target is not found;
    TreePtr p = ptr;
    while (p != kNoFamily){
        if (x < list[p].data)
            p = list[p].lchild;
        else if (x > list[p].data)
            p = list[p].rchild;
        else break;
    }
    if (p != kNoFamily)
        cout << "Found" << endl;
    else cout << "Not Found" << endl;
    return p;
}