/*
给定一棵二叉树的先序遍历序列和中序遍历序列，要求计算该二叉树的高度。

输入格式:
输入首先给出正整数N（≤50），为树中结点总数。下面两行先后给出先序和中序遍历序列，
均是长度为N的不包含重复英文字母（区别大小写）的字符串。

输出格式:
输出为一个整数，即该二叉树的高度。

输入样例:
9
ABDFGHIEC
FDHGIBEAC
输出样例:
5
*/
#include<iostream>
using namespace std;
constexpr int kLen = 64;
struct Node { char val; int lf, rt; } binT[kLen];
struct Elem { char val; bool chk; } inOrdSeq[kLen]{};
char preOrdSeq[kLen];
int N;

void reconstruct(int idx, int ptr, int lfLn, int rtLn);
int getHeight(int iN);
void preOrdTrvs(int iN);
void inOrdTrvs(int iN);

int main(){
    freopen("E:\\in.txt", "r", stdin);
    cin >> N >> ws >> preOrdSeq >> ws;
    for (int i = 0; i < N; ++i) cin >> inOrdSeq[i].val;
    for (int i = 0; i < N; ++i) binT[i].lf = binT[i].rt = -1;
    int j;
    for (j = 0; j < N; ++j) if (inOrdSeq[j].val == preOrdSeq[0]) break;
    reconstruct(0, j, j, ::N - j - 1);
    printf("PreOrder: ");
    preOrdTrvs(0);
    printf("\nInOrder : ");
    inOrdTrvs(0);
    printf("\nHeight = %d", getHeight(0));
}

void reconstruct(int idx, int ptr, int lfLn, int rtLn){
    int ptrLf, ptrRt, nLfLn, nRtLn,
        idxLf = idx + 1,        stpLf = ptr - lfLn,
        idxRt = idx + lfLn + 1, stpRt = ptr + rtLn;

    /*record current node;*/
    ::binT[idx].val = ::preOrdSeq[idx];
    ::inOrdSeq[ptr].chk = true;
    /*search left subtree;*/
    for (ptrLf = ptr - 1; ptrLf >= stpLf; --ptrLf){
        if (::preOrdSeq[idxLf] == ::inOrdSeq[ptrLf].val) break;
    }
    /*if new ptr of left subtree is found;*/
    if (ptrLf >= 0 && !::inOrdSeq[ptrLf].chk){
        ::binT[idx].lf = idxLf;
        nLfLn = nRtLn = 0;
        for (int j = ptrLf - 1; j >= 0 && !::inOrdSeq[j].chk; --j, ++nLfLn);
        for (int j = ptrLf + 1; j < ptr && !::inOrdSeq[j].chk; ++j, ++nRtLn);
        /*recursively reconstruct;*/
        reconstruct(idxLf, ptrLf, nLfLn, nRtLn);
    }
    
    /*search right subtree;*/
    for (ptrRt = ptr + 1; ptrRt <= stpRt; ++ptrRt){
        if (::preOrdSeq[idxRt] == ::inOrdSeq[ptrRt].val) break;
    }
    /*if new ptr of right subtree is found;*/
    if (ptrRt < ::N && !::inOrdSeq[ptrRt].chk){
        ::binT[idx].rt = idxRt;
        nLfLn = nRtLn = 0;
        for (int j = ptrRt - 1; j >= ptr && !::inOrdSeq[j].chk; --j, ++nLfLn);
        for (int j = ptrRt + 1; j < ::N && !::inOrdSeq[j].chk; ++j, ++nRtLn);
        reconstruct(idxRt, ptrRt, nLfLn, nRtLn);
    }
    return;
}
int getHeight(int iN){
    int h = 0, l = 0;
    if (binT[iN].lf != -1) h = getHeight(binT[iN].lf);
    if (binT[iN].rt != -1) l = getHeight(binT[iN].rt);
    return h > l ? h + 1 : l + 1;
}
void preOrdTrvs(int iN){
    printf("%c", binT[iN].val);
    if (binT[iN].lf != -1) preOrdTrvs(binT[iN].lf);
    if (binT[iN].rt != -1) preOrdTrvs(binT[iN].rt);
}
void inOrdTrvs(int iN){
    if (binT[iN].lf != -1) inOrdTrvs(binT[iN].lf);
    printf("%c", binT[iN].val);
    if (binT[iN].rt != -1) inOrdTrvs(binT[iN].rt);
}
