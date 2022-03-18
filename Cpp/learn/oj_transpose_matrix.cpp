#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <array>
#include <cmath>

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&, const char*);

struct Matrix {
    int row;
    int col;
    int* entry;
};

void transposeMatrix(Matrix& mtx) {
    int mtx_size = (mtx.row + 1) * (mtx.col + 1);
    int* mtx_buffer = new int[mtx_size]{};
    for (int i = 0; i < mtx.row; i++) {
        for (int offset1, offset2, j = 0; j < mtx.col; j++) {
            offset1 = j * mtx.row + i;
            offset2 = i * mtx.col + j;
            *(mtx_buffer + offset1) = *(mtx.entry + offset2);
        }
    }
    memcpy(mtx.entry, mtx_buffer, mtx_size * sizeof(int));
    int new_row = mtx.col;
    mtx.col = mtx.row;
    mtx.row = new_row;
    delete[] mtx_buffer;
}

void printMatrix(const Matrix& mtx) {
    for (int i = 0; i < mtx.row; i++) {
        for (int offset, j = 0; j < mtx.col; j++) {
            offset = i * mtx.col + j;
            printf("%d\t", *(mtx.entry + offset));
        }
        printf("\n");
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //----------------------------------------------------------------

    int row, col;
    scanf("%d %d", &row, &col);
    int dynamic_range = (row + 1) * (col + 1);
    int* pMtx = new int[dynamic_range]{};
    Matrix mtx = { row, col, pMtx };
    for (int i = 0; i < row; i++) {
        for (int input, offset, j = 0; j < col; j++) {
            scanf("%d", &input);
            offset = i * col + j;
            *(pMtx + offset) = input;
        }
    }
    
    printMatrix(mtx);

    transposeMatrix(mtx);

    printMatrix(mtx);

    //for (int i = 0; i < col; i++) {
    //    for (int offset, j = 0; j < row; j++) {
    //        offset = (i * row) + j;
    //        printf("%d\t", *(pMtx + offset));
    //    }
    //    printf("\n");
    //}

    delete[] pMtx;
    //----------------------------------------------------------------
    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t1, "Total  ");
}

/*
输入一个n行m列的矩阵A，输出它的转置AT。

输入
第一行包含两个整数n和m，表示矩阵A的行数和列数。1 <= n <= 100，1 <= m <= 100。
接下来n行，每行m个整数，表示矩阵A的元素。相邻两个整数之间用单个空格隔开，每个元素均在1~1000之间。
输出
m行，每行n个整数，为矩阵A的转置。相邻两个整数之间用单个空格隔开。
样例输入
3 3
1 2 3 1
4 5 6 1
7 8 9 1
样例输出
1 4 7
2 5 8
3 6 9
1 1 1
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