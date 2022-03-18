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
����һ���������������ظ�Ԫ�أ�����ʼΪ�ա����Ƕ������²�����
add x ��x���뼯��
del x �Ѽ�����������x��ȵ�Ԫ��ɾ��
ask x �Լ�����Ԫ��x�����ѯ��
��ÿ�ֲ���������Ҫ��������������
add ��������󼯺���x�ĸ���
del �������ǰ������x�ĸ���
ask �����0��1��ʾx�Ƿ��������뼯�ϣ�0��ʾ�������룩���������ǰ������x�ĸ������м��ÿո�񿪡�
����
��һ����һ������n����ʾ��������0<=n<=100000��
����n�������Description��������
���
��n�У�ÿ�а�Ҫ�������
��������
7
add 1
add 1
ask 1
ask 2
del 2
del 1
ask 1
�������
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