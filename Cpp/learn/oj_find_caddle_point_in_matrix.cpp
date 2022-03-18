#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include <cstring>

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&, const char*);

void searchMatrix(int* mtx_entry, int* max_nums) {
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++) {
            if (*(mtx_entry + ((i * 5) + k)) == *(max_nums + i)) {
                int min = *(mtx_entry + ((i * 5) + k));
                int m = 0;
                for (; m < 5; m++) {
                    if (min > *(mtx_entry + ((m * 5) + k))) break;
                }
                if (m == 5) {
                    printf("%d %d %d", i + 1, k + 1, min);
                    return;
                }
                break;
            }
        }
    }
    printf("not found");
}

int main() {
    freopen("in.txt", "r", stdin);
    LARGE_INTEGER t0, t1, t2;
    QueryPerformanceCounter(&t0);
    //----------------------------------------------------------------

    int mtx[5][5] = {};
    int max_nums[5] = {};
    for (int i = 0; i < 5; i++) {
        int input;
        scanf("%d", &input);
        int max = input;
        *(mtx[0] + (i * 5)) = input;
        for (int k = 1; k < 5; k++) {
            scanf("%d", &input);
            if (input > max) max = input;
            *(mtx[0] + ((i * 5) + k)) = input;
        }
        *(max_nums + i) = max;
    }

    QueryPerformanceCounter(&t2);

    searchMatrix(mtx[0], max_nums);

    //QueryPerformanceCounter(&t3);


    //QueryPerformanceCounter(&t4);


    //----------------------------------------------------------------
    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t2, "Input ");
    printPerfCounter(t2, t1, "Count ");
    printPerfCounter(t0, t1, "Total ");
}

/*
����һ��5*5�ľ���ÿ��ֻ��һ�����ֵ��ÿ��ֻ��һ����Сֵ��Ѱ���������İ��㡣
����ָ���Ǿ����е�һ��Ԫ�أ����������е����ֵ�������������е���Сֵ��
���磺������������У���4�е�1�е�Ԫ�ؾ��ǰ��㣬ֵΪ8 ����
11 3 5 6 9
12 4 7 8 10
10 5 6 9 11
8 6 4 7 2
15 10 11 20 25

����
�������һ��5��5�еľ���
���
������ڰ��㣬����������ڵ��С��м���ֵ����������ڣ����"not found"
��������
11 3 5 6 9
12 4 7 8 10
10 5 6 9 11
8  6 4 7 2
15 10 11 20 25
�������
4 1 8
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