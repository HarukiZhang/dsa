/*
有一个正方形的墙，由N*N个正方形的砖组成，其中一些砖是白色的，另外一些砖是黄色的。
Bob是个画家，想把全部的砖都涂成黄色。但他的画笔不好使。当他用画笔涂画第(i, j)个位置的砖时， 
位置(i-1, j)、 (i+1, j)、 (i, j-1)、 (i, j+1)上的砖都会改变颜色。
请你帮助Bob计算出最少需要涂画多少块砖，才能使所有砖的颜色都变成黄色。

输入
第一行是一个整数n (1≤n ≤15)，表示墙的大小。接下来的n行表示墙的初始状态。每一行包含n个字符。
第i行的第j个字符表示位于位置(i,j)上的砖的颜色。“w”表示白砖，“y”表示黄砖。
输出
一行，如果Bob能够将所有的砖都涂成黄色，则输出最少需要涂画的砖数，否则输出“inf”。
*/
#include<cstdio>
using namespace std;

int N;
char wall[16][16];
bool tmp[16][16];

int main(){
    scanf("%d", &N);
    for (int i = 0; i < N; ++i){
        scanf("%s", wall[i]);
    }
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (wall[i][j] == 'w')
                tmp[i][j] = true;
        
    int stp = 1 << N;
    int cnt = 0, min = 0xffff;
    /*Start to enumerate the first row;*/
    /*Need to enumerate from not-paint-at-all to paint-all;*/
    for (int i = 0; i < stp; ++i){

        /*Paint the first row;*/
        for (int j = N - 1; j >= 0; --j){
            if (i >> j & 1){
                ++cnt;
                tmp[0][j] = !tmp[0][j];
                if (j - 1 >= 0)
                    tmp[0][j - 1] = !tmp[0][j - 1];
                if (j + 1 < N)
                    tmp[0][j + 1] = !tmp[0][j + 1];
                tmp[1][j] = !tmp[1][j];
            }
        }
        /*Paint the rest rows according to the first row;*/
        for (int k = 0; k < N - 1; ++k){
            for (int m = 0; m < N; ++m){
                if (tmp[k][m]){
                    ++cnt;
                    tmp[k + 1][m] = !tmp[k + 1][m];
                    if (m - 1 >= 0)
                        tmp[k + 1][m - 1] = !tmp[k + 1][m - 1];
                    if (m + 1 < N)
                        tmp[k + 1][m + 1] = !tmp[k + 1][m + 1];
                    if (k + 2 < N)
                        tmp[k + 2][m] = !tmp[k + 2][m];
                }
            }
        }
        /*Check the last row whether still there's white grid;*/
        int chk = 0;
        while (chk < N && !tmp[N - 1][chk]) ++chk;
        if (chk == N && cnt < min)
            min = cnt;
        
        /*Reset the wall;*/
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (wall[i][j] == 'w')
                    tmp[i][j] = true;
                else
                    tmp[i][j] = false;
        cnt = 0;
    }

    if (min != 0xffff)
        printf("%d\n", min);
    else
        printf("inf\n");

}

/*
10
wywywyywwy
ywywwywyyw
wywwywyyww
wwywwwwyww
wwyywyywyy
wywywwwwwy
yywwywyyyw
yyywwwywyy
wywwyyywwy
wyyyywwywy
*/

/*
样例输入
5
wwwww
wwwww
wwwww
wwwww
wwwww
样例输出
15 

*/