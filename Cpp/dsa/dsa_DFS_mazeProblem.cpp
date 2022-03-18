#include<cstdio>
#include<cmath>
#include<vector>
#include<utility>
using namespace std;
constexpr double kPi = 3.1415926'5358979'3238462;
int maze[5][5];
int minRoute, depth;
vector< pair<int, int> > tmpVec, resVec;
bool guidePost[8][8];

void searchRoute(int r = 0, int c = 0){
    ++depth;
    guidePost[r][c] = false;
    tmpVec.push_back(make_pair(r, c));
    if (r == 4 && c == 4 && depth < minRoute){
        minRoute = depth;
        /*Prepare two global vectors, one for temporary storage, and once a minRoute is found,
        assign tmpVec to resVec; Finally, resVec will be storing the minRoute;*/
        resVec.assign(tmpVec.begin(), tmpVec.end());
    }
    for (int i = 0; i < 4; ++i){
        double rad = i * kPi / 2;
        int rNxt = r + static_cast<int>(sin(rad));
        int cNxt = c + static_cast<int>(cos(rad));
        if (depth > minRoute) break;
        if (guidePost[rNxt][cNxt] && maze[rNxt][cNxt] == 0)
            searchRoute(rNxt, cNxt);
    }
    --depth;
    guidePost[r][c] = true;
    tmpVec.pop_back();
    return;
}

int main(){
    for (int i = 0; i < 5; ++i)
        for (int j = 0 ; j < 5; ++j){
            scanf("%d", &maze[i][j]);
            guidePost[i][j] = true;
        }
    minRoute = 0x7fffffff;
    depth = 0;
    searchRoute();
    for (auto it = resVec.begin(); it != resVec.end(); ++it)
        printf("(%d, %d)\n", it->first, it->second);
}

/*
描述
定义一个二维数组：

int maze[5][5] = {

0, 1, 0, 0, 0,

0, 1, 0, 1, 0,

0, 0, 0, 0, 0,

0, 1, 1, 1, 0,

0, 0, 0, 1, 0,

};

它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，
要求编程序找出从左上角到右下角的最短路线。

输入
一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。
输出
左上角到右下角的最短路径，格式如样例所示。

样例输入
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0

样例输出
(0, 0)
(1, 0)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 4)
(4, 4)
*/