/*
已知一张地图（以二维矩阵的形式表示）以及佐助和鸣人的位置。地图上的每个位置都可以走到，
只不过有些位置上有大蛇丸的手下，需要先打败大蛇丸的手下才能到这些位置。鸣人有一定数量的查克拉，
每一个单位的查克拉可以打败一个大蛇丸的手下。假设鸣人可以往上下左右四个方向移动，
每移动一个距离需要花费1个单位时间，打败大蛇丸的手下不需要时间。如果鸣人查克拉消耗完了，
则只可以走到没有大蛇丸手下的位置，不可以再移动到有大蛇丸手下的位置。佐助在此期间不移动，
大蛇丸的手下也不移动。请问，鸣人要追上佐助最少需要花费多少时间？

输入
输入的第一行包含三个整数：M，N，T。代表M行N列的地图和鸣人初始的查克拉数量T。
0 < M,N < 200，0 ≤ T < 10
后面是M行N列的地图，其中@代表鸣人，+代表佐助。*代表通路，#代表大蛇丸的手下。
输出
输出包含一个整数R，代表鸣人追上佐助最少需要花费的时间。如果鸣人无法追上佐助，则输出-1。
*/
#include<cstdio>
#include<cmath>

/* Logic: stack-backTrace (DFS); */

constexpr double kPi = 3.1415926'5358979'3238463;
constexpr int kInfty = ~(1<<31);
int row, col, rNrt, cNrt, rSsk, cSsk,
    totChkr, curChkr,
    curTime, minTime;
char dungeonMap[210][210];
bool guidePost[210][210];
int timeMtx[12][210][210];

inline int computeCoef(int deltaR, int deltaC);
bool chaseSsk(int r, int c);

int main(){
    freopen("E:\\Downloads\\in.txt", "r", stdin);

    scanf("%d %d %d", &::row, &::col, &::totChkr);
    for (int i = 0; i < ::row; ++i){
        scanf("%s", dungeonMap[i]);
        for (int j = 0; j < ::col; ++j){
            if (dungeonMap[i][j] == '@'){
                rNrt = i; cNrt = j;
            }
            else if (dungeonMap[i][j] == '+'){
                rSsk = i; cSsk = j;
            }
        }
    }

    minTime = kInfty;
    curTime = 0;
    curChkr = 0;
    for (int i = 0; i < ::row; ++i)
        for (int j = 0; j < ::col; ++j){
            guidePost[i][j] = true;
            for (int k = 0; k <= ::totChkr + 1; ++k){
                timeMtx[k][i][j] = kInfty;
            }
        }
    
    chaseSsk(rNrt, cNrt);

    if (minTime < kInfty)
        printf("%d", minTime);
    else
        printf("%d", -1);
    return 0;
}

bool chaseSsk(int r, int c){
    /*Judge whether Sasuke is reached*/
    if (r == rSsk && c == cSsk){
        /*Record the current minimal time using*/
        if (curTime < minTime)
            minTime = curTime;
        return true;
    }

    /*Movement effect*/
    int savChkr = curChkr;
    if (dungeonMap[r][c] == '#'){
        /*trim*/
        // if (timeMtx[curChkr + 1][r][c] <= curTime + 1)
        //     return;

        if (totChkr <= curChkr)
            return false;
        else ++curChkr;
    }
    // else if (timeMtx[curChkr][r][c] < curTime + 1)
    //     return;
    ++curTime;
    guidePost[r][c] = false;
    timeMtx[curChkr][r][c] = curTime;

    int radCoef = computeCoef(rSsk - rNrt, cSsk - cNrt);
    
    /*Loop for 4 direction*/
    for (int i = 0; i < 4; ++i){


        /*Set the priority of direction*/
        double rad = (radCoef + i) * kPi / 2;
        int rdx = static_cast<int>(sin(rad));
        int cdx = static_cast<int>(cos(rad));
        
        /*Go further into next grid*/
        /*when initiating the guidePost, only the range within valid dungeonMap is set to be 
        true, so only need to query guidePost for validity;

        r + rdx >= 0 && r + rdx < ::row && c + cdx >= 0 && c + cdx < ::col
        */
        if (guidePost[r + rdx][c + cdx]){
            /*Trim the branch*/
            if (curTime + 1 > minTime)
                break;
            

            if (dungeonMap[r + rdx][c + cdx] == '#'){
                if (timeMtx[curChkr + 1][r + rdx][c + cdx] <= curTime + 1)
                    continue;
            }
            else if (timeMtx[curChkr][r + rdx][c + cdx] <= curTime + 1)
                continue;


            chaseSsk(r + rdx, c + cdx);
        }

    }
    
    /*Undo the movement effect*/
    if (savChkr != curChkr)
        --curChkr;
    --curTime;
    guidePost[r][c] = true;
    
    /*Temporary return*/
    return false;
}

inline int computeCoef(int deltaR, int deltaC){
    /*Compute the coef. of radian for setting the priority of direction
    in the loop:
                                     up   rt   dw    lf
        offset of R: sin(-1*PI/2) == -1    0    1     0  
        offset of C: cos(-1*PI/2) ==  0    1    0    -1       */
    if (deltaR >= 0){
        if (deltaC >= 0) return 0;//Right first
        else return 1;//Down first
    }
    else {//deltaR < 0;
        if (deltaC >= 0) return -1;//Up fisrt
        else return 2;//Left first
    }
}
/*
样例输入
样例输入1
4 4 1
#@##
**##
###+
****

样例输入2
4 4 2
#@##
**##
###+
****
样例输出
样例输出1
6

样例输出2
4
*/