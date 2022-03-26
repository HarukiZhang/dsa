/*Use data of pta dsa en 7-25 Harry Potter's Exam*/
#include<iostream>
#include<vector>
using namespace std;

constexpr int kInfty = ~(1 << 31);
constexpr int kMaxLen = 128;

struct GNode {
    int into;
    int splLen;
};

vector<GNode> VGraph[kMaxLen];

int animalN, spellN;
int dist[kMaxLen][kMaxLen];

class MinHeap {
public:
    MinHeap(int crtV)
        : crtVtx {crtV}
    {
        list[0] = -1;//lookout;
    }
    ~MinHeap(){}
    bool empty(){ return size == 0; }
    void insert(int v);
    int pop();
private:
    inline void percolate(int ptr);
    inline bool compare(int a, int b);
    int size = 0;//num of vertex;
    int capacity = kMaxLen;
    int crtVtx;
    int list[kMaxLen];
};

void Dijkstra(int ptr);

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> animalN >> spellN;
    GNode tmp;
    int turn, into;
    for (int i = 0; i < spellN; ++i){
        cin >> turn >> into >> tmp.splLen;
        tmp.into = into;
        VGraph[turn].push_back(tmp);
        tmp.into = turn;
        VGraph[into].push_back(tmp);
    }

    /*initialization of dist and path*/
    for (int i = 1; i <= animalN; ++i){//starts from idx 1;
        for (int j = 1; j <= animalN; ++j){
            dist[i][j] = kInfty;
        }
        for (auto it = VGraph[i].begin(); it != VGraph[i].end(); ++it){
            dist[i][it->into] = it->splLen;
        }
    }

    for (int i = 1; i <= animalN; ++i){//starts from idx 1;
        Dijkstra(i);
    }
    
    int minS=kInfty,tar;
    for(int i=1;i<=animalN;++i){
        int maxS=-1;
        for(int j=1;j<=animalN;++j){
            if(dist[i][j]==kInfty){
                cout<<0<<endl; return 0;
            }
            if(dist[i][j]>maxS) maxS=dist[i][j];
        }
        if(maxS<minS){
            minS=maxS;
            tar=i;
        }
    }
    cout<<tar<<" "<<minS << endl;
    return 0;
}

void Dijkstra(int ptr){
    MinHeap minheap { ptr };
    bool collected[kMaxLen]{};
    dist[ptr][ptr] = 0;//self to self is zero;
    minheap.insert(ptr);
    collected[ptr]=true;
    while ( !minheap.empty() ){//every vertex in minheap will be popped out;
        int crtV = minheap.pop();
        auto itW=VGraph[crtV].begin(), ited=VGraph[crtV].end();
        for ( ;itW != ited; ++itW ){
            /*shortening path is independent of collecting vertex;
                ie, there should be two independent if statement,
                rahter than nested;*/
            int tmp = dist[ptr][crtV] + dist[crtV][itW->into];
            if (tmp < dist[ptr][itW->into]){//core algorithm;
                dist[ptr][itW->into] = tmp;
                dist[itW->into][ptr] = tmp;
            }
            if (collected[itW->into] == false){
                minheap.insert(itW->into);
                /*updating collected[] should be here, for in outer while-loop,
                it is constrained that all vertex that has been inserted into minheap
                will be popped out to the collected set;*/
                collected[itW->into] = true;
            }
        }
    }
    return;
}


void MinHeap::insert(int v){
    int ptr = ++size;
    for ( ; compare(v, list[ptr/2]); ptr/=2){//if v > list[ptr/2];
        list[ptr] = list[ptr/2];
    }
    list[ptr] = v;
    return;
}

int MinHeap::pop(){
    int ret = list[1];
    list[1] = list[size--];
    percolate(1);
    return ret;
}

void MinHeap::percolate(int ptr){
    int parent = ptr, child;
    int data = list[ptr];
    for ( ; (child = parent * 2) <= size; parent = child){
        if (child != size && compare(list[child + 1], list[child]))
            ++child;//if list[child + 1] < list[child], choose smaller one;
        if (compare(list[child], data))//if list[child] < data;
            list[parent] = list[child];//float up;
        else break;
    }
    list[parent] = data;
    return;
}

bool MinHeap::compare(int a, int b){
    return dist[crtVtx][a] < dist[crtVtx][b];
}


/*
0       1       70      61      81      51
1       0       71      60      80      50
70      71      0       70      120     80
61      60      70      0       50      60
81      80      120     50      0       60
51      50      80      60      60      0


0       1       70      61      81      51
1       0       71      60      80      50
70      71      0       70      120     80
61      60      70      0       50      60
81      80      120     50      0       60
51      50      80      60      60      0
*/