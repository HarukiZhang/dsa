#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

char str1[210], str2[210], str3[210];

int main(){
    freopen("E:\\Downloads\\in (1).txt", "r", stdin);
    freopen("D:\\haruk\\Documents\\VSCode\\Cpp\\out.txt", "w", stdout);
    int n;
    scanf("%d\n", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%s %s %s\n", str1, str2, str3);
        int l1 = strlen(str1);
        int l2 = strlen(str2);
        bool resMtx[210][210]{true};
        for (int i = 0; i <= l1; ++i){
            for (int j = 0; j <= l2; ++j){
                if (resMtx[i][j]){
                    if (str3[i + j] == str2[j])
                        resMtx[i][j + 1] = true;
                    if (str3[i + j] == str1[i])
                        resMtx[i + 1][j] = true;
                }
            }
        }
        if (resMtx[l1][l2])
            printf("Data set %d: yes\n", i);
        else
            printf("Data set %d: no\n", i);
    }
}