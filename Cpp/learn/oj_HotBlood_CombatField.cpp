#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstring>
#include <iostream>

#include <map>
#include <cstdlib>

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&, const char*);

void verifyAnwser(const char*, const char*);

int main() {
    freopen("E:\\Downloads\\in (3).txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //-----------------------------main codes below-----------------------------------
    
    std::map<int, int> memsht; //first:attack; second:memID;
    memsht.insert(std::make_pair(1000000000, 1));
    int nMem;
    scanf("%d", &nMem);
    for (int i = 0; i < nMem; i++) {
        int memId, memAtt;
        scanf("%d %d", &memId, &memAtt);
        int idApprop; //firstly search for appropriate member ID in the map;
        auto itLowB = memsht.lower_bound(memAtt);
        if (itLowB == memsht.begin()) idApprop = itLowB->second;
        else if (itLowB == memsht.end()) idApprop = (--itLowB)->second;
        else {
            auto itAft = itLowB;
            auto itBef = --itLowB;
            int distA = abs(itAft->first - memAtt);
            int distB = abs(itBef->first - memAtt);
            if (distA != distB)
                idApprop = (distA < distB) ? itAft->second : itBef->second;
            else idApprop = itBef->second;
        }
        printf("%d %d\n", memId, idApprop);
        //then consider insert the present member;
        memsht.insert(std::make_pair(memAtt, memId));
    }

    //-----------------------------main codes above-----------------------------------
    QueryPerformanceCounter(&t1);

    freopen("CON", "a", stdout);

    printf("\n--------------- Main complete. ---------------\n");
    printPerfCounter(t0, t1, "Total  ");

    verifyAnwser("E:\\Downloads\\out (3).txt", "out.txt");
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

/*
为了迎接08年的奥运会，让大家更加了解各种格斗运动，facer新开了一家热血格斗场。
格斗场实行会员制，但是新来的会员不需要交入会费，而只要同一名老会员打一场表演赛，证明自己的实力。

我们假设格斗的实力可以用一个正整数表示，成为实力值。另外，每个人都有一个唯一的id，也是一个正整数。
为了使得比赛更好看，每一个新队员都会选择与他实力最为接近的人比赛，即比赛双方的实力值之差的绝对值越小越好，
如果有两个人的实力值与他差别相同，则他会选择比他弱的那个（显然，虐人必被虐好）。

不幸的是，Facer一不小心把比赛记录弄丢了，但是他还保留着会员的注册记录。
现在请你帮facer恢复比赛纪录，按照时间顺序依次输出每场比赛双方的id。

输入
第一行一个数n(0 < n <=100000)，表示格斗场新来的会员数（不包括facer）。
以后n行每一行两个数，按照入会的时间给出会员的id和实力值。
一开始，facer就算是会员，id为1，实力值1000000000。
输入保证两人的实力值不同。

输出
N行，每行两个数，为每场比赛双方的id，新手的id写在前面。

样例输入
3
2 1
3 3
4 2
样例输出
2 1
3 2
4 2
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

constexpr unsigned short kArrSize_vfAws = 20;
void verifyAnwser(const char* dir1, const char* dir2) {
    FILE* f1 = fopen(dir1, "r");
    FILE* f2 = fopen(dir2, "r");
    char line1[kArrSize_vfAws], line2[kArrSize_vfAws];
    for (int i = 0; fgets(line2, kArrSize_vfAws, f2) != NULL; i++) {
        fgets(line1, kArrSize_vfAws, f1);
        if (strcmp(line1, line2) != 0) {
            printf("\n-----------------------------------------------------");
            printf("\nWrong in line %d. Please try again, Master Haruki.", i);
            printf("\n-----------------------------------------------------");
            fclose(f1);
            fclose(f2);
            return;
        }
    }
    printf("\n---------------------------------------------");
    printf("\nAll correct! Congradulations, master Haruki~!");
    printf("\n---------------------------------------------");
    fclose(f1);
    fclose(f2);
    return;
}