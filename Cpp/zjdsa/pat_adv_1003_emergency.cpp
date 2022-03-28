#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

constexpr int kMaxCityNum = 500, kInfty = ~(1 << 31);
struct Node {
    int to, rlen;
};
struct Graph {
    int teamNums[kMaxCityNum];
    vector<Node> roadLen[kMaxCityNum];
};

vector<int> crtTNums[kMaxCityNum];//for Dijkstra();
Graph graph;
bool visited[kMaxCityNum]{};
int cityN, roadM, Cnow, Ctar;
int resCnt = 0, resMaxTeam = 0;
int minDist = kInfty;
int dist[kMaxCityNum];

void debugPrint_graph();
void debugPrint_dist();

void BFS(int ptr);//patially correct: when N it too big, over-time;
void backTrace(int ptr, int dist, int team);//accepted;
bool Dijkstra(int src, int dest);//accepted;

int main(){
    freopen("E:\\in.txt", "r", stdin);

    scanf("%d %d %d %d ", &cityN, &roadM, &Cnow, &Ctar);
    for (int i = 0; i < cityN; ++i)
        scanf("%d ", &graph.teamNums[i]);
    int c1, c2;
    Node tmpN;
    for (int i = 0; i < roadM; ++i){
        scanf("%d %d %d ", &c1, &c2, &tmpN.rlen);
        tmpN.to = c2;
        graph.roadLen[c1].push_back(tmpN);
        tmpN.to = c1;
        graph.roadLen[c2].push_back(tmpN);
    }
    // debugPrint_graph();

    Dijkstra(Cnow, Ctar);
    printf("%d %d", resCnt, resMaxTeam);

    /*debug*/
    // printf("\n");
    // debugPrint_dist();
    return 0;
}


/* customized sample input:
13 16 0 11
1 1 2 2 3 3 1 1 2 2 0 0 10
0 1 1
0 2 1
0 4 3
1 3 1
2 5 1
3 4 1
4 5 1
4 6 1
6 7 1
6 8 2
6 12 1
7 9 2
8 10 2
8 12 1
9 10 1
10 11 1

supposed output:
9 22
*/

void sendTeam(int crt, int tar){
    auto it = crtTNums[crt].begin();
    auto ie = crtTNums[crt].end();
    int tarTNum = graph.teamNums[tar];
    for (; it != ie; ++it)
        crtTNums[tar].push_back( *it + tarTNum );
    return;
}

int weightof(int a, int b){
    auto it = graph.roadLen[a].begin();
    auto ie = graph.roadLen[a].end();
    for (; it != ie; ++it){
        if (it->to == b) return it->rlen;
    }
    return kInfty;
}

struct PElem {
    int cityId, dist;
    bool operator<(const PElem& e) const {//for minheap;
        return dist > e.dist;
    }
};

bool Dijkstra(int src, int dest){
    /*initialization*/
    priority_queue<PElem> mypque;//minheap;
    auto it = graph.roadLen[src].begin();
    auto ie = graph.roadLen[src].end();
    int tmpDist;
    PElem crtE;
    for (int i = 0; i < cityN; ++i){
        dist[i] = kInfty;
    }
    for (; it != ie; ++it){
        dist[it->to] = it->rlen;
    }
    /*algorithm*/
    dist[src] = 0;
    crtTNums[src].push_back(graph.teamNums[src]);
    mypque.push(PElem {src, 0});
    visited[src] = true;
    while ( !mypque.empty() ){
        crtE = mypque.top(); mypque.pop();
        // if (crtE.cityId == dest) break;

        it = graph.roadLen[crtE.cityId].begin();
        ie = graph.roadLen[crtE.cityId].end();
        for (; it != ie; ++it){
            //with minus-cost edge, Dijkstra doesnt work;
            // if (it->rlen < 0) return false;
            
            /*note: std dijkstra modifys only the dist of those has yet been collected;
            so, when finding weight of crtE -> it, should find its original value;*/
            tmpDist = crtE.dist + weightof(crtE.cityId, it->to);
            if (visited[it->to] == false){
                if (tmpDist < dist[it->to]){
                    dist[it->to] = tmpDist;
                }
                mypque.push( PElem {it->to, dist[it->to]} );
                visited[it->to] = true;
            }
            /*updating dist[] and crtTNums[] should be independent;*/
            if (tmpDist < dist[it->to]){//send teams no matter visited or not;
                crtTNums[it->to].clear();
                sendTeam(crtE.cityId, it->to);
            }
            else if (tmpDist == dist[it->to]){
                sendTeam(crtE.cityId, it->to);
            }
        }
    }

    /*print*/
    resCnt = crtTNums[dest].size();
    auto ited = crtTNums[dest].end();
    for (auto it1 = crtTNums[dest].begin(); it1 != ited; ++it1)
        if (*it1 > resMaxTeam)
            resMaxTeam = *it1;

    return true;
}

void backTrace(int ptr, int dist, int team){
    if (ptr == ::Ctar){
        if (minDist > dist){
            minDist = dist;
            resCnt = 1;
            resMaxTeam = team;
        }
        else if (minDist == dist){
            ++resCnt;
            if (team > resMaxTeam)
                resMaxTeam = team;
        }
        return;
    }
    visited[ptr] = true;
    auto it = graph.roadLen[ptr].begin(),
         ie = graph.roadLen[ptr].end();
    for (; it != ie; ++it){
        if ( visited[it->to] == false ){
            if ( dist + it->rlen > minDist) continue;

            backTrace(it->to, dist + it->rlen, team + graph.teamNums[it->to]);
        }
    }
    visited[ptr] = false;
    return;
}

struct Elem {
    int cityId, team, dist;
};

void BFS(int ptr){
    queue<Elem> myque;
    myque.push(Elem { ptr, graph.teamNums[ptr], 0 });
    while ( !myque.empty() ){
        Elem crtE = myque.front(); myque.pop();
        if (crtE.cityId == ::Ctar){
            if (crtE.dist < minDist){
                minDist = crtE.dist;
                resCnt = 1;
                resMaxTeam = crtE.team;
            }
            else if (crtE.dist == minDist){
                ++resCnt;
                if (crtE.team > resMaxTeam) resMaxTeam = crtE.team;
            }
        }
        else {
            auto it = graph.roadLen[crtE.cityId].begin();
            auto ie = graph.roadLen[crtE.cityId].end();
            for (; it != ie; ++it){
                /*only control with dist is very easy to go cycle;
                so this is not a good idea;*/
                if (crtE.dist + it->rlen <= minDist){
                    Elem tmpE {
                        it->to, 
                        crtE.team + graph.teamNums[it->to],
                        crtE.dist + it->rlen
                    };
                    myque.push(tmpE);
                }
            }
        }
    }
    return;
}

void debugPrint_graph(){
    for (int i = 0; i < cityN; ++i){
        printf("%d : ", graph.teamNums[i]);
        auto it = graph.roadLen[i].begin();
        auto ie = graph.roadLen[i].end();
        for (; it != ie; ++it)
            printf("(%d, %d),", it->to, it->rlen);
        printf("\n");
    }
    return;
}

void debugPrint_dist(){
    for (int i =0; i < cityN;  ++i){
        printf("%d ", dist[i]);
    }
    printf("\n");
    return;
}