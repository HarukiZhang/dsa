#include<cstdio>

/*This is an ex for reverse inferencial dynamic programming algo*/
int mR;
int arr[100][100];

int maxRoute(int r, int c){
    for (int i = mR - 2; i >= r; --i){
        for (int j = c; j <= i; ++j){
            int maxT = arr[i + 1][j] > arr[i + 1][j + 1] ?
                arr[i + 1][j] : arr[i + 1][j + 1];
            arr[i][j] += maxT;
        }
    }
    return arr[r][c];
}

int main(){
    scanf("%d", &mR);
    int cn;
    for (int i = 0; i < mR; ++i){
        for (int j = 0; j <= i; ++j){
            scanf("%d", &cn);
            arr[i][j] = cn;
        }
    }
    int res = maxRoute(0, 0);
    printf("%d", res);
}