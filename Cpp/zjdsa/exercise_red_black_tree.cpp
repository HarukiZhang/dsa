#include<iostream>
#include<queue>
using namespace std;

enum class Color : bool {
    Black = false, Red = true
};
typedef int DataType;
typedef struct TNode *TreePtr;
struct TNode {
    DataType key = 0;
    Color color = Color::Red;//by default, node-newly-inserted is Red;
    TreePtr parent, lchild, rchild;
};

class Tree {
public:
    Tree();
    ~Tree();
    void insert(DataType x);
    void erase(DataType x);
    void traversal();
private:
    void _left_rotate(TreePtr me);
    void _right_rotate(TreePtr me);
    void _insert_FixUp(TreePtr me);
    void _transplant(TreePtr to, TreePtr fr);
    void _erase_node(TreePtr z);
    void _erase_FixUp(TreePtr x);
    TreePtr _findMin(TreePtr fr);

    int size = 0;
    TreePtr Nil;//head alse as leaf;
    TreePtr root;
};


int main(){
    Tree T;
    T.insert(41);
    T.traversal();
    T.insert(38);
    T.traversal();
    T.insert(31);
    T.traversal();
    T.insert(12);
    T.traversal();
    T.insert(19);
    T.traversal();
    T.insert(8);
    T.traversal();
    return 0;
}

Tree::Tree(){
    Nil = new TNode {0, Color::Black, nullptr };
    root = Nil;
}

Tree::~Tree(){
    queue<TreePtr> que;
    que.push(root);
    while (!que.empty()){
        TreePtr crtP = que.front();
        que.pop();
        if (crtP->lchild != Nil)
            que.push(crtP->lchild);
        if (crtP->rchild != Nil)
            que.push(crtP->rchild);
        delete crtP;
    }
    delete Nil;
}


void Tree::_transplant(TreePtr to, TreePtr fr){
    if (to->parent == Nil)//if to is root;
        root = fr;
    else if (to == to->parent->lchild)//if to is left child of its father;
        to->parent->lchild = fr;
    else to->parent->rchild = fr;//else when to is right child of its father;
    fr->parent = to->parent;//un-conditional;
    return;
}

void Tree::_erase_node(TreePtr z){
    //x: the trace : points to the node being trans-ed;
    //x will be used as the base loc of _fixUp();
    TreePtr x;
    TreePtr y = z;
    //y_ori_color: used to judge whether the rb-property is spoiled by transplantation;
    Color y_ori_color = y->color;
    if (z->lchild == Nil){//no matter whether left child exists;
        x = z->rchild;
        _transplant(z, z->rchild);//substitute z with its child;
    }
    else if (z->rchild == Nil){//left child exists;
        x = z->lchild;
        _transplant(z, z->lchild);
    }
    else {//both children exist;
        y = _findMin(z->rchild);//by default, search the min of RIGHT CHILD;
        y_ori_color = y->color;//update;
        x = y->rchild;//note: crt y is min node, hence it has Nil left child;
        if (y->parent == z)
            x->parent = y;//if new y is adjacent to z, no need to transplant x to y;
        else {//if new y is not adjacent to z;
            //before tranplant y to z, firstly need to trans x to y;
            _transplant(y, y->rchild);
            y->rchild = z->rchild;//resolve z->right from z, and concatenate it to y;
                                  //prepare for, later, y replacing z;
            y->rchild->parent = y;
        }
        _transplant(z, y);
        y->lchild = z->lchild;
        y->lchild->parent = y;
        y->color = z->color;//set color of y as z;
    }
    if (y_ori_color == Color::Black)
        _erase_FixUp(x);
    delete z;
    return;
}

void Tree::_erase_FixUp(TreePtr x){
    while (x != root && x->color == Color::Black){
        if (x == x->parent->lchild){
            TreePtr w = x->parent->rchild;//the brother of x;
            /*case 1*/
            if (w->color == Color::Red){
                w->color = Color::Black;
                x->parent->color = Color::Red;
                _left_rotate(x->parent);
                w = x->parent->rchild;
            }
            /*case 2*/
            if (w->lchild->color == Color::Black && w->rchild->color == Color::Black){
                w->color = Color::Red;
                x = x->parent;
            }
            else {
                /*case 3*/
                if (w->rchild->color == Color::Black){
                    w->lchild->color = Color::Black;
                    w->color = Color::Red;
                    _right_rotate(w);
                    w = x->parent->rchild;
                }
                /*case 4*/
                w->color = x->parent->color;
                x->parent->color = Color::Black;
                w->rchild->color = Color::Black;
                _left_rotate(x->parent);
                x = root;
            }
        }
        else {
            //same as then clause with "right" and "left" exchanged;
        }
    }
    x->color = Color::Black;
    return;
}

void Tree::insert(DataType x){
    //initially, root = Nil;
    TreePtr crt = root, last = Nil;
    bool isLeft = true;
    while (crt != Nil){
        last = crt;
        if (x < crt->key){
            crt = crt->lchild;
            isLeft = true;
        }
        else {
            crt = crt->rchild;
            isLeft = false;
        }
    }
    TreePtr tmp = new TNode {x, Color::Red, last, Nil, Nil };
    if (last == Nil)
        root = tmp;
    else if (x < last->key)
        last->lchild = tmp;
    else last->rchild = tmp;
    _insert_FixUp(tmp);
    ++size;
    return;
}

void Tree::_insert_FixUp(TreePtr me){
    TreePtr father = me->parent,
        grandpa = father->parent;
    while (father->color == Color::Red){
        if (father == grandpa->lchild){
            TreePtr uncle = grandpa->rchild;
  /*case 1*/if (uncle->color == Color::Red){
                //parent-grandparent color exchange;
                father->color = uncle->color = Color::Black;
                grandpa->color = Color::Red;
                //shift-up me pointer and family by two levels;
                me = grandpa;
                father = me->parent;
                grandpa = father->parent;
            }
            else {
  /*case 2*/    if (me == father->rchild){
                    me = father;//me being shifted-up 1 level;
                    _left_rotate(me);//me being rotated-down 1 level;
                    //after rotation, need to reset pointer family;
                    father = me->parent;
                    grandpa = father->parent;
                }
  /*case 3*/    //if me is left child of father;
                father->color = Color::Black;//here, uncle is already black;
                grandpa->color = Color::Red;
                _right_rotate(grandpa);
                //once case 2 or 3 being done, while-loop terminates;
            }
        }
        else {//if father is right child of grandpa;
            //same as then clause wiht "right" and "left" exchanged;
            TreePtr uncle = grandpa->lchild;
            if (uncle->color == Color::Red){
                father->color = uncle->color = Color::Black;
                grandpa->color = Color::Red;
                me = grandpa;
                father = me->parent;
                grandpa = father->parent;
            }
            else {
                if (me == father->lchild){
                    me = father;
                    _right_rotate(me);
                    father = me->parent;
                    grandpa = father->parent;
                }
                //if me is right child of father;
                father->color = Color::Black;
                grandpa->color = Color::Red;
                _left_rotate(grandpa);
            }
        }
    }
    root->color = Color::Black;
    return;
}

void Tree::_left_rotate(TreePtr me){
    TreePtr rtChild = me->rchild,
        grandpa = me->parent;
    me->rchild = rtChild->lchild;
    if (rtChild->lchild != Nil)
        rtChild->lchild->parent = me;
    rtChild->parent = grandpa;
    if (grandpa == Nil)//if me is root;
        root = rtChild;
    else if (me == grandpa->lchild)
        grandpa->lchild = rtChild;
    else grandpa->rchild = rtChild;
    rtChild->lchild = me;
    me->parent = rtChild;
    return;
}

void Tree::_right_rotate(TreePtr me){
    TreePtr lfChild = me->lchild,
        grandpa = me->parent;
    me->lchild = lfChild->rchild;
    if (lfChild->rchild != Nil)
        lfChild->rchild->parent = me;
    lfChild->parent = grandpa;
    if (grandpa == Nil)
        root = lfChild;
    else if (me == grandpa->lchild)
        grandpa->lchild = lfChild;
    else grandpa->rchild = lfChild;
    lfChild->rchild = me;
    me->parent = lfChild;
    return;
}

void Tree::traversal(){
    queue<TreePtr> que;
    que.push(root);
    while (!que.empty()){
        TreePtr crtP = que.front();
        que.pop();
        if (crtP != Nil){
            if (crtP->color == Color::Black)
                cout << '(' << crtP->key << ") ";
            else cout << '<' << crtP->key << "> ";
            if (crtP->lchild != Nil || crtP->rchild != Nil){
                que.push(crtP->lchild);
                que.push(crtP->rchild);
            }
        }
        else cout << "-- ";
    }
    cout << endl;
    return;
}