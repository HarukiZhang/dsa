#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

constexpr int kInfty = ~(1<<31), kMaxCityN = 100;
constexpr int stt_Collected = -1, stt_Biult = 0;

struct Road {
    int from, to, expense;
    bool operator<(const Road &r) const {
        return expense > r.expense;
    }
};

class UCSet {
public:
    UCSet(int raw_list[], int cap):capacity{cap}, list{raw_list} {
        for (int i = 0; i < capacity; ++i)
            list[i] = -1;
    }
    bool unionSet(Road rd){
        int x = find(rd.from),
            y = find(rd.to);
        if (x == y) return false;
        else if (list[x] < list[y]){
            list[x] += list[y];
            list[y] =  x;
        }
        else {
            list[y] += list[x];
            list[x] = y;
        }
        return true;
    }
private:
    int find(int x){
        if (list[x] < 0) return x;
        return list[x] = find(list[x]);
    }

    int capacity;
    int *list;
};

int cityN, roadN;

priority_queue<Road> roads;
int ucset_raw[kMaxCityN];

int Kruskal(UCSet &MST, int eN_exp){
    int wpl = 0;
    int eN_Mst = 0;
    while ( eN_Mst < eN_exp && !roads.empty() ){
        Road crtR = roads.top(); //implement with minheap;
        roads.pop();
        if ( MST.unionSet(crtR) ){//if do not constitute circulation;
            ++eN_Mst;
            wpl += crtR.expense;//roads is a minheap;
        }
    }
    if (eN_Mst < eN_exp)
        return -1;
    return wpl;
}

void solution_Kruskal(){
    scanf("%d ", &cityN);
    UCSet MinSpanTree (ucset_raw, cityN);
    roadN = cityN *( cityN - 1) / 2;
    int expected_edgeN = cityN - 1;
    for (int i = 0; i < roadN; ++i){
        Road ri;
        int isBiult;
        scanf("%d %d %d %d ", &ri.from, &ri.to, &ri.expense, &isBiult);
        if (isBiult == 0){
            roads.push(ri);
        }
        else {//if not biult;
            if ( MinSpanTree.unionSet(ri) )//if in one set, and union them;
                --expected_edgeN; 
        }
    }
    printf("%d", Kruskal(MinSpanTree, expected_edgeN));
    return;
}


struct Elem {
    bool isBiult;
    int to, exps;
    bool operator<(const Elem &e) const {
        return exps > e.exps;
    }
};

vector<Elem> map[kMaxCityN];

int Prim(int vIdx){
    //initilization;
    int totExps = 0, vertCnt = 0;
    int exps[kMaxCityN];
    for (int i = 0; i <= cityN; ++i)
        exps[i] = kInfty;
    for (Elem e : map[vIdx])
        exps[e.to] = e.exps;
    /*Attention: differentiate status "collected" and "biult";*/
    exps[vIdx] = stt_Collected;
    ++vertCnt;
    while ( true ){
        int crt = -1, minCost = kInfty;
        for (int i = 1; i <= cityN; ++i)
            if (exps[i] != stt_Collected && minCost > exps[i]){
                crt = i;
                minCost = exps[i];
            }
        if (crt == -1 ) break;
        totExps += minCost;
        exps[crt] = stt_Collected;//collect it;
        ++vertCnt;
        for (Elem el : map[crt]){
            if (exps[el.to] != stt_Collected){//if uncollected;
                if (el.exps < exps[el.to])
                    exps[el.to] = el.exps;
            }
        }
    }
    if (vertCnt != cityN)
        return -1;
    return totExps;
}

void solution_Prim(){
    scanf("%d ", &cityN);
    roadN = cityN *( cityN - 1) / 2;
    for (int i = 0;i < roadN; ++i){
        int v1, v2;
        Elem ei;
        scanf("%d %d %d %d ", &v1, &v2, &ei.exps, &ei.isBiult);
        if (ei.isBiult)
            ei.exps = stt_Biult;//here initiate expense to stt_Biult,
                                //which should be differentiated with stt_Collected;
        ei.to = v2;
        map[v1].push_back(ei);
        ei.to = v1;
        map[v2].push_back(ei);
    }
    int res = Prim(1);
    printf("%d", res);
    return;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);

    solution_Prim();

    return 0;
}