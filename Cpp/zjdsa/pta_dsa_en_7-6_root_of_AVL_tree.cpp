#include<iostream>
using namespace std;

typedef struct AVLNode* Position;
typedef Position AVLTree;
struct AVLNode {
    int data, height;
    AVLTree left, right;
};

int max(int a, int b){ return a > b ? a : b; }
int getFBlc(AVLTree tr);
int getHeight(AVLTree tr);

AVLTree insert(AVLTree tr, int x);
void freeTree(AVLTree tr);
void preOrdTrvs(AVLTree tr);

AVLTree sglLfRot(AVLTree tr);
AVLTree sglRtRot(AVLTree tr);
AVLTree dblLfRtRot(AVLTree tr);
AVLTree dblRtLfRot(AVLTree tr);

int main(){
    freopen("E:\\in.txt", "r", stdin);
    AVLTree avlTree = nullptr;
    int n, x;
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> x;
        avlTree = insert(avlTree, x);
    }
    preOrdTrvs(avlTree);
    freeTree(avlTree);
}

AVLTree sglLfRot(AVLTree tr){
    /*Attention : tr need to have left subtree;*/
    /*perform sLL rot*/
    AVLTree child = tr->left;
    tr->left = child->right;
    child->right = tr;
    /*update height*/
    tr->height = getHeight(tr);//now child node is taller than tr;
    child->height = getHeight(child);//so child's height should update later;
    return child;
}

AVLTree sglRtRot(AVLTree tr){
    AVLTree child = tr->right;
    tr->right = child->left;
    child->left = tr;
    tr->height = getHeight(tr);
    child->height = getHeight(child);
    return child;
}

AVLTree dblLfRtRot(AVLTree tr){
    /*Firstly, perform sR rotation to B-C, return C;*/
    tr->left = sglRtRot(tr->left);
    /*Secondly, perform sL rotation to A-C, return C;*/
    return sglLfRot(tr);
}

AVLTree dblRtLfRot(AVLTree tr){
    /*individual statement has one less getHeight() than enclosed function;*/
    AVLTree watcher = tr;
    AVLTree midman = watcher->right;
    AVLTree breaker = midman->left;//this is not necessarily breaker actually;
    midman->left = breaker->right;
    watcher->right = breaker->left;
    breaker->left = watcher;
    breaker->right = midman;
    watcher->height = getHeight(watcher);
    midman->height = getHeight(midman);
    breaker->height = getHeight(breaker);
    return breaker;
}

AVLTree insert(AVLTree tr, int x){
    if (!tr){
        tr = new AVLNode {x, 0, 0, 0};
    }
    else {
        if (x < tr->data){
            tr->left = insert(tr->left, x);
            /*new node was inserted into left branch,
                left subtree can only be higher than right;*/
            if (getFBlc(tr) > 1){
                if (x < tr->left->data) tr = sglLfRot(tr);
                else tr = dblLfRtRot(tr);
            }
        }
        else {
            tr->right = insert(tr->right, x);
            if (getFBlc(tr) < -1){//insertion is on right, left - right <= 0;
                if (x < tr->right->data) tr = dblRtLfRot(tr);
                else tr = sglRtRot(tr);
            }
        }
    }
    /*update height for every insertion, no matter rotated or not;*/
    tr->height = getHeight(tr);
    return tr;
    /*my original version below; optimized version above;*/
    // /*update height and compute balancing factor*/
    // int hLf, hRt, fB;
    // hLf = tr->left ? tr->left->height : -1;
    // hRt = tr->right ? tr->right->height : -1;
    // tr->height = max(hLf, hRt) + 1;
    // fB = hLf - hRt;
    // if (fB > 1 || -fB > 1){//abs(fB) > 1;
    //     cout << tr->data << " unbalanced; x=" << x << "\n";
    //     /*judging restoration method*/
    //     /*1st direction judging : left == +1 ; right == -1;
    //       2nd direction judging : left ==  1 ; right ==  2;
    //     Total judging flag = 1st-flag * 2nd-flag;
    //         +1 : Left-left;
    //         +2 : Left-right;
    //         -1 : Right-left;
    //         -2 : Right-right
    //     */
    //     int flag1, flag2;
    //     Position tmp = tr;
    //     /*This two nodes must exist because x has just now been inserted there;
    //         and unbalancing could only happen two or more level upper than itself;*/
    //     if (x < tmp->data){ flag1 =  1; tmp = tmp->left; }
    //     else {              flag1 = -1; tmp = tmp->right; }
    //     if (x < tmp->data){ flag2 =  1; tmp = tmp->left; }
    //     else {              flag2 =  2; tmp = tmp->right; }
    //     switch(flag1 * flag2){
    //     case -2 :
    //         tr = sglRtRot(tr);
    //         cout << "    single Right Rotation has been performed;\n";
    //         break;
    //     case -1 :
    //         tr = dblRtLfRot(tr);
    //         cout << "    double Right-Left Rotation has been performed;\n";
    //         break;
    //     case 1  :
    //         tr = sglLfRot(tr);
    //         cout << "    single Left Rotation has been performed;\n";
    //         break;
    //     case 2  :
    //         tr = dblLfRtRot(tr);
    //         cout << "    double Left-right Rotation has been performed;\n";
    //         break;
    //     default : cout << "switch error;\n"; break;
    //     }
    // }
    // return tr;
}

void freeTree(AVLTree tr){
    if (tr){
        if (tr->left) freeTree(tr->left);
        if (tr->right) freeTree(tr->right);
        delete tr;
    }
    return;
}
void preOrdTrvs(AVLTree tr){
    if (tr){
        cout << tr->data << "[" << tr->height << "] ";
        if (tr->left) preOrdTrvs(tr->left);
        if (tr->right) preOrdTrvs(tr->right);
    }
    return;
}
int getFBlc(AVLTree tr){
    int fB = tr->left ? tr->left->height : -1;
    fB -= tr->right ? tr->right->height : -1;
    return fB;
}
int getHeight(AVLTree tr){
    int hLf = tr->left ? tr->left->height : -1;
    int hRt = tr->right ? tr->right->height : -1;
    return hLf > hRt ? hLf + 1 : hRt + 1;
}