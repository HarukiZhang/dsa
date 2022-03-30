/*Input Specification:
N (≤ 100), the number of subway lines. 
M (≤ 100) is the number of stops, 
K (≤ 10) query number

The indices of the stations are 4-digit numbers from 0000 to 9999;

It is guaranteed that the stations are given in the correct order
    that is, the train travels between S[i] and S[i+1] (i=1,⋯,M−1) without any stop.

Note: It is possible to have loops, but not self-loop 
    (no train starts from S and stops at S without passing through another station). 

Each station interval belongs to a unique subway line. 

Although the lines may cross each other at some stations ("transfer stations"), 
    no station can be the conjunction of more than 5 lines.

Note: It is guaranteed that all the stations are reachable, 
    and all the queries consist of legal station numbers.

*/

/*Output Specification:
the minimum number of stops.
the optimal path in a friendly format as the following:

    Take Line#X1 from S1 to S2.
    Take Line#X2 from S2 to S3.
    ......

where Xi's are the line numbers and Si's are the station indices. 

Note: Besides the starting and ending stations, 
    only the transfer stations shall be printed.

If the quickest path is not unique, output the one with the minimum number of transfers,
    which is guaranteed to be unique.
*/
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

constexpr int kMaxLines = 128, kMaxStops = 128, kMaxQuery = 16;

int hashList[kMaxStops], hIdx = 1;//convert stopName to idx;
int lineN, queryK;

struct GNode {
    int lineId, to;
};
vector<GNode> graph[kMaxStops];
// vector<int> statInfo[kMaxStops];

void read();
void query_BFS(int sta, int dest);

void debugPrint_graph();

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    scanf("%d ", &lineN);
    read();
    scanf("%d ", &queryK);
    for (int i = 0; i < queryK; ++i){
        int s, d;
        scanf("%d %d ", &s, &d);
        query_BFS(s, d);
    }
    return 0;
}

void read(){
    int statN, crtStat, lastStat, iLast, iCrt;
    hashList[0] = -1;//data starts from index 1 in graph;
    for (int i = 1; i <= lineN; ++i){
        scanf("%d ", &statN);
        lastStat = -1;//-1 for head;
        for (int j = 0; j < statN; ++j){
            scanf("%d ", &crtStat);
            /*before inserting a new station, check whether it already exists;*/
            for (iCrt = 0; iCrt < kMaxStops && hashList[iCrt] != crtStat; ++iCrt);
            if (iCrt == kMaxStops){//if not found;
                //get new index of hashList;
                hashList[hIdx] = crtStat;
                iCrt = hIdx;
                ++hIdx;
            }
            //find the index of lastStat, which necessarily exists (?);
            for (iLast = 0; iLast < kMaxStops && hashList[iLast] != lastStat; ++iLast);
            if (iLast != 0){
                graph[iLast].push_back(GNode{i, iCrt });
                graph[iCrt ].push_back(GNode{i, iLast});
            }

            lastStat = crtStat;
        }
    }
    return;
}

struct Elem {
    GNode gnode;
    int parent, transT, dist;
    bool operator<(const Elem &e) const {
        if (dist != e.dist)
            return dist > e.dist;//dist smaller better;
        else
            return transT > e.transT;//transT smaller better;
    }
};

void query_BFS(int sta, int dest){
    /*pre-check*/
    int iSta;
    for (iSta  = 0; hashList[iSta ] != sta ; ++iSta );//ensured to find;
    if (sta == dest){
        //? what if there are more than one lineId;
        printf(
            "0\n"
            "Take Line#%d from %04d to %04d.\n",
            graph[iSta][0].lineId, sta, dest
        );
        return;
    }

    /*initialization*/
    priority_queue<Elem> myque;//minheap: firPrior: dist; secPrior: transT;
    vector<Elem> path;
    stack<GNode> mystk;
    bool visited[kMaxStops]{};
    int parCnt = 0, iDest;
    for (iDest = 0; hashList[iDest] != dest; ++iDest);
    
    /*BFS algorithm*/
    visited[iSta] = true;
    myque.push( Elem { GNode{ 0, iSta }, -1, 0, 0 } );//vertex is denoted by GNode.to;
    Elem crtE;
    while (!myque.empty()){
        crtE = myque.top(); myque.pop();
        path.push_back(crtE);

        /*termination condition*/
        if (crtE.gnode.to == iDest)
            break;
        
        auto ie = graph[crtE.gnode.to].end();
        for (auto it = graph[crtE.gnode.to].begin(); it != ie; ++it){
            if ( visited[it->to] == false){
                visited[it->to] = true;
                int tt = crtE.gnode.lineId != it->lineId ? 1 : 0;
                myque.push( Elem {*it, parCnt, crtE.transT + tt, crtE.dist + 1} );
            }
        }
        ++parCnt;
    }
    
    
    /*post-BFS*/
    int pathIdx = path.size() - 1;
    printf("%d\n", path[pathIdx].dist);

    while (pathIdx != 0){
        mystk.push( path[pathIdx].gnode );
        pathIdx = path[pathIdx].parent;
    }

    int lastStatId, crtLineId;
    crtLineId = mystk.top().lineId;
    lastStatId = mystk.top().to;
    printf("Take Line#%d from %04d to ", crtLineId, sta);

    while (!mystk.empty()){
        GNode tmpGN = mystk.top();
        mystk.pop();
        if (tmpGN.lineId != crtLineId){//if transferred;
            crtLineId = tmpGN.lineId;
            printf("%04d.\n"
                "Take Line#%d from %04d to ",
                hashList[lastStatId],
                crtLineId, hashList[lastStatId]);
        }

        lastStatId = tmpGN.to;
    }
    printf("%04d.\n", dest);
    return;
}

void debugPrint_graph(){
    for (int i = 1; i <= lineN; ++i){
        printf("Station %04d:", hashList[i]);

        for (GNode gn : graph[i]){
            printf("(%d,%04d),", gn.lineId, gn.to);
        }

        printf("\n");
    }
    return;
}
/*
Sample Input:
4
7 1001 3212 1003 1204 1005 1306 7797
9 9988 2333 1204 2006 2005 2004 2003 2302 2001
13 3011 3812 3013 3001 1306 3003 2333 3066 3212 3008 2302 3010 3011
4 6666 8432 4011 1306
3
3011 3013
6666 2001
2004 3001


Sample Output:
2
Take Line#3 from 3011 to 3013.
10
Take Line#4 from 6666 to 1306.
Take Line#3 from 1306 to 2302.
Take Line#2 from 2302 to 2001.
6
Take Line#2 from 2004 to 1204.
Take Line#1 from 1204 to 1306.
Take Line#3 from 1306 to 3001.
*/

/*
2
Take Line#3 from 3011 to 3013.
10
Take Line#4 from 6666 to 1306.
Take Line#3 from 1306 to 2302.
Take Line#2 from 2302 to 2001.
6
Take Line#2 from 2004 to 1204.
Take Line#1 from 1204 to 1306.
Take Line#3 from 1306 to 3001.
*/