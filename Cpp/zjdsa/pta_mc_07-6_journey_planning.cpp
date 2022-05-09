#include<iostream>
#include<vector>
#include<queue>
using namespace std;
constexpr int kMaxLen = 512, kInf = 1000;

int cityN, roadM, Sta, Dest;

struct Node {
    int to, len, charge;
};

vector<Node> Map[kMaxLen];
int dist[kMaxLen];
int minCharge[kMaxLen];
bool collect[kMaxLen];

struct Elem {
    int to, len;
    bool operator<(const Elem &e) const {
        return len > e.len;
    }
};

void Dijkstra(){
    priority_queue<Elem> que;
    for (int i = 0; i < cityN; ++i)
        dist[i] = minCharge[i] = kInf;
    Elem tmpE {Sta, 0};
    que.push(tmpE);
    dist[Sta] = minCharge[Sta] = 0;
    collect[Sta] = true;
    while (!que.empty()){
        Elem crtE = que.top();
        que.pop();
        for (auto nod : Map[crtE.to]){
            //tmpDist: distance to nod.to via crtE.to;
            //calc: (min dist from Sta to crtE.to) + (len of the last period of road);
            int tmpDist = dist[crtE.to] + nod.len;
            //tmpCharge: the same concept as dist;
            int tmpCharge = minCharge[crtE.to] + nod.charge;
            //update should be independent of collection;
            if (tmpDist < dist[nod.to]){
                dist[nod.to] = tmpDist;
                minCharge[nod.to] = tmpCharge;
            }
            else if (tmpDist == dist[nod.to]){
                if (tmpCharge < minCharge[nod.to])
                    minCharge[nod.to] = tmpCharge;
            }
            if (collect[nod.to] == false){
                collect[nod.to] = true;
                tmpE.to = nod.to;
                tmpE.len = dist[nod.to];
                que.push(tmpE);
            }
        }
    }
    cout << dist[Dest] << ' ' << minCharge[Dest] << endl;
    return;
}

int main(){
    ios::sync_with_stdio(false);
    // freopen("E:\\in.txt", "r", stdin);
    cin >> cityN >> roadM >> Sta >> Dest;
    Node t;
    int v1, v2;
    for (int i = 0; i < roadM; ++i){
        cin >> v1 >> t.to >> t.len >> t.charge;
        Map[v1].push_back(t);
        v2 = t.to;
        t.to = v1;
        Map[v2].push_back(t);
    }
    Dijkstra();
    return 0;
}