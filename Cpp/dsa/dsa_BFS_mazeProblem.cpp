#include<cstdio>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#include<utility>
#include<memory>
using namespace std;
constexpr double kPi = 3.1415926'5358979'3238462;
int maze[5][5];
struct NODE {
    int r, c, f;
    NODE(){}
    NODE(int r_, int c_, int f_): r(r_), c(c_), f(f_){}
    NODE(const NODE& n): r(n.r), c(n.c), f(n.f){}
};
queue< NODE > tmpQue;
vector< NODE > resVec;
stack< pair< int, int > > prtStk;
bool guidePost[8][8];

void searchRoute(){

    NODE start {0, 0, -1};
    tmpQue.push(move(start));
    guidePost[0][0] = false;

    int cnt = 0;
    NODE node;
    while (!tmpQue.empty()) {
        int rB = tmpQue.front().r , cB = tmpQue.front().c;
        
        if (rB == 4 && cB == 4){
            resVec.push_back(move(tmpQue.front()));
            break;
        }

        for (int d = 0; d < 4; ++d){
            double rad = kPi * d / 2;
            int row = rB + static_cast<int>(sin(rad));
            int col = cB + static_cast<int>(cos(rad));

            if (guidePost[row][col] && maze[row][col] != 1){
                node.r = row; node.c = col; node.f = cnt;
                tmpQue.push(move(node));
                guidePost[row][col] = false;
            }
        }

        resVec.push_back(move(tmpQue.front()));
        tmpQue.pop();
        ++cnt;//for each elem popped out from queue into vector;
    }

    auto it = resVec.rbegin();
    prtStk.push(make_pair(it->r, it->c));
    for (int i = it->f; i != -1; i = resVec[i].f){
        prtStk.push(make_pair(resVec[i].r, resVec[i].c));
    }

    pair<int, int> pT;
    while (!prtStk.empty()){
        pT = prtStk.top();
        printf("(%d, %d)\n", pT.first, pT.second);
        prtStk.pop();
    }

}

int main(){
    for (int i = 0; i < 5; ++i)
        for (int j = 0 ; j < 5; ++j){
            scanf("%d", &maze[i][j]);
            guidePost[i][j] = true;
        }

    searchRoute();

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