#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <Windows.h>
#include <cmath>

inline void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1) {
    LARGE_INTEGER fq;
    QueryPerformanceFrequency(&fq);
    double freq = (double)fq.QuadPart;
    double ts = (double)(t1.QuadPart - t0.QuadPart) / freq;
    if (ts < 1) {
        ts *= 1000;
        printf("\n\n------\nTime span: %.3f ms\n------\n", ts);
    }
    else printf("\n\n------\nTime span: %.3f s\n------\n", ts);
}

inline int getDigit(int num) {
    // return the exponent of digit on the base of ten;
    if (num == 0) return 0;
    int dig = 0;
    for (int quo = num / 10; quo > 0; quo /= 10) { dig++; }
    return dig;
}

inline int _countNum(int find, int a, int b) {
    if (a > b) return 0;
    int count = 0;
    for (int i = a; i <= b; i++) {
        for (int quo = i; quo > 0; quo /= 10) {
            if (quo % 10 == find) count++;
        }
    }
    return count;
}

inline int countNum(int find, int a, int b) {
    int sta = 0, mid = 0, tail = 0, pwsm = 0, pwbg = 0;

    int exp_a = getDigit(a);
    int exp_b = getDigit(b);

    if (exp_b - exp_a > 1) {
        mid = (exp_b * ((int)pow(10, exp_b - 1))) - ((exp_a + 1) * ((int)pow(10, exp_a)));
        pwsm = (int)pow(10, exp_a + 1);
        pwbg = (int)pow(10, exp_b);
        sta = _countNum(2, a, pwsm - 1);
        tail = _countNum(2, pwbg + 1, b);
    }
    else if (exp_b - exp_a == 1) {
        pwsm = (pwbg = (int)pow(10, exp_b));
        sta = _countNum(2, a, pwsm - 1);
        tail = _countNum(2, pwsm + 1, b);
    }
    else sta = _countNum(2, a, b);

    printf("%d\n", sta + mid + tail);
    printf("exp_a = %d\nexp_b = %d\nsta = %d\nmid = %d\ntail = %d\npwsm = %d\npwbg = %d",
        exp_a, exp_b, sta, mid, tail, pwsm, pwbg
    );
    return sta + mid + tail;
}

int main() {
    //freopen("E:\\Downloads\\in.txt", "r", stdin);
    LARGE_INTEGER t0, t1;
    
    int a, b;
    scanf("%d %d", &a, &b);
    
    QueryPerformanceCounter(&t0);

    //int count = 0;
    //for (int i = a; i <= b; i++) {
    //    for (int quo = i; quo > 0; quo /= 10) {
    //        if (quo % 10 == 2) count++;
    //    }
    //}
    //printf("%d", count);

    countNum(2, a, b);

    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t1);
}


/*

*/