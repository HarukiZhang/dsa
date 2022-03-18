#include <iostream>
#include <iomanip>
#include "haruki.h"

void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1, const char* tag_name) {
    static double freq = -1;
    if (freq == -1) {
        LARGE_INTEGER fq;
        QueryPerformanceFrequency(&fq);
        freq = (double)fq.QuadPart;
        std::cout << "\n\n-----------------------------\n" << std::flush;
    }
    double ts = (double)(t1.QuadPart - t0.QuadPart) / freq;
    if (ts < 1) {
        ts *= 1000;
        std::cout << tag_name << ":" 
            << std::setprecision(3) << ts << " ms\n-----------------------------\n"
            << std::flush;
    }
    else std::cout << tag_name << ":" 
            << std::setprecision(3) << ts << " s\n-----------------------------\n"
            << std::flush;
    return;
}

void verifyAnswer(const char* dir1, const char* dir2) {
    FILE* f1 = fopen(dir1, "r");
    FILE* f2 = fopen(dir2, "r");
    char line1[kVerifyAnswer_arraySize];
    char line2[kVerifyAnswer_arraySize];
    for (int i = 1; fgets(line2, kVerifyAnswer_arraySize, f2) != NULL; i++) {
        fgets(line1, kVerifyAnswer_arraySize, f1);
        if (strcmp(line1, line2) != 0) {
            printf("\n-----------------------------------------------------------");
            printf("\nFirst wrong in line %d. Please try again, Master Haruki.", i);
            printf("\n-----------------------------------------------------------");
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