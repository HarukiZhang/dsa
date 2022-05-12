/*result: slower and comsume more space than implementation of priority_queue;*/
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;

constexpr int kMaxVilla = 1024, kMaxRoad = 3 * kMaxVilla;

struct Node {
    int from, to, cost;
};

class UCSet {
public:
    UCSet(int s);
    bool unionS(int x, int y);
private:
    int find(int x);
    int list[kMaxVilla];
};

Node roads_info[kMaxRoad];
int roads_index[kMaxRoad];

bool myComp(int n1, int n2){
    return roads_info[n1].cost < roads_info[n2].cost;
}

int main(){
    ios::sync_with_stdio(false);
    // freopen("E:\\in.txt", "r", stdin);
    int cityN, roadM;
    cin >> cityN >> roadM;
    for (int i = 0; i < roadM; ++i){
        cin >> roads_info[i].from >> roads_info[i].to >> roads_info[i].cost;
        roads_index[i] = i;
    }
    sort(roads_index, roads_index + roadM, myComp);//sort to ascending order by cost;
    UCSet mst (cityN);
    int n_mst = 0, minCost = 0;
    for (int i = 0; i < roadM; ++i){
        Node &crtN = roads_info[roads_index[i]];
        if (mst.unionS(crtN.from, crtN.to)){
            ++n_mst;
            minCost += crtN.cost;
            if (n_mst == cityN - 1) break;
        }
    }
    if (n_mst == cityN - 1)
        cout << minCost << endl;
    else cout << -1 << endl;
    return 0;
}

UCSet::UCSet(int s){
    for (int i = 0; i <= s; ++i)
        list[i] = -1;
}

bool UCSet::unionS(int x, int y){
    if ( ( x = find(x) ) != ( y = find(y) ) ){
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
    else return false;
}

int UCSet::find(int x){
    //find() non-recursive;
    if (list[x] < 0) return x;
    stack<int> stk;
    int px = x, rt = x;
    stk.push(x);
    while ((px = stk.top()) >= 0)
        stk.push(list[px]);
    stk.pop();
    if (!stk.empty()){
        rt = stk.top();
        stk.pop();
    }
    while (!stk.empty()){
        list[stk.top()] = rt;
        stk.pop();
    }
    return rt;
}