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
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
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
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert( BinTree BST, ElementType X ){
    if (BST == NULL){
        BST = (BinTree)calloc(1, sizeof(struct TNode));//initialize all bits 0;
        BST->Data = X;
    }
    else if (X < BST->Data){
        BST->Left = Insert( BST->Left, X );
    }
    else {
        BST->Right = Insert( BST->Right, X );
    }
    return BST;
}

BinTree Delete( BinTree BST, ElementType X ){
    if (BST == NULL){//if no X in BINTREE;
        printf("Not Found\n");
    }
    else if (X < BST->Data){
        BST->Left = Delete( BST->Left, X );
    }
    else if (X > BST->Data){
        BST->Right = Delete( BST->Right, X );
    }
    else {//X is found;
        if ( BST->Left != NULL ){//if at-least BST has left subTree;
            BST->Data = FindMax( BST->Left )->Data;//substitue with max in left subtree;
            /*delete */
            BST->Left = Delete( BST->Left, BST->Data );
        }
        else if (BST->Right != NULL){//if only has right subTree;
            BST->Data = FindMin( BST->Right )->Data;
            BST->Right = Delete( BST->Right, BST->Data );
        }
        else {//if degree == 0;
            free(BST);
            BST = NULL;
        }
    }
    return BST;
}

Position Find( BinTree BST, ElementType X ){
    if (BST != NULL){
        if (X < BST->Data)
            return Find(BST->Left, X);
        else if (X > BST->Data)
            return Find(BST->Right, X);
    }
    return BST;
}

Position FindMin( BinTree BST ){
    if (BST && BST->Left != NULL){
        return FindMin( BST->Left );
    }
    else return BST;
}

Position FindMax( BinTree BST ){
    if (BST && BST->Right != NULL){
        return FindMax( BST->Right );
    }
    else return BST;
}


void PreorderTraversal( BinTree BT ){
    if (BT != NULL){
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
    return;
}

void InorderTraversal( BinTree BT ){
    if (BT != NULL){
        InorderTraversal(BT->Left);
        printf(" %d", BT->Data);
        InorderTraversal(BT->Right);
    }
    return;
}
