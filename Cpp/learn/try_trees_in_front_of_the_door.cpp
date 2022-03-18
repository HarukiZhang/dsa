#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include <unordered_set>
#include <map>

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&);

int main() {
    freopen("in.txt", "r", stdin);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //------------------------------------------------
    
    std::multimap<int, int> mymap;
    int llen, line, llim, rlim, count = 0;
    scanf("%d %d", &llen, &line);
    for (int i = 0; i < line; i++) {
        scanf("%d %d", &llim, &rlim);
        mymap.insert(std::make_pair(llim, rlim));
    }
    auto map_it = mymap.begin(), map_ite = mymap.end();
    for (int max_rlim = -1; map_it != map_ite; map_it++) {
        rlim = map_it->second;
        llim = map_it->first;
        for (int i = rlim; i >= llim; i--) {
            if (i <= max_rlim) break;
            count++;
        }
        if (rlim > max_rlim) max_rlim = rlim;
    }
    llen += 1;
    int res = llen - count;
    if (res < 0) res = 0;
    printf("%d", res);

    //------------------------------------------------
    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t1);
}

/*
0-18¡¢19-35¡¢36-60¡¢61ÒÔÉÏ£¨º¬61£©ËÄ
*/

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