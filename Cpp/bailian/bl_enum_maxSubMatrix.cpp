#include<cstdio>
using namespace std;

int nL;
int psMtx[110][110];

inline int sumSubMtx(int i1, int i2, int j1, int j2){
    return psMtx[i2][j2]
        - psMtx[i2][j1 - 1]
        - psMtx[i1 - 1][j2]
        + psMtx[i1 -1][j1 - 1];
}

int main(){
    scanf("%d", &nL);
    for (int i = 1; i <= nL; ++i){
        for (int j = 1; j <= nL; ++j){
            scanf("%d", &psMtx[i][j]);
            psMtx[i][j] += 
                + psMtx[i - 1][j]
                + psMtx[i][j - 1]
                - psMtx[i - 1][j - 1];
        }
    }
    int max = 0, tmp;
    for (int i2 = 1; i2 <= nL; ++i2){
    for (int j2 = 1; j2 <= nL; ++j2){
    for (int i1 = 1; i1 <= i2; ++i1){
    for (int j1 = 1; j1 <= j2; ++j1){
        tmp = sumSubMtx(i1, i2, j1, j2);
        if (tmp > max) max = tmp;
    }    }    }    }

    printf("%d\n", max);
}