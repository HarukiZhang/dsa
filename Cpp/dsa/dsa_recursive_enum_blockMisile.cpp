#include<cstdio>
#include"haruki.h"
// The complexity: o(2^n);
int mslN;

int blockMsl(int* a, int idx, int lastH){
    bool beAbleTo = a[idx] <= lastH;
    if (idx == mslN - 1){
        if (beAbleTo) return 1;
        return 0;
    }
    int max = 0, planTo = 1, curH;
    for (; planTo >= 0; --planTo){
        /* 
        For each missile, only when it is able to be blocked and we planned to,
            it is blocked;
        any other combination of two conditions leads to the misile unblocked;
        */
        if (beAbleTo && planTo)
            curH = a[idx];
        else {
            curH = lastH;
            planTo = 0;
        }
        int ret;
        for (int i = idx + 1; i < mslN; ++i){
            ret = planTo;
            ret += blockMsl(a, i, curH);
            if (ret > max) max = ret;
        }
    }
    return max;
}

int ms[32]{};
int main() {
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    LARGE_INTEGER t0, t1;
    
    int m;
    scanf("%d", &mslN);
    int hgt = 0;
    for (int i = 0; i < mslN; ++i){
        scanf("%d", &m);
        ms[i] = m;
        if (m > hgt) hgt = m;
    }

    QueryPerformanceCounter(&t0);
    int res = blockMsl(ms, 0, hgt);
    QueryPerformanceCounter(&t1);
    printf("%d", res);
    printPerfCounter(t0, t1, "total");
}