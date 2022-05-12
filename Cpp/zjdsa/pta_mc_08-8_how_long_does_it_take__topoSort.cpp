#include<iostream>
#include<vector>
#include<queue>
using namespace std;

constexpr int kMaxLen = 128;

struct Node {
    int to, time;
};

int poiN, actM;
vector<Node> graph[kMaxLen];
vector<bool> indegrees_cnt[kMaxLen];
int degrees[kMaxLen];
int cumulTime[kMaxLen]{};

void topoSort(){
    queue<int> que;
    int ear_cmpl_time = 0, vertN = 0;
    for (int i = 0; i < poiN; ++i){
        degrees[i] = indegrees_cnt[i].size();
        if (degrees[i] == 0)
            que.push(i);
    }
    while (!que.empty()){
        int crt = que.front();  que.pop();
        ++vertN;
        for (auto node : graph[crt]){
            int time = cumulTime[crt] + node.time;
            if (time > cumulTime[node.to]) cumulTime[node.to] = time;
            --degrees[node.to];
            if (degrees[node.to] == 0){
                que.push(node.to);
                if (cumulTime[node.to] > ear_cmpl_time)
                    ear_cmpl_time = cumulTime[node.to];
            }
        }
    }
    if (vertN < poiN)
        cout << "Impossible" << endl;
    else cout << ear_cmpl_time << endl;
    return;
}

void topological_sort(){
    queue<int> que;
    for (int i = 0; i < poiN; ++i){
        degrees[i] = indegrees_cnt[i].size();
        if (degrees[i] == 0)
            que.push(i);
    }
    while (!que.empty()){
        int crt = que.front(); que.pop();
        /* output(crt); */
        for (auto n : graph[crt]){
            --degrees[n.to];
            if (degrees[n.to] == 0)
                que.push(n.to);
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> poiN >> actM;
    Node tmpN;
    int v1, v2;
    for (int i = 0; i < actM; ++i){
        cin >> v1 >> tmpN.to >> tmpN.time;
        graph[v1].push_back(tmpN);
        indegrees_cnt[tmpN.to].push_back(true);
    }
    topoSort();
    return 0;
}