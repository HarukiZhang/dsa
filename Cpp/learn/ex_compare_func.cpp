#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;

int compareFunc(const void * a, const void * b){
    char *c, *d;
    c = (char *) a;
    d = (char *) b;
    if (*c == ' ') return -1;
    else if (*d == ' ') return 1;
    else return *d - *c;
}

int main(){
    // freopen("D:\\haruk\\Documents\\VSCode\\Data\\in.txt", "r", stdin);
    int twodim[3][3];
    int * p = twodim[0];
    for (int i = 0; i < 10; i++){
        *(p+i) = i+1;
    }
    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){
            printf("%d", twodim[i][k]);
        }
    }
    return 0;
}
/*

*/