/*This is an exercise to write a Floyd algorithm in its standard version, 
    also as an example;

Three things to note:
    1) initialize pathLen Mtx with infty;
    2) record path and how to print;
    3) how to cope with negative-cost cycle;

Additional:
    In what situation (how sparce the matrix is) it is more efficient to use
        multiple Dijkstra rather than Floyd?
*/
#include<cstdio>
using namespace std;

constexpr int kInfinity = 1000;
constexpr int kVertexNum = 100;
constexpr int kNoConnect = -1;

/*Adjacent Matrix for Original Graph; unconnect = -1;*/
int AdjMtx[kVertexNum][kVertexNum];
int vertNum;//actual vertex number;

int FloydMtx[kVertexNum][kVertexNum];
int pathMtx[kVertexNum][kVertexNum];

bool Floyd(int Graph[][kVertexNum], int Mtx[][kVertexNum], int path[][kVertexNum]){
    /*initialization*/
    for (int i = 0; i < vertNum; ++i){
        for (int j = 0; j < vertNum; ++j){
            if (i == j)
                Mtx[i][j] = 0;//self to self has no lenght;
            else if (Graph[i][j] == kNoConnect)//no direct connection between i and j;
                Mtx[i][j] = kInfinity;
            else
                Mtx[i][j] = Graph[i][j];
            /*path mtx initialization*/
            path[i][j] = -1;//for no path temporarily;
        }
    }
    /*find min path len and record path*/
    for (int k = 0; k < vertNum; ++k){
        for (int i = 0; i < vertNum; ++i){
            for (int j = 0; j < vertNum; ++j){
                int tmp = Mtx[i][k] + Mtx[k][j];
                if (tmp < Mtx[i][j]){
                    Mtx[i][j] = tmp;
                    if (i == j && Mtx[i][j] < 0)//if negative-cost cycle found;
                        return false;
                    path[i][j] = k;
                }
            }
        }
    }
    return true;
}

/*simple recursive print cannot print starting and ending point;*/
void printPath_recur(int path[][kVertexNum], int vSta, int vTo){
    int transie = path[vSta - 1][vTo - 1];
    if (transie < 0) return;
    ++transie;//explicit value is 1 more than actual storage value;
    printPath_recur(path, vSta, transie);
    printf("%d ", transie);
    printPath_recur(path, transie, vTo);
    return;
}

void printPath(int path[][kVertexNum], int vSta, int vTo){
    printf("%d ", vSta);
    printPath_recur(path, vSta, vTo);
    printf("%d ", vTo);
    return;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);

    int N, M, v1, v2, data;
    scanf("%d %d", &N, &M);
    vertNum = N;
    //original graph insertion;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            AdjMtx[i][j] = kNoConnect;
    for (int i = 0; i < M; ++i){
        scanf("%d %d %d", &v1, &v2, &data);
        AdjMtx[v1 - 1][v2 - 1] = data;
        AdjMtx[v2 - 1][v1 - 1] = data;
    }
    Floyd(AdjMtx, FloydMtx, pathMtx);
    /*print floyd matrix*/
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j)
            printf("%d\t", FloydMtx[i][j]);
        printf("\n");
    }
    printf("\n");
    /*print path matrix*/
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j)
            printf("%d\t", pathMtx[i][j]);
        printf("\n");
    }
    /*print min path*/
    printPath(pathMtx, 3, 5);
    
}

/*Sample Input: original
6 11
3 4 70
1 2 1
5 4 50
2 6 50
5 6 60
1 3 70
4 6 60
3 6 80
5 1 100
2 4 60
5 2 80
*/

/*
Sample Input modified:
6 11
3 4 70
1 2 1
5 4 50
2 6 1
5 6 60
1 3 70
4 6 60
3 6 1
5 1 1
2 4 60
5 2 100

Floyd Matrix:
0       1       3       51      1       2
1       0       2       52      2       1
3       2       0       54      4       1
51      52      54      0       50      53
1       2       4       50      0       3
2       1       1       53      3       0

Path Matrix:
-1      -1      5       4       -1      1
-1      -1      5       4       0       -1
5       5       -1      5       5       -1
4       4       5       -1      -1      4
-1      0       5       -1      -1      1
1       -1      -1      4       1       -1

min Path printed:
3 6 2 1 5 
*/