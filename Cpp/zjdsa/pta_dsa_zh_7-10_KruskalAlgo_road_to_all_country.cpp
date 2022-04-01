/*
现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，
求使每个村落都有公路连通所需要的最低成本。

输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；随后的M行对应M条道路，
每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。
为简单起见，城镇从1到N编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多公路。
*/
#include<iostream>
#include<vector>
using namespace std;

constexpr int kInfty = ~(1 << 31);
constexpr int kMaxCity = 1024, kMaxRoad = 3*kMaxCity;

struct Edge {
    int vFrom, vTo, exps;
};
typedef int EdgePtr;

Edge edges[kMaxRoad];       //storage and hash;
EdgePtr edge_indices[kMaxRoad]; //for min heap; alike table-sort;

bool compare(EdgePtr a, EdgePtr b);

class MinHeap {  //elem is Edge;
public:
    using MHeapPtr = int;
    MinHeap(EdgePtr *l, int sz, bool (*pr)(EdgePtr, EdgePtr));
    EdgePtr pop();
private:
    void biuldUp();
    void percDown(MHeapPtr mhPtr);

    int size;
    EdgePtr *list;
    bool (*comp)(EdgePtr, EdgePtr);
};

class UCSet { //elem is Vertex;
public:
    using UCS_ptr = int;
    UCSet(int sz);
    bool unionSet(EdgePtr ePtr);
    bool checkSet(EdgePtr ePtr);
    int size();
private:
    UCS_ptr find(UCS_ptr x);
    
    int capacity;
    EdgePtr list[kMaxCity];
};

int cityN, roadM;

int Kruskal(MinHeap &unCollected, UCSet &MST);

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> cityN >> roadM;
    for (EdgePtr i = 0; i < roadM; ++i){
        cin >> edges[i].vFrom >> edges[i].vTo >> edges[i].exps;
        edge_indices[i] = i;
    }
    MinHeap minheap (edge_indices, roadM, compare);
    UCSet minSpanTree (cityN);
    int weighted_path_len = Kruskal(minheap, minSpanTree);
    cout << weighted_path_len;
    return 0;
}

/*Sample input:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3

Sample output:
12
*/

int Kruskal(MinHeap &unCollected, UCSet &MST){
    /*initialization*/
    int WPL = 0;
    int eN_unC = roadM,  //edge num in uncollected set;
        eN_MST = 0,      //edge num in MST;
        eN_exp = cityN - 1;  //expected edge num;
    /*algorithm*/
    while ( eN_MST < eN_exp && eN_unC != 0){
        int crtE = unCollected.pop();
        --eN_unC; // == unCollected.size();

        /*if crt edge do not constitute circulation;
            unionSet() method will check before union opt;*/
        if ( MST.unionSet(crtE) ){//if already in one set, .unionSet() return false;
            ++eN_MST;
            WPL += edges[crtE].exps;
        }
        //else ignore crtE;
    }
    if (eN_MST < eN_exp)//Spanning Tree do not exist;
        return -1;
    return WPL;
}

bool compare(EdgePtr a, EdgePtr b){
    return edges[a].exps > edges[b].exps;
}

MinHeap::MinHeap(EdgePtr *l, int sz, bool (*pr)(EdgePtr, EdgePtr))
    : size{sz}, list{l}
{
    biuldUp();
}

EdgePtr MinHeap::pop(){
    EdgePtr ret = list[0];
    list[0] = list[--size];
    percDown(0);
    return ret;
}

void MinHeap::biuldUp(){
    MHeapPtr ptr = (size - 1) / 2;
    for (; ptr >= 0; --ptr)
        percDown(ptr);
    return;
}

void MinHeap::percDown(MHeapPtr mhPtr){
    MHeapPtr parent = mhPtr, child;
    EdgePtr tar = list[mhPtr];
    for (; (child = (parent + 1) * 2 - 1) <= size; parent = child){
        if (child != size && compare(list[child], list[child + 1]))//if child > child + 1;
            ++child;
        if (compare(tar, list[child]))
            list[parent] = list[child];
        else break;
    }
    list[parent] = tar;
    return;
}


UCSet::UCSet(int sz) : capacity{sz} {
    for (UCS_ptr i = 0; i <= sz; ++i)
        list[i] = -1;//each vertex is initially an independent tree;
}

bool UCSet::unionSet(EdgePtr ePtr){
    UCS_ptr x = find(edges[ePtr].vFrom);
    UCS_ptr y = find(edges[ePtr].vTo);
    if (x == y) return false; // no need to union;
    if (list[x] < list[y]){
        list[x] += list[y];
        list[y] = x;
    }
    else {
        list[y] += list[x];
        list[x] = y;
    }
    return true; //actually union has been done;
}

bool UCSet::checkSet(EdgePtr ePtr){
    UCS_ptr x = find(edges[ePtr].vFrom);
    UCS_ptr y = find(edges[ePtr].vTo);
    return x == y;
}

UCSet::UCS_ptr UCSet::find(UCS_ptr x){
    if (list[x] < 0)
        return x;
    return list[x] = find(list[x]);//with path compression;
}