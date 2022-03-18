#include<iostream>

using namespace std;

constexpr int kLen = 52;
struct TNode { char data; int lf, rt, inOrd; } binT[kLen];
char preOrd[kLen];

/*The simplest way to define the subtree len is to give starting ptr of sequence
    and the len of subtree (only two parameter);
Store subtree ptr in form of idx with inorder;
In order to obtain absolute idx but not relative idx within recursion, 
    set an individual field for input order within each TNode;*/
int reconstruct(char* preBuf, TNode* inBuf, int subLn){
    if (subLn == 0) return -1;
    int idx = 0, lfLn;
    while (idx < subLn && preBuf[0] != inBuf[idx].data) ++idx;
    lfLn = idx;
    inBuf[idx].lf = reconstruct(preBuf + 1, inBuf, lfLn);
    inBuf[idx].rt = reconstruct(preBuf + 1 + lfLn, inBuf + lfLn + 1, subLn - lfLn - 1);
    return inBuf[idx].inOrd;//input order (absolute loc), not relative loc;
}
int getHeight(int n){
    int hLf = 0, hRt = 0;
    if (::binT[n].lf != -1) hLf = getHeight(::binT[n].lf);
    if (::binT[n].rt != -1) hRt = getHeight(::binT[n].rt);
    return hLf > hRt ? hLf + 1 : hRt + 1;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);

    int N;
    cin >> N >> ws >> preOrd >> ws;
    for (int i = 0; i < N; ++i){
        cin >> binT[i].data;
        binT[i].inOrd = i;
        binT[i].lf = binT[i].rt = -1;
    }
    int iRoot = reconstruct(preOrd, binT, N);
    cout << getHeight(iRoot);
}