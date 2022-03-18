#include<iostream>
#include<cstring>
#define MSL 256
using namespace std;

char astr[MSL], bstr[MSL];
int maxNs[MSL][MSL];

void maxSubStrLen(int aLn, int bLn){
    for (int i = 0; i < aLn; ++i){
        for (int j = 0; j < bLn; ++j){
            if (astr[i] != bstr[j]){
                int t1 = maxNs[i + 1][j];
                int t2 = maxNs[i][j + 1];
                maxNs[i + 1][j + 1] = t1 > t2 ? t1 : t2;
            }
            else maxNs[i + 1][j + 1] = maxNs[i][j] + 1;
        }
    }
    cout << maxNs[aLn][bLn] << "\n" << flush;
}

int main(){

    while (cin >> astr >> bstr){

        int aLn = strlen(astr);
        int bLn = strlen(bstr);
        for (int i = 0; i <= aLn; ++i)
            maxNs[i][0] = 0;
        for (int j = 0; j <= bLn; ++j)
            maxNs[0][j] = 0;
        maxSubStrLen(aLn, bLn);
    }
}