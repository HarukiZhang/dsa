#include <cstdio>
#include <cstdlib>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );

int main()
{
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

    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}
/* 你的代码将被嵌在这里 */

void InorderTraversal( BinTree BT ){
    if (BT){
        InorderTraversal( BT->Left );
        printf(" %c", BT->Data);
        InorderTraversal( BT->Right );
    } else return;
}
void PreorderTraversal( BinTree BT ){
    if (BT){
        printf(" %c", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    } else return;
}
void PostorderTraversal( BinTree BT ){
    if (BT){
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        printf(" %c", BT->Data);
    } else return;
}
void LevelorderTraversal( BinTree BT ){
    if (BT){
        const int qLen = 32;
        BinTree crt, queue[qLen];
        int front = 0, back = -1;
        queue[++back] = BT;
        while ((back + 1) & qLen != front){//both idx monotone increasing;
            crt = queue[front++ % qLen];
            printf(" %c", crt->Data);
            if (crt->Left) queue[++back % qLen] = crt->Left;
            if (crt->Right) queue[++back % qLen] = crt->Right;
        }
    }
    return;
}


/*Non-recur*/
void InorderTraversal( BinTree BT ){
    BinTree stack[32],
        crtN = BT;//crt ptr to BT root;
    int top = -1;
    while (crtN || top > -1){
        while (crtN){//judge crt node whether null;
            stack[++top] = crtN;//push crt node;
            crtN = crtN->Left;//go to left subtree;
        }
        if (top > -1){//if stack not empty;
            crtN = stack[top--];
            /*visit bintree data;*/
            printf(" %c", crtN->Data);
            crtN = crtN->Right;//go to right subtree;
        }
    }
    return;
}
void PreorderTraversal( BinTree BT ){
    BinTree stack[32], crtN = BT;
    int top = -1;
    while (crtN || top > -1){
        while (crtN){
            printf(" %c", crtN->Data);
            if (crtN->Right) stack[++top] = crtN->Right;
            crtN = crtN->Left;
        }
        if (top > -1) crtN = stack[top--];
    }
    return;
}
void PostorderTraversal( BinTree BT ){
    BinTree stack[32], crtN = BT, last = NULL;
    int top = -1;
    while (crtN || top > -1){
        while (crtN){
            stack[++top] = crtN;
            crtN = crtN->Left;
        }
        crtN = stack[top];
        if (!crtN->Right || crtN->Right == last){
            printf(" %c", crtN->Data);
            --top;
            last = crtN;
            crtN = NULL;
        }
        else crtN = crtN->Right;
    }
    return;
}