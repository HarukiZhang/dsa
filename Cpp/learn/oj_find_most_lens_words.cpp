#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include <set>

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&, const char*);

struct Word {
    int order;
    size_t wordLen;
    char wd[110];
};
struct Rule {
    bool operator() (const Word& wd1, const Word& wd2) const {
        if (wd1.wordLen != wd2.wordLen) return wd1.wordLen < wd2.wordLen;
        else return wd1.order < wd2.order;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //----------------------------------------------------------------
    
    std::set<Word, Rule> myset;
    Word tmp;
    for (int i = 0; scanf("%s", tmp.wd) != EOF; i++) {
        tmp.order = i;
        strtok(tmp.wd, ",.!");
        tmp.wordLen = strlen(tmp.wd);
        myset.insert(tmp);
    }
    //auto itbg = myset.begin();
    //auto it = myset.end();
    //size_t maxWdLen = (--it)->wordLen;
    //for (; it->wordLen == maxWdLen; it--) {
    //    if (it == itbg) {
    //        printf("%s\n%s", (*itbg).wd, (*itbg).wd);
    //        return 0;
    //    }
    //}
    //printf((*(++it)).wd);
    //printf("\n");
    //printf((*itbg).wd);
    printf("Order\tStrlen\tWord\n");
    for (auto it = myset.begin(); it != myset.end(); it++) {
        printf("%d\t%llu\t%s\n", it->order, it->wordLen, it->wd);
    }


    //----------------------------------------------------------------
    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t1, "Total  ");
    fclose(stdin);
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