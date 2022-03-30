/*
找一条出发地和目的地之间的最短路径。

如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入说明：
输入数据的第1行给出4个正整数N、M、S、D，其中
    N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；
    M是高速公路的条数；
    S是出发地的城市编号；
    D是目的地的城市编号。
随后的M行中，每行给出一条高速公路的信息，分别是：
    城市1、城市2、高速公路长度、收费额，

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。
*/

/*Logic:
    If there are two properties should be considered, such in this problem they are
    min distance and least expense,
    operation updating these two properties should be independent of collecting vertex;
    That is to say, although each vertex will have been collected only once,
    regarding to those that has already been collected,
    we also should update their dist or expense when needed;
    Otherwise, we can not traverse all possible paths completely.
*/
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

constexpr int kMaxCityN = 500, kInfty = ~(1 << 31);

struct Highway {
    int to, len, charge;
};

vector<Highway> map[kMaxCityN];
int cityN, highwM, staS, destD;
int dist[kMaxCityN], expenses[kMaxCityN];
bool ved[kMaxCityN]{};

void read();
void Dijkstra();

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    scanf("%d %d %d %d ", &cityN, &highwM, &staS, &destD);
    read();
    Dijkstra();
    printf("%d %d", dist[destD], expenses[destD]);

    return 0;
}

void read(){
    int city1, city2, highwLen, charge;
    Highway hw;
    for (int i = 0; i < highwM; ++i){
        scanf("%d %d %d %d ", &city1, &city2, &highwLen, &charge);
        hw.to = city2;
        hw.len = highwLen;
        hw.charge = charge;
        map[city1].push_back(hw);
        hw.to = city1;
        map[city2].push_back(hw);
    }
    return;
}

int getDist(int c1, int c2){
    for (Highway hw : map[c1])
        if (hw.to == c2) return hw.len;
    return kInfty;
}

struct QElem {
    int city, dist; //crt len that already passed;
    bool operator<(const QElem &qe) const {
        //min heap lets the greater percolate down;
        return dist > qe.dist;
    }
};

void Dijkstra(){
    /*initilization*/
    priority_queue<QElem> pque;
    for (int i = 0; i < cityN; ++i)
        dist[i] = expenses[i] = kInfty;
    for (Highway hw : map[staS])
        dist[hw.to] = hw.len;
    /*algorithm*/
    ved[staS] = true;
    dist[staS] = 0;
    expenses[staS] = 0;
    pque.push( QElem {staS, 0} );
    while ( !pque.empty() ){
        QElem crt = pque.top();
        pque.pop();
        for (Highway hw : map[crt.city]){
            /*update dist and exps no matter collected or not;*/
            int tmpDist = dist[crt.city] + getDist(crt.city, hw.to);
            int tmpExps = expenses[crt.city] + hw.charge;
            if (tmpDist < dist[hw.to]){
                dist[hw.to] = tmpDist;
                expenses[hw.to] = tmpExps;/*update expense*/
            }
            else if (tmpDist == dist[hw.to]){
                if (tmpExps < expenses[hw.to])
                    expenses[hw.to] = tmpExps;
            }
            /*collect only the un-collected;*/
            if ( ved[hw.to] == false ){
                ved[hw.to] = true;
                pque.push( QElem {hw.to, dist[hw.to]} );
            }
        }
    }
    return;
}

/*
输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40
*/