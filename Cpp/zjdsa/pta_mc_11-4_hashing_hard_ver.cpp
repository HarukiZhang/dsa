#include<iostream>
#include<vector>
#include<queue>
using namespace std;

constexpr int kMaxLen = 1024;

int TSize;
vector<int> graph[kMaxLen];//out-directed;
int hashTbl[kMaxLen],//keys;
    indegrs[kMaxLen];//indegrees;

struct MyComp {
    bool operator()(int a, int b) const {
        return hashTbl[a] > hashTbl[b];//minheap;
    }
};

priority_queue<int, vector<int>, MyComp> que;//minheap by key value;

int main(){
    ios::sync_with_stdio(false);
    cin >> TSize;
    for (int i = 0; i < TSize; ++i){
        cin >> hashTbl[i];
        if (hashTbl[i] < 0){
            indegrs[i] = -1;
            continue;
        }
        int hashV = hashTbl[i] % TSize;//hash function;
        int ofs = i - hashV;
        //probing;
        if (ofs > 0){
            indegrs[i] = ofs;//offset == indegree;
            for (int j = hashV; j < i; ++j)
                graph[j].push_back(i);
        }
        else if (ofs < 0){
            indegrs[i] = TSize + ofs;//offset overlapped;
            for (int j = 0; j < i; ++j)//overflowed position;
                graph[j].push_back(i);
            for (int j = hashV; j < TSize; ++j)
                graph[j].push_back(i);
        }
        //else when ofs == 0, nop;
    }
    //topological sort;
    for (int i = 0; i < TSize; ++i)
        if (indegrs[i] == 0)
            que.push(i);
    bool firP = true;
    while (!que.empty()){
        int idx = que.top();
        que.pop();
        if (firP) firP = false;
        else cout << ' ';
        cout << hashTbl[idx];
        for (auto iLoc : graph[idx]){
            --indegrs[iLoc];
            if (indegrs[iLoc] == 0)
                que.push(iLoc);
        }
    }
    return 0;
}