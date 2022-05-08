#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

constexpr int kMaxLen = 128, kBound = 50;
constexpr double kRadi = 7.5;

struct PNode {
    int x = 0, y = 0;
    bool isSafe, firJump = false;
    int dist;
};

PNode graph[kMaxLen];
bool visited[kMaxLen];

int N, D;

bool canJump(int i1, int i2){
    PNode &p1 = graph[i1], &p2 = graph[i2];
    int dev = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    return dev <= D;//D has been squared already;
}
bool getSafe(const PNode &pn){
    //D has yet been squared;
    int x = pn.x > 0 ? pn.x : -pn.x;
    int y = pn.y > 0 ? pn.y : -pn.y;
    return (x + D >= kBound) || (y + D >= kBound);
}

struct Elem {
    int parent, idx;
};

void BFS(){
    int cnt = 0;
    queue<Elem> que;
    vector<Elem> vec;
    stack<int> stk;
    Elem tmpE {-1, -1};
    vec.push_back(tmpE);
    tmpE.parent = 0;
    for (int i = 0; i < N; ++i){
        if (graph[i].firJump){
            tmpE.idx = i;
            que.push(tmpE);
            visited[i] = true;
        }
    }
    bool flag = false;
    while (!que.empty()){
        Elem crtE = que.front();
        que.pop();
        vec.push_back(crtE);
        if (graph[crtE.idx].isSafe){ flag = true; break;}
        ++cnt;

        for (int i = 0; i < N; ++i){
            if (!visited[i] && canJump(i, crtE.idx)){
                visited[i] = true;
                tmpE.idx = i;
                tmpE.parent = cnt;
                que.push(tmpE);
            }
        }

    }
    if (flag){
        int rCnt = 1;
        for (int i = cnt + 1; i > 0; i = vec[i].parent){
            stk.push(vec[i].idx);
            ++rCnt;
        }
        cout << rCnt << endl;
        while (!stk.empty()){
            int i = stk.top();
            stk.pop();
            cout << graph[i].x << ' ' << graph[i].y << endl;
        }
    }
    else cout << 0 << endl;
    
    return;
}

int main(){
    ios::sync_with_stdio(false);
    // freopen("E:\\in.txt", "r", stdin);
    cin >> N >> D;
    if (D >= kBound){ cout << 1 << endl; return 0; }//one jump to shore;
    double islandJump = (kRadi + D) * (kRadi + D);
    PNode tmpN;
    for (int i = 0 ;i < N; ++i){
        cin >> tmpN.x >> tmpN.y;
        tmpN.isSafe = getSafe(tmpN);
        tmpN.dist = tmpN.x * tmpN.x + tmpN.y * tmpN.y;
        //if this croc to which James can jump from island;
        if (tmpN.dist <= islandJump ){
            tmpN.firJump = true;
            //insertion sort by distance to island;
            int j;
            for (j = i; j > 0 && graph[j - 1].dist > tmpN.dist; --j)
                graph[j] = graph[j - 1];
            graph[j] = tmpN;
        }
        else graph[i] = tmpN;
        tmpN.firJump = false;
    }
    D = D * D;//for convenience of comparation;
    BFS();
    return 0;
}