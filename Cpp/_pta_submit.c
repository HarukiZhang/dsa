#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT );
void InorderTraversal( BinTree BT );

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

void freeBinTree(BinTree& BT);

int main()
{
    freopen("E:\\in.txt", "r", stdin);

    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    freeBinTree(BST);

    return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert( BinTree BST, ElementType X ){
    if (!BST){
        BST = (BinTree)calloc(1, sizeof(struct TNode));
        BST->Data = X;
    }
    else {
        Position crtN = BST;
        while (1){
            if (X > crtN->Data){
                if (crtN->Right) crtN = crtN->Right;
                else {
                    crtN->Right = (BinTree)calloc(1, sizeof(struct TNode));
                    crtN->Right->Data = X;
                    break;
                }
            }
            else if (X < crtN->Data){
                if (crtN->Left) crtN = crtN->Left;
                else {
                    crtN->Left = (BinTree)calloc(1, sizeof(struct TNode));
                    crtN->Left->Data = X;
                    break;
                }
            }
            else break;//no need to insert an equal value;
        }
    }
    return BST;
}
BinTree Delete( BinTree BST, ElementType X ){
    /*Find(X);*/
    Position toDel = BST, parent = NULL;
    while (toDel){
        if (X > toDel->Data){
            parent = toDel;
            toDel = toDel->Right;
        }
        else if (X < toDel->Data){
            parent = toDel;
            toDel = toDel->Left;
        }
        else break;//target found;
    }
    if (toDel){
        /*Situ1: leaf node or degree 1 node*/
        if (!toDel->Left || !toDel->Right){
            Position descendant = toDel->Left ? toDel->Left : toDel->Right;
            if (parent){
                if (parent->Left == toDel) parent->Left = descendant;
                else parent->Right = descendant;
            }
            else BST = descendant;
            free(toDel);
        }
        /*Situ2: degree 2 node*/
        else {
            /*Find max in left-subtree;*/
            Position maxN = toDel->Left, maxPrt = toDel;
            while (maxN->Right){
                maxPrt = maxN;
                maxN = maxN->Right;
            }
            /*Subtitute toDel with the value of maxN;*/
            toDel->Data = maxN->Data;
            /*Then the problem has been converted to delete maxN;*/
            Position tmp = NULL;
            if (maxN->Left) tmp = maxN->Left;
            if (maxPrt->Left == maxN) maxPrt->Left = tmp;
            else maxPrt->Right = tmp;
            free(maxN);
        }
    }
    else printf("Not Found\n");
    return BST;
}
Position Find( BinTree BST, ElementType X ){
    Position crtN = BST;
    while (crtN){
        if (X > crtN->Data) crtN = crtN->Right;
        else if (X < crtN->Data) crtN = crtN->Left;
        else break;//found an equal positon;
    }
    return crtN;
}
Position FindMin( BinTree BST ){
    Position crtP = BST;
    if (crtP) while (crtP->Left) crtP = crtP->Left;
    return crtP;
}
Position FindMax( BinTree BST ){
    Position crtP = BST;
    if (crtP) while (crtP->Right) crtP = crtP->Right;
    return crtP;
}



void PreorderTraversal( BinTree BT ){
    if (BT){
        printf(" %d", BT->Data);
        if (BT->Left) PreorderTraversal(BT->Left);
        if (BT->Right) PreorderTraversal(BT->Right);
    }
    return;
}
void InorderTraversal( BinTree BT ){
    if (BT){
        if (BT->Left) InorderTraversal(BT->Left);
        printf(" %d", BT->Data);
        if (BT->Right) InorderTraversal(BT->Right);
    }
    return;
}
void freeBinTree(BinTree& BT){
    if (BT){
        if (BT->Left) freeBinTree(BT->Left);
        if (BT->Right) freeBinTree(BT->Right);
        free(BT);
    }
    return;
}