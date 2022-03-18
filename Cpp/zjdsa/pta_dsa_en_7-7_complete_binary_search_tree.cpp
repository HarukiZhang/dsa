/*Now given a sequence of distinct non-negative integer keys, 
a unique BST can be constructed if it is required that the tree must also be a CBT. 
You are supposed to output the level order traversal sequence of this BST.*/
/*Logic:
The sequence of inOrder traversal of a complete BST is equivalent to a sorted seq;
Therefore, given total nodes num and values, the problem becomes how to find
    the idx of root node according to the properties of complete BST and the 
    total num of nodes;
According to the property of BST, the left subtree of a node contains only
    nodes with keys less than the node's key; So, the number of nodes in left 
    subtree constitutes the index of its root node, when the value sequence 
    is sorted;
Because 1) for a BST, the bottom level's node number will always be an even number;
    2) for a complete BST, all levels except for the bottom level consist of 
    full BST,
    the num of nodes in left subtree of the original root is countable as:
        node num of full BST with [height - 1] + node num in left side of bottom
*/
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>

using namespace std;

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    int data;
    BinTree left, right;
};

int buff[1010];
queue<BinTree> myQue;

BinTree reconstruct(int* buf, int num);
void freeBinTree(BinTree tr);
void traverse_lv(BinTree tr);

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
        scanf("%d", &buff[i]);
    sort(buff, buff + N);
    
    BinTree binT = reconstruct(buff, N);
    traverse_lv(binT);
    freeBinTree(binT);

    return 0;
}

BinTree reconstruct(int* buf, int num){
    if (num == 0) return nullptr;
    /*variable explanation:
    lv : potential level of current tree;
    nFBT : total num of nodes in a Full Binary Tree respect to the potential level;
    oprd : used for counting the number of nodes at each level;
    bottomFull : respect to the potential level (above-counted),
        the num of nodes that is at the bottom level if it is a Full BST;
    bottomLeft : respect to current num of nodes, the num of nodes that will be at the
        bottom level if it is constructed as a complete BST;
    offset : records the devient between the expected num of nodes in the
        left side of bottom level, and the actural number of it;
        so that if offset > 0, the idx should minus this offset for correction;
    idx : point to the location of the root in the parameter buf;
        and this value is equal to the total number of nodes in the subtree of root; */
    int lv, nFBT, oprd, bottomFull, bottomLeft, offset, idx;
    /*Search for the idx of root;*/
    lv = nFBT = oprd = 1;
    /*count the level of BST;*/
    while (nFBT < num){ oprd <<= 1; nFBT += oprd; ++lv; }
    bottomFull = pow(2, lv - 1);
    bottomLeft = bottomFull - (nFBT - num);
    offset = bottomFull / 2 - bottomLeft;
    idx = nFBT / 2;//expected value of idx;
    if (offset > 0) idx -= offset;//minus actual offset;
    /*reconstrct binTree*/
    BinTree bt = new TNode {buf[idx], 0, 0};
    bt->left = reconstruct(buf, idx);
    bt->right = reconstruct(buf + idx + 1, num - idx - 1);
    return bt;
}

void freeBinTree(BinTree tr){
    if (tr){
        if (tr->left) freeBinTree(tr->left);
        if (tr->right) freeBinTree(tr->right);
        delete tr;
    }
    return;
}

void traverse_lv(BinTree tr){
    if (tr){
        BinTree crtN = tr;
        printf("%d", crtN->data);
        if (crtN->left) myQue.push(crtN->left);
        if (crtN->right) myQue.push(crtN->right);
        while (!::myQue.empty()){
            crtN = myQue.front(); myQue.pop();
            printf(" %d", crtN->data);
            if (crtN->left) myQue.push(crtN->left);
            if (crtN->right) myQue.push(crtN->right);
        }
    }
}