#include<iostream>
#include<cmath>
using namespace std;

constexpr int kBound = 50, kMaxLen = 128;
constexpr double kRadius = 7.5;

struct Node {
    int xc, yc;
    bool safe = false;
};

Node crocs[kMaxLen];
bool visited[kMaxLen]{};
int N, D;
bool escaped = false;//overall control flag;

bool judgeSafe(int x, int y){
    return fabs(kBound - fabs(x)) <= D || fabs(kBound - fabs(y)) <= D;
}
bool judgeJump(Node &a, Node &b){
    double limit = D;
    if ( (a.xc == 0 && a.yc == 0) || (b.xc == 0 && b.yc == 0) )
        limit += kRadius;
    //square distance : delta x ^ 2 + delta y ^ 2 = dist ^ 2;
    int sq_dist = (a.xc - b.xc) * (a.xc - b.xc) + (a.yc - b.yc) * (a.yc - b.yc);
    return limit * limit >= sq_dist;
}

void DFS(int ptr){
    if (crocs[ptr].safe){
        escaped = true;
        return;
    }
    visited[ptr] = true;
    for (int i = 1; i <= N; ++i){
        if ( visited[i] == false && judgeJump(crocs[ptr], crocs[i]) ){
            DFS(i);
            if (escaped) return;//return all stacks;
        }
    }
    visited[ptr] = false;
    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> N >> D;
    crocs[0] = Node {0, 0, false};//the island coordinate;
    for (int i = 1; i <= N; ++i){
        cin >> crocs[i].xc >> crocs[i].yc;
        crocs[i].safe = judgeSafe(crocs[i].xc, crocs[i].yc);
    }

    DFS(0);

    if ( escaped ) cout << "Yes";
    else cout << "No";

    return 0;
}

