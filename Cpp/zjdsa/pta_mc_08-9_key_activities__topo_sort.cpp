#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

constexpr int kMaxLen = 128, kInf = ~(1<<31);

struct LNode {
    int no;
    int lasting;
};

struct HNode {
    int early = 0, late = kInf;
};

HNode heads[kMaxLen];
vector<LNode> graph[kMaxLen];
vector<LNode> graph_rev[kMaxLen];
int degrees[kMaxLen];
int N, M;

bool myComp(const pair<int, int> &p1, const pair<int, int> &p2){
    return p1.first > p2.first;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    cin >> N >> M;
    int v1, v2;
    LNode tmp;
    for (int i = 0; i < M; ++i){
        cin >> v1 >> tmp.no >> tmp.lasting;
        graph[v1].push_back(tmp);
        v2 = tmp.no;
        tmp.no = v1;
        graph_rev[v2].push_back(tmp);
    }
    queue<int> que;
    for (int i = 1; i <= N; ++i){
        degrees[i] = graph_rev[i].size();
        if (degrees[i] == 0){
            heads[i].early = 0;
            que.push(i);
        }
    }
    int totTime = 0, cntA = 0;
    while (!que.empty()){
        int crtI = que.front();
        que.pop();
        ++cntA;
        for (LNode ln : graph[crtI]){
            int tmpTime = heads[crtI].early + ln.lasting;
            if (tmpTime > heads[ln.no].early){
                heads[ln.no].early = tmpTime;
            }
            --degrees[ln.no];
            if (degrees[ln.no] == 0){
                que.push(ln.no);
                if (heads[ln.no].early > totTime)
                    totTime = heads[ln.no].early;
            }
        }
    }
    if (cntA < N){
        cout << 0 << endl;
        return 0;
    }
    else cout << totTime << endl;
    for (int i = N; i > 0; --i){
        degrees[i] = graph[i].size();
        if (degrees[i] == 0){
            heads[i].late = totTime;//exit all set to totTime;
            que.push(i);
        }
    }
    pair<int, int> printA[kMaxLen];//stack for printing;
    int top = -1;
    while (!que.empty()){
        int crtI = que.front();
        que.pop();
        for (LNode nd : graph_rev[crtI]){
            int tmpTime = heads[crtI].late - nd.lasting;
            if (tmpTime < heads[nd.no].late){
                heads[nd.no].late = tmpTime;
            }
            if (tmpTime - heads[nd.no].early == 0){//once mobile time == 0;
                printA[++top] = {nd.no, crtI};
            }

            --degrees[nd.no];
            if (degrees[nd.no] == 0){
                que.push(nd.no);
            }
        }
    }
    stable_sort(printA, printA + top + 1, myComp);//micro adjust;
    while (top >= 0){
        cout << printA[top].first << "->" << printA[top].second << endl;
        --top;
    }
    return 0;
}