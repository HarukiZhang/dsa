#include<cstdio>
#include<cmath>

using namespace std;

int buff[1010], binTree[1010];

void reconstruct(int* buf, int len, int idx);
int getLeftLen(int numTot);
void sort(int* begin, int* end);
void traversal_lv(int* binT, int num);
int min(int a, int b){ return a < b ? a : b; }
void swap(int& a, int& b){ int t = a; a = b; b = t; }

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%d", &buff[i]);
    sort(buff, buff + N);
    reconstruct(buff, N, 0);
    traversal_lv(binTree, N);
    return 0;
}

void reconstruct(int* buf, int len, int idx){
    if (len == 0) return;
    int lfLn = getLeftLen(len);
    ::binTree[idx] = buf[lfLn];
    reconstruct(buf, lfLn, idx * 2 + 1);
    reconstruct(buf + lfLn + 1, len - lfLn - 1, idx * 2 + 2);
    return;
}

int getLeftLen(int numTot){
    int height, topsideFull, bottomLeft;
    height = floor(log2(numTot + 1));
    topsideFull = pow(2, height) - 1;
    bottomLeft = min(numTot - topsideFull, (int)pow(2, height - 1));
    return (int)pow(2, height - 1) - 1 + bottomLeft;
}

void sort(int* begin, int* end){
    if (begin >= end) return;
    int k = *begin;
    int* iLf = begin;
    int* iRt = end - 1;
    while (iLf < iRt){
        while (iLf < iRt && *iRt >= k) --iRt;
        swap(*iLf, *iRt);
        while (iLf < iRt && *iLf <= k) ++iLf;
        swap(*iLf, *iRt);
    }
    sort(begin, iLf);
    sort(iLf + 1, end);
    return;
}

void traversal_lv(int* binT, int num){
    printf("%d", binT[0]);
    for (int i = 1; i < num; ++i) printf(" %d", binT[i]);
    return;
}