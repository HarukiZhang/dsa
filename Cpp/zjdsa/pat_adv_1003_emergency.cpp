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
struct Elem {
    int cityId, team, dist;
    bool operator<(const Elem& e) const {
        return dist < e.dist;
    }
};

Graph graph;
bool visited[kMaxCityNum]{};
int cityN, roadM, Cnow, Ctar;
int resCnt = 0, resMaxTeam = 0;
int minDist = kInfty;
int dist[kMaxCityNum];

void debugPrint();

void BFS(int ptr);//patially correct: when N it too big, over-time;
void backTrace(int ptr, int dist, int team);//accept;
bool Dijkstra(int ptr);

int main(){
    freopen("E:\\in.txt", "r", stdin);

    scanf("%d %d %d %d ", &cityN, &roadM, &Cnow, &Ctar);
    int tmp;
    for (int i = 0; i < cityN; ++i)
        scanf("%d ", &graph.teamNums[i]);
    int c1, c2, di;
    Node tmpN;
    for (int i = 0; i < roadM; ++i){
        scanf("%d %d %d ", &c1, &c2, &tmpN.rlen);
        tmpN.to = c2;
        graph.roadLen[c1].push_back(tmpN);
        tmpN.to = c1;
        graph.roadLen[c2].push_back(tmpN);
    }
    // BFS(Cnow);
    // backTrace(Cnow, 0, graph.teamNums[Cnow]);

    Dijkstra(Cnow);
    printf("%d %d", resCnt, resMaxTeam);
    /*debug*/
    // printf("\n");
    // debugPrint();
    return 0;
}

int weightof(int a, int b){
    auto it = graph.roadLen[a].begin();
    auto ie = graph.roadLen[a].end();
    for (; it != ie; ++it){
        if (it->to == b) return it->rlen;
    }
    return kInfty;
}

bool Dijkstra(int ptr){
    /*initialization*/
    for (int i = 0; i < cityN; ++i){
        dist[i] = kInfty;
    }
    auto it = graph.roadLen[ptr].begin();
    auto ie = graph.roadLen[ptr].end();
    for (; it != ie; ++it){
        dist[it->to] = it->rlen;
    }
    /*algorithm*/
    dist[ptr] = 0;
    priority_queue<Elem> mypque;
    mypque.push(Elem {ptr, graph.teamNums[ptr], 0});
    visited[ptr] = true;
    while ( !mypque.empty() ){
        Elem crtE = mypque.top(); mypque.pop();

        auto it = graph.roadLen[crtE.cityId].begin();
        auto ie = graph.roadLen[crtE.cityId].end();
        for (; it != ie; ++it){
            //with minus-cost edge, Dijkstra doesnt work;
            // if (it->rlen < 0) return false;
            
            int tmp = dist[crtE.cityId] + weightof(crtE.cityId, it->to);

            if (it->to == ::Ctar){
                if (tmp < minDist){
                    minDist = tmp;
                    resCnt = 1;
                    resMaxTeam = crtE.team + graph.teamNums[it->to];
                }
                else if (dist[crtE.cityId] == minDist){
                    ++resCnt;
                    if (resMaxTeam < crtE.team + graph.teamNums[it->to])
                        resMaxTeam = crtE.team + graph.teamNums[it->to];
                }
            }

            if (visited[it->to] == false){
                if (tmp < dist[it->to]){
                    dist[it->to] = tmp;
                }

                visited[it->to] = true;
                mypque.push(Elem {it->to,
                    graph.teamNums[it->to] + crtE.team,//cumulative;
                    it->rlen//non-cumulative;
                });
            }
        }
    }
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

void debugPrint(){
    for (int i = 0; i < cityN; ++i){
        printf("%d : ", graph.teamNums[i]);
        auto it = graph.roadLen[i].begin();
        auto ie = graph.roadLen[i].end();
        for (; it != ie; ++it)
            printf("(%d, %d)\t", it->to, it->rlen);
        printf("\n");
    }
    return;
}
