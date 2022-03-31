/*
现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，
求使每个村落都有公路连通所需要的最低成本。

输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；
随后的M行对应M条道路，每行给出3个正整数，
分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。
为简单起见，城镇从1到N编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多公路。
*/
#include<cstdio>
#include<vector>
using namespace std;

constexpr int kInfty = ~(1 << 31);
constexpr int kMaxCity = 1024, kMaxRoad = 3*kMaxCity;

int cityN, roadM;

int mgraph[kMaxCity][kMaxCity];

void read();
int Prim(int src);//return weight sum;

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    scanf("%d %d ", &cityN, &roadM);
    if (roadM == 0 || cityN == 0){
        printf("-1\n");
        return 0;
    }
    read();
    int resCost = Prim(cityN);//only once is sufficient, for min WPL is unique;
    if (resCost != kInfty)
        printf("%d\n", resCost);
    else
        printf("-1\n");
    return 0;
}

/*
输入样例:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
输出样例:
12
*/

inline int getMinDist(int dist[]){
    int min = kInfty, resIdx = -1;
    for (int i = 1; i <= cityN; ++i)
        if (dist[i] != 0 && dist[i] < min){//uncollected && min dist;
            min = dist[i];
            resIdx = i;
        }
    return resIdx;//if not found return -1, which is initialized;
}

int Prim(int src){
    /*initialization*/
    //do not require output MST, no need for parent[];
    //min Cost counter and crt-collected-vertices counter;
    int minC = 0, vNum = 0;
    int dist[kMaxCity];
    for (int i = 0; i <= cityN; ++i)
        dist[i] = mgraph[src][i];//suppose in mgraph no edge is initialized to kInfty;
    /*algorithm*/
    dist[src] = 0;//collect source vertex;
    ++vNum;
    while (true){
        int crt = getMinDist(dist);
        if (crt == -1) break;
        minC += dist[crt];
        dist[crt] = 0;//collect it;
        ++vNum;
        for (int i = 1; i <= cityN; ++i){
            /*if uncollected && is adjacent vertex*/
            if (dist[i] != 0 && mgraph[crt][i] < kInfty){
                /*direct edge's weight == dist to crt MST*/
                if (mgraph[crt][i] < dist[i])
                    dist[i] = mgraph[crt][i];
                //parent[i] = crt;
            }
        }
    }
    if (vNum != cityN)//graph is un-connected;
        return kInfty;
    return minC;
}

void read(){
    /*initialization*/
    for (int i = 0; i <= cityN; ++i)
        for (int j = 0; j <= cityN; ++j)
            mgraph[i][j] = kInfty;
    /*read*/
    int v1, v2, wi;
    for (int i = 0; i < roadM; ++i){
        scanf("%d %d %d ", &v1, &v2, &wi);
        mgraph[v1][v2] = mgraph[v2][v1] = wi;
    }
    return;
}