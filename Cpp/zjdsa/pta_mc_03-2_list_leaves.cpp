#include<cstdio>
#include<cmath>
#include<queue>

constexpr int kMaxNodeNum = 10;
constexpr int kMaxQueueLen(int totalNodeNum){
    /*concurrent node num in the queue*/
    return (int)pow(2, floor(log2(totalNodeNum + 1)));
}

class TNode {
    friend class BinTree;
public:
private:
    char lchild, rchild;
};

class BinTree {
public:
    using Tree = TNode;
    BinTree(int sz)
        :size(sz)
    {
        insert();
    }
    void insert();
    void printLeaves();
private:
    int size;
    Tree tree[kMaxNodeNum + 2]{};
    int entry = 0;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N;
    scanf("%d ", &N);
    BinTree bTree { N };
    bTree.printLeaves();
    return 0;
}

void BinTree::insert(){
    /*initial entry = cumulative sum of indice of all nodes*/
    for (int i = 0; i < size; ++i) entry += i;
    char left, right;
    for (int i =0; i < size; ++i){
        scanf("%c %c ", &tree[i].lchild, &tree[i].rchild);
        /*if no child, child = '-' - '0' = -2;*/
        tree[i].lchild -= '0';
        tree[i].rchild -= '0';
        /*modify entry*/
        entry -= tree[i].lchild < 0 ? 0 : tree[i].lchild;
        entry -= tree[i].rchild < 0 ? 0 : tree[i].rchild;
    }
    return;
}

void BinTree::printLeaves(){
    bool firstTime = true;

    const int qLen = 32;
    char queue[qLen]{};
    int front = 0, back = -1;

    queue[++back] = (char)entry;

    while ((back + 1) % qLen != front){
        char crt = queue[front++ % qLen];
        if (tree[crt].lchild >= 0) queue[++back % qLen] = tree[crt].lchild;
        if (tree[crt].rchild >= 0) queue[++back % qLen] = tree[crt].rchild;
        else if (tree[crt].lchild < 0){//no rchild and no lchild;
            if (firstTime) firstTime = false;
            else printf(" ");
            printf("%d", (int)crt);
        }
    }
    return;
}