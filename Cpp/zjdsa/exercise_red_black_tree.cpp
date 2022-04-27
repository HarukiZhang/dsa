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
    void traversal();
private:
    void left_rotate(TreePtr me);
    void right_rotate(TreePtr me);
    void insert_FixUp(TreePtr me);

    int size = 0;
    TreePtr Nil;
    TreePtr root;
};


int main(){
    Tree T;
    T.insert(11);
    T.insert(2);
    T.insert(14);
    T.insert(1);
    T.insert(7);
    T.insert(15);
    T.insert(5);
    T.insert(8);
    T.insert(4);
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
    insert_FixUp(tmp);
    ++size;
    return;
}

void Tree::left_rotate(TreePtr me){
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

void Tree::right_rotate(TreePtr me){
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

void Tree::insert_FixUp(TreePtr me){
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
  /*case 2*/else if (me == father->rchild){
                me = father;//me being shifted-up 1 level;
                left_rotate(me);//me being rotated-down 1 level;
                //finally, me's level is unchanged;
                //both father and grandpa pointer is unchanged;
            }
  /*case 3*/else {//if me is left child of father;
                //should there be an else clause?
                father->color = Color::Black;//here, uncle is already black;
                grandpa->color = Color::Red;
                right_rotate(grandpa);
            }
            //once case 2 or 3 being done, while-loop terminates;
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
            else if (me == father->lchild){
                me = father;
                right_rotate(me);
            }
            else {//if me is right child of father;
                father->color = Color::Black;
                grandpa->color = Color::Red;
                left_rotate(grandpa);
            }
        }
    }
    root->color = Color::Black;
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