#include<iostream>
#include<queue>
using namespace std;

constexpr int kMaxLen = 128, kInf = 200;

struct Elem {
    int dist, to;
    bool operator<(const Elem &e) const {
        return dist > e.dist;
    }
};

int anmN, mgcM;

int magicBook[kMaxLen][kMaxLen]{};
int minSpell[kMaxLen][kMaxLen]{};

void Dijkstra(int n){
    priority_queue<Elem> que;
    bool visited[kMaxLen]{};
    for (int i = 1; i <= anmN; ++i)
         if (magicBook[n][i] < kInf)
            que.push(Elem {magicBook[n][i], i});
    minSpell[n][n] = 0;//set self to self as 0;
    visited[n] = true;
    while (!que.empty()){
        Elem crtE = que.top();
        que.pop();
        for (int si = 1; si <= anmN; ++si){
            if (magicBook[crtE.to][si] < kInf){
                int tmpDist = crtE.dist + minSpell[crtE.to][si];
                if (tmpDist < minSpell[n][si]){
                    minSpell[n][si] = tmpDist;
                    minSpell[si][n] = tmpDist;
                }
                if (!visited[si]){
                    visited[si] = true;
                    que.push(Elem {minSpell[n][si], si});
                }
            }
        }
    }
    return;
}

void output(){
    int resA = -1, resL = kInf, tmpL = -1;
    for (int i = 1; i <= anmN; ++i){
        tmpL = -1;
        for (int j = 1; j <= anmN; ++j){
            if (minSpell[i][j] == kInf){
                cout << 0;
                return;
            }
            if (minSpell[i][j] > tmpL)
                tmpL = minSpell[i][j];
        }
        if (tmpL < resL){//output the animal with smallest index;
            resL = tmpL;
            resA = i;
        }
    }
    cout << resA << ' ' << resL;
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> anmN >> mgcM;
    for (int i = 1; i <= anmN; ++i)
        for (int j = 1; j <= anmN; ++j)
            magicBook[i][j] = kInf;
    int v1, v2, wi;
    for (int i = 0; i < mgcM; ++i){
        cin >> v1 >> v2 >> wi;
        magicBook[v1][v2] = magicBook[v2][v1] = wi;
    }
    for (int i = 1; i <= anmN; ++i){
        for (int j = 1; j <= anmN; ++j){
            minSpell[i][j] = magicBook[i][j];//self to self is also kInf;
        }
    }
    for (int i = 1; i <= anmN; ++i)
        Dijkstra(i);
    output();
    
    //debug:

    return 0;
}