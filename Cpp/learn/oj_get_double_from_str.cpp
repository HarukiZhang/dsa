#include "haruki.h"

#include <iostream>
#include <iomanip>

using namespace std;

double GetDoubleFromString(char* str)
{
    static char* start;
    static int strln;
    if (str != NULL) {
        start = str;
        for (strln = 0; *(str + strln) != 0; strln++);
        strln--;
    }
    if (strln <= 0) return 0;
    for (; *start > 0 && (*start < 48 || *start > 57); strln--, start++);
    if (*start == 0) return 0;
    char* pNum = start;

    for (; (*start > 47 && *start < 58) || *start == 46; strln--, start++);
    *(start++) = 0;
    strln--;
    cout << pNum << endl;
    return 1;

    //int lflen = 0, rtlen = 0;
    //for (; *start > 47 && *start < 58; strln--, start++) lflen++;
    //if (*start == 46) for (start++; *start > 47 && *start < 58; strln--, start++) rtlen++;
    //*(start++) = 0;
    //strln--;

    //double res = 0;
    //for (int j = --lflen; j >= 0; j--) {
    //    double base = 1;
    //    for (int i = 0; i < j; i++) base *= 10;
    //    int fig = *(pNum + (lflen - j)) - 48;
    //    res += base * fig;
    //}
    //for (int j = 0; j < rtlen; j++) {
    //    double base = 0.1;
    //    for (int i = 0; i < j; i++) base *= 0.1;
    //    int fig = *(pNum + (lflen + 2 + j)) - 48;
    //    res += base * fig;
    //}
    //return res;
}



int main() {
    bool swt_rein = false;
    bool swt_reout = false;
    bool swt_va = false;
    FILE* rein = nullptr, * reout = nullptr;
    if (swt_rein) rein = freopen("in.txt", "r", stdin);
    if (swt_reout) reout = freopen("out.txt", "w", stdout);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //-----------------------------main codes below-----------------------------------
    


    //-----------------------------main codes above-----------------------------------
    QueryPerformanceCounter(&t1);
    if (reout) reout = freopen("CON", "a", stdout);
    printf("\n--------------- Main complete. ---------------\n");
    printPerfCounter(t0, t1, "Total  ");
    if (swt_va) verifyAnswer("E:\\Downloads\\out.txt", "out.txt");
    if (rein) fclose(stdin);
    if (reout) fclose(stdout);
    return 0;
}

/*
*/