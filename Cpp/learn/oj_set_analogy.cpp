#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&, const char*);

void verifyAnwser(const char*, const char*);

struct ElemInSet {
    int elem;
    int num;
};

int main() {
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //----------------------------------------------------------------
    
    unordered_map<int, int> dtbs;
    int nTot, tmpelem;
    cin >> nTot;
    char cmdstr[5];
    for (int i = 0; i < nTot; i++) {
        cin.get(cmdstr, 5, ' ');
        cin >> tmpelem;
        if (strcmp(cmdstr, "\nadd") == 0){
            dtbs[tmpelem]++;
            cout << dtbs[tmpelem] << endl;
        }
        else if (strcmp(cmdstr, "\ndel") == 0){
            auto it = dtbs.find(tmpelem);
            if (it != dtbs.end()) {
                int nElem = dtbs[tmpelem];
                dtbs[tmpelem] = 0;
                cout << nElem << endl;
            }
            else cout << 0 << endl;
        }
        else if (strcmp(cmdstr, "\nask") == 0){
            auto it = dtbs.find(tmpelem);
            if (it != dtbs.end()) {
                int nElem = dtbs[tmpelem];
                cout << "1 " << nElem << endl;
            }
            else cout << "0 0" << endl;
        }
    }

    //----------------------------------------------------------------
    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t1, "Total  ");
    fclose(stdin);
    //fclose(stdout);
    //verifyAnwser();
    return 0;
}

/*
现有一整数集（允许有重复元素），初始为空。我们定义如下操作：
add x 把x加入集合
del x 把集合中所有与x相等的元素删除
ask x 对集合中元素x的情况询问
对每种操作，我们要求进行如下输出。
add 输出操作后集合中x的个数
del 输出操作前集合中x的个数
ask 先输出0或1表示x是否曾被加入集合（0表示不曾加入），再输出当前集合中x的个数，中间用空格格开。
输入
第一行是一个整数n，表示命令数。0<=n<=100000。
后面n行命令，如Description中所述。
输出
共n行，每行按要求输出。
样例输入
7
add 1
add 1
ask 1
ask 2
del 2
del 1
ask 1
样例输出
1
2
1 2
0 0
0
2
1 0
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

void verifyAnwser(const char* dir1, const char* dir2) {
    FILE* f1 = fopen(dir1, "r");
    FILE* f2 = fopen(dir2, "r");
    char line1[10], line2[10];
    for (int i = 0; fscanf(f2, "%s", line2) != EOF; i++) {
        fscanf(f1, "%s", line1);
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