#include<iostream>
#include<vector>
#include<queue>
using namespace std;

constexpr int kMaxLen = 1024;

class UCSet {
public:
    UCSet(int sz);
    bool unionS(int x, int y);
private:
    int find(int x);
    int list[kMaxLen];
};

struct Node {
    int from, to, cost;
    bool operator<(const Node &n) const {
        return cost > n.cost;
    }
};

int cityN, roadM;
//all road edge node directly stored into min heap;
priority_queue<Node> Que;

void Kruskal(){
    UCSet MST (cityN);//construct an empty set A;
    int n_MST = 0, //edge number collected into A;
        n_unC = roadM, //un-collected edge number;
        WPL = 0; //weighted path len;
    while (n_MST < cityN - 1 && n_unC > 0){
        Node crtN = Que.top();//find the min-weighted edge that has yet been collected;
        Que.pop();
        --n_unC;//un-collected edge number decreases;
        //check whether the edge found is safe for A;
        if ( MST.unionS(crtN.from, crtN.to) ){//if safe, union the edge into set A;
            ++n_MST;//size of set A increases;
            WPL += crtN.cost;
        }
    }
    if (n_MST == cityN - 1)//a spanning tree should have just the number of vertex - 1;
        cout << WPL << endl;
    else cout << -1 << endl;//spanning tree does not exist;
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> cityN >> roadM;
    Node tmpN;
    for (int i = 0; i < roadM; ++i){
        cin >> tmpN.from >> tmpN.to >> tmpN.cost;
        Que.push(tmpN);
    }
    Kruskal();
    return 0;
}

UCSet::UCSet(int sz){
    for (int i = 0; i <= sz; ++i)
        list[i] = -1;//initially, all city nodes are regarded as an individual tree;
}

int UCSet::find(int x){
    if (list[x] < 0) return x;//till the head node is found, return the index of it;
    return list[x] = find(list[x]);//goto parent node and compress the path;
}

bool UCSet::unionS(int x, int y){
    if ((x = find(x)) != (y = find(y))){
        if (list[x] < list[y]){
            list[x] += list[y];
            list[y] = x;
        }
        else {
            list[y] += list[x];
            list[x] = y;
        }
        return true;
    }
    return false;
}