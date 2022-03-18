#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
int GetHeight( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("%d\n", GetHeight(BT));
    return 0;
}
/* 你的代码将被嵌在这里 */
/*Recursion*/
int GetHeight( BinTree BT ){
    if (!BT) return 0;
    int lf, rt;
    if (BT->Left) lf = GetHeight(BT->Left);
    else lf = 0;
    if (BT->Right) rt = GetHeight(BT->Right);
    else rt = 0;
    return (lf > rt) ? lf + 1 : rt + 1;
}

/*Non-Recursion*/
int GetHeight( BinTree BT ){
    if (!BT) return 0;
    const int qLen = 16;
    BinTree bTQueue[qLen], crtB;
    int hQueue[qLen], crtH, front = 0, back = -1, maxH = 0;
    ++back; bTQueue[back] = BT; hQueue[back] = 1;
    while ((back + 1) % qLen != front){
        crtB = bTQueue[front];
        crtH = hQueue[front];
        front = (front + 1) % qLen;
        if (crtB->Left){
            back = (back + 1) % qLen;
            bTQueue[back] = crtB->Left;
            hQueue[back] = crtH + 1;
        }
        if (maxH < crtH) maxH = crtH;
        if (crtB->Right){
            back = (back + 1) % qLen;
            bTQueue[back] = crtB->Right;
            hQueue[back] = crtH + 1;
        }
    }
    return maxH;
}