#include<cstdio>
using namespace std;

int T, depth = 0, cnt = 0;
int n,m,x,y;
bool mtx[12][12];

void findWays(int r, int c){
    ++depth;
    if (depth == n * m){
        ++cnt;
        --depth;
        return;
    }
    mtx[r][c] = true;

    if (r - 2 >= 0 && c + 1 < m && !mtx[r - 2][c + 1])
        findWays(r - 2, c + 1);

    if (r - 1 >= 0 && c + 2 < m && !mtx[r - 1][c + 2])
        findWays(r - 1, c + 2);

    if (r + 1 < n && c + 2 < m && !mtx[r + 1][c + 2])
        findWays(r + 1, c + 2);

    if (r + 2 < n && c + 1 < m && !mtx[r + 2][c + 1])
        findWays(r + 2, c + 1);

    if (r + 2 < n && c - 1 >= 0 && !mtx[r + 2][c - 1])
        findWays(r + 2, c - 1);

    if (r + 1 < n && c - 2 >= 0 && !mtx[r + 1][c - 2])
        findWays(r + 1, c - 2);

    if (r - 1 >= 0 && c - 2 >= 0 && !mtx[r - 1][c - 2])
        findWays(r - 1, c - 2);

    if (r - 2 >= 0 && c - 1 >= 0 && !mtx[r - 2][c - 1])
        findWays(r - 2, c - 1);

    --depth;
    mtx[r][c] = false;
    return;
}

int main(){
    scanf("%d", &T);
    for (int i = 0; i < T; ++i){

        scanf("%d", &n);
        scanf("%d", &m);
        scanf("%d", &x);
        scanf("%d", &y);

        findWays(x, y);

        printf("%d\n", cnt);

        cnt = 0;
        depth = 0;
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < m; ++k)
                mtx[j][k] = false;

    }
}

/*
描述
马在中国象棋以日字形规则移动。

请编写一段程序，给定n*m大小的棋盘，以及马的初始位置(x，y)，要求不能重复经过棋盘上的同一个点，计算马可以有多少途径遍历棋盘上的所有点。

输入
第一行为整数T(T < 10)，表示测试数据组数。
每一组测试数据包含一行，为四个整数，分别为棋盘的大小以及初始位置坐标n,m,x,y。(0<=x<=n-1,0<=y<=m-1, m < 10, n < 10)
输出
每组测试数据包含一行，为一个整数，表示马能遍历棋盘的途径总数，0为无法遍历一次。
样例输入
1
5 4 0 0
样例输出
32
*/