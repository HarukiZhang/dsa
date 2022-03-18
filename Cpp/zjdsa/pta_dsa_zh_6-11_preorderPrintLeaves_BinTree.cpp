#include<cstdio>

typedef char ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree();
void PreorderPrintLeaves(BinTree);

int main(){
    
    TNode node8 {'I', 0, 0};
    TNode node3 {'D', 0, 0};
    TNode node4 {'E', 0, 0};
    TNode node7 {'H', 0, 0};

    TNode node5 {'F', &node4, 0};
    TNode node6 {'G', 0, &node7};
    TNode node1 {'B', &node3, &node5};
    TNode node2 {'C', &node6, &node8};
    TNode node {'A', &node1, &node2};

    BinTree BT = &node;

    printf("Leaf nodes are:");
    PreorderPrintLeaves(BT);
    printf("\n");
    return 0;
}

void PreorderPrintLeaves(BinTree BT){
    if (!BT) return;
    BinTree stack[32], crtN = BT;
    int top = -1;
    while (crtN || top > -1){
        while (crtN){
            if (crtN->Right) stack[++top] = crtN->Right;
            else if (!crtN->Left) printf(" %c", crtN->Data);
            crtN = crtN->Left;
        }
        if (top > -1) crtN = stack[top--];
    }
    return;
}