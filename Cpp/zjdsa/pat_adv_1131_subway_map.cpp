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

constexpr int kMaxLines = 100, kMaxStops = 100, kMaxQuery = 10;

int hashList[kMaxStops], hIdx = 1;//convert stopName to idx;
int lineN, queryK;

struct GNode {
    int lineId, from, to;
};
vector<GNode> graph[kMaxStops];
// vector<int> statInfo[kMaxStops];

void read();
void query_BFS(int sta, int dest);

void debugPrint_graph();

int main(){
    freopen("E:\\in.txt", "r", stdin);

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
    hashList[0] = 0;//data starts from index 1 in graph;
    for (int i = 1; i <= lineN; ++i){
        scanf("%d ", &statN);
        lastStat = 0;//0 for head;
        for (int j = 0; j < statN; ++j){
            scanf("%d ", &crtStat);
            /*before inserting a new station, check whether it already exists;*/
            for (iCrt = 0; iCrt < kMaxStops; ++iCrt){
                if (hashList[iCrt] == crtStat){
                    break;
                }
            }
            if (iCrt == 0){//if not found;
                //get new index of hashList;
                hashList[hIdx] = crtStat;
                iCrt = hIdx;
                ++hIdx;
            }

            //update station info about line# that pass through;
            // statInfo[iCrt].push_back(i);
            //find the index of lastStat, which necessarily exists;
            for (iLast = 0; hashList[iLast] != lastStat; ++iLast);

            if (iLast != 0){
                graph[iLast].push_back(GNode{i, iLast, iCrt });
                graph[iCrt ].push_back(GNode{i, iCrt,  iLast});
            }

            lastStat = crtStat;
        }
    }
    return;
}

struct Elem {
    GNode gnode;
    int parent;
};

void query_BFS(int sta, int dest){
    /*initialization*/
    queue<Elem> myque;//logically vertex in it;
    vector<Elem> path;
    stack<GNode> mystk;
    bool visited[kMaxStops]{};
    int iSta, iDest, parCnt = 0, pathCnt = 0;
    for (iSta  = 0; hashList[iSta ] != sta ; ++iSta );//ensure to find;
    for (iDest = 0; hashList[iDest] != dest; ++iDest);
    /*BFS algorithm*/
    visited[iSta] = true;
    myque.push( Elem {GNode{0,0,iSta}, -1} );//vertex is denoted by GNode.to;
    Elem crtE;
    while (!myque.empty()){
        crtE = myque.front(); myque.pop();
        path.push_back(crtE);

        /*termination condition*/
        if (crtE.gnode.to == iDest){
            ++pathCnt;
            if (myque.front().gnode.to != iDest){
                break;
            }
        }
        
        auto ie = graph[crtE.gnode.to].end();
        for (auto it = graph[crtE.gnode.to].begin(); it != ie; ++it){
            if ( visited[it->to] == false){
                visited[it->to] = true;
                myque.push( Elem {*it, parCnt} );
            }
        }
        ++parCnt;
    }
    /*post-BFS*/
    int resDist, crtDist;
    int crtLineId;
    int minTransTimes = 99999;//large num as infty;
    int minTransIdx = -1;
    int idxCnt = 0;
    for (Elem e : path){
        if (e.gnode.to == iDest){
            int crtTransTimes = 0;
            crtLineId = e.gnode.lineId;
            int i = e.parent;
            crtDist = 0;
            while (i != -1){
                if (path[i].gnode.lineId != crtLineId){
                    crtLineId = path[i].gnode.lineId;
                    ++crtTransTimes;
                }
                i = path[i].parent;
                ++crtDist;
            }
            if (crtTransTimes < minTransTimes){
                minTransTimes = crtTransTimes;
                minTransIdx = idxCnt;
                resDist = crtDist;
            }
        }
        ++idxCnt;
    }
    while (minTransIdx != -1){
        mystk.push(path[minTransIdx].gnode);
        minTransIdx = path[minTransIdx].parent;
    }

    int lastStatId;
    if (!mystk.empty()){
        printf("%d\n", resDist);
        crtLineId = mystk.top().lineId;
        lastStatId = mystk.top().from;
        printf("Take Line#%d from %04d to ", crtLineId, hashList[lastStatId]);
    }
    while (!mystk.empty()){
        GNode tmpGN = mystk.top();
        mystk.pop();
        if (tmpGN.lineId != crtLineId){
            crtLineId = tmpGN.lineId;
            if (!mystk.empty()){
                printf("%04d.\nTake Line#%d from %04d to ",
                    hashList[lastStatId], crtLineId, hashList[lastStatId]);
            }
            else printf("%04d.\n", hashList[lastStatId]);
        }

        lastStatId = tmpGN.from;
    }
    return;
}

void debugPrint_graph(){
    for (int i = 1; i <= lineN; ++i){
        printf("Station %04d:", hashList[i]);

        for (GNode gn : graph[i]){
            printf("(%04d,%d,%04d),", gn.from, gn.lineId, gn.to);
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