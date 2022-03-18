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
    // freopen("E:\\in.txt", "r", stdin);

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
    else if (X > BST->Data) BST->Right = Insert(BST->Right, X);
    else if (X < BST->Data) BST->Left = Insert(BST->Left, X);
    //if equal value exists, do nothing;
    return BST;
}
BinTree Delete( BinTree BST, ElementType X ){
    if (!BST) printf("Not Found\n");
    else if (X > BST->Data) BST->Right = Delete(BST->Right, X);
    else if (X < BST->Data) BST->Left = Delete(BST->Left, X);
    else {
        if (BST->Left && BST->Right){
            BST->Data = FindMax(BST->Left)->Data;
            BST->Left = Delete(BST->Left, BST->Data);//BST-Data has now been replaced;
        }
        else {
            BinTree child = NULL;
            if (BST->Left) child = BST->Left;
            else if (BST->Right) child = BST->Right;
            free(BST);
            BST = child;
        }
    }
    return BST;
}
Position Find( BinTree BST, ElementType X ){
    if (BST){
        if (X > BST->Data) return Find(BST->Right, X);
        else if (X < BST->Data) return Find(BST->Left, X);
    }
    return BST;
}
Position FindMin( BinTree BST ){
    if (BST && BST->Left) return FindMin(BST->Left);
    return BST;
}
Position FindMax( BinTree BST ){
    if (BST && BST->Right) return FindMax(BST->Right);
    return BST;
}


/*Auxiliary codes*/
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