#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
constexpr int kLen = 150;

void verifyAnswer(const char* dir1, const char* dir2) {
    FILE* f1 = fopen(dir1, "r");
    FILE* f2 = fopen(dir2, "r");
    char line1[kLen];
    char line2[kLen];
    for (int i = 1; fgets(line2, kLen, f2) != NULL; i++) {
        fgets(line1, kLen, f1);
        for (int j = 0; line1[j]; ++j){
            if (line1[j] != line2[j]){
                clog << "\n" << flush;
                clog << "-----------------------------------------------------------\n" << flush;
                clog << "First wrong in ln " << i << ", col " << j
                    << ". Please try again, Master Haruki.\n" << flush;
                clog << "-----------------------------------------------------------\n" << flush;
                fclose(f1);
                fclose(f2);
                return;
            }
        }
    }
    clog << "\n" << flush;
    clog << "---------------------------------------------\n" << flush;
    clog << "All correct! Congradulations, master Haruki~!\n" << flush;
    clog << "---------------------------------------------\n" << flush;
    fclose(f1);
    fclose(f2);
    return;
}

int main () {
    verifyAnswer("E:\\Downloads\\out.txt",
        "E:\\Downloads\\myout.txt"
    );
}