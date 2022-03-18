#pragma once

#ifndef _HARUKI_H_
#define _HARUKI_H_

#include <Windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

constexpr unsigned short kVerifyAnswer_arraySize = 20;

void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1, const char* tag_name, 
    bool resetFreq = false) {
    static bool firstCall = true;
    double freq = 1000.0;
    if (resetFreq) {
        LARGE_INTEGER fq;
        QueryPerformanceFrequency(&fq);
        freq = static_cast<double>(fq.QuadPart);
    }
    double ts = static_cast<double>(t1.QuadPart - t0.QuadPart) / freq;
    const char* unit = " ms\n";
    /*if (ts > 1000){
        ts /= 1000; unit = " s\n";
    }*/
    if (firstCall){
        std::clog << "\n\n-----------------------------\n" << std::flush;
        firstCall = false;
    }
    std::clog << tag_name << " : " << std::setprecision(3) << ts 
        << unit << "-----------------------------\n"
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

#endif