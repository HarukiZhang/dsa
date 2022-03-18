#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include <cstring>

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&, const char*);

int main() {
    freopen("in.txt", "r", stdin);
    LARGE_INTEGER t0, t1, t2, t3, t4;
    QueryPerformanceCounter(&t0);
    //----------------------------------------------------------------
    
    int llen, line, llim, rlim, count = 0;
    scanf("%d %d", &llen, &line);
    char* road = new char[llen + 10](); // if allocation is failed, exception will be raised

    QueryPerformanceCounter(&t2);
    
    for (int i = 0; i < line; i++) {
        scanf("%d %d", &llim, &rlim);
        memset(road + llim, 1, rlim - llim + 1);
    }

    QueryPerformanceCounter(&t3);

    for (int i = 0; i <= llen; i++)
        if (*(road + i) == 1)
            count++;
    int res = llen + 1 - count;
    printf("%d", res);

    QueryPerformanceCounter(&t4);

    delete[] road;

    //----------------------------------------------------------------
    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t2, " Array Allocation ");
    printPerfCounter(t2, t3, "      Loop memset ");
    printPerfCounter(t3, t4, "    Tree Counting ");
    printPerfCounter(t4, t1, "     Deallocation ");
    printPerfCounter(t0, t1, "            Total ");
}

/*

*/

inline void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1, const char* tag_name) {
    static double freq = -1;
    if (freq == -1) {
        LARGE_INTEGER fq;
        QueryPerformanceFrequency(&fq);
        freq = (double)fq.QuadPart;
        printf("\n\n-----------------------------\n");
    }
    double ts = (double)(t1.QuadPart - t0.QuadPart) / freq;
    if (ts < 1) {
        ts *= 1000;
        printf("%s: %.3f ms\n-----------------------------\n", tag_name, ts);
    }
    else printf("%s: %.3f s\n-----------------------------\n", tag_name, ts);
}