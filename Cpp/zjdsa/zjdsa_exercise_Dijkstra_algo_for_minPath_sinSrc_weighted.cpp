/*Use data of pta dsa en 7-25 Harry Potter's Exam*/
#include<iostream>
#include<vector>
using namespace std;

constexpr int kInfty = ~(1 << 31);
constexpr int kMaxLen = 100;

struct GNode {
    int into;
    int splLen;
};

vector<GNode> VGraph[kMaxLen + 10];

int animalN, spellN;
int dist[kMaxLen + 10][kMaxLen + 10], path[kMaxLen + 10][kMaxLen + 10];

class MinHeap {
public:
    MinHeap(int crtV)
        : crtVtx   {crtV},
          list     {new int[capacity]}
    {
        list[0] = -1;//lookout;
        /*directly biuld up;*/
        for (int i = 1; i <= animalN; ++i)
            list[i] = i;
        size = animalN;
        for (int ptr = size / 2 ; ptr > 0; --ptr)
            percolate(ptr);

    }
    ~MinHeap(){
        delete[] list;
    }
    bool empty(){ return size == 0; }
    void insert(int v);
    int pop();
    void adjust(int tar);
private:
    inline void percolate(int ptr);
    inline bool compare(int a, int b);
    int size = 0;//num of vertex;
    int capacity = animalN + 10;
    int crtVtx;
    int *list;
};

void Dijkstra(int ptr);

int main(){
    freopen("E:\\in.txt", "r", stdin);

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
            path[i][j] = -1;
        }
        for (auto it = VGraph[i].begin(); it != VGraph[i].end(); ++it){
            dist[i][it->into] = it->splLen;
            path[i][it->into] = i;
        }
    }

    for (int i = 1; i <= animalN; ++i){//starts from idx 1;
        Dijkstra(i);
    }

    /*debug*/
    for (int i = 1; i <= animalN; ++i){
        for (int j = 1; j <= animalN; ++j){
            if (dist[i][j] < kInfty) cout << dist[i][j] << "\t";
            else cout << "Inf\t";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= animalN; ++i){
        for (int j = 1; j <= animalN; ++j)
            cout << path[i][j] << "\t";
        cout << endl;
    }
}

void Dijkstra(int ptr){
    /*biuld min heap*/
    MinHeap minheap { ptr };
    bool *collected = new bool[animalN + 10]{};
    /*algorithm*/
    dist[ptr][ptr] = 0;//self to self == 0;
    collected[ptr] = true;//collect self;
    while (!minheap.empty()){
        int crtV = minheap.pop();
        collected[crtV] = true;
        auto itW  = VGraph[crtV].begin(),
             ited = VGraph[crtV].end();
        for ( ;itW != ited; ++itW ){
            if ( collected[itW->into] == false ){
                int tmp = dist[ptr][crtV] + dist[crtV][itW->into];
                if ( tmp < dist[ptr][itW->into]){
                    dist[ptr][itW->into] = tmp;
                    
                    /*...
                    how to influence minheap?
                    ...*/
                    minheap.adjust(itW->into);//this opt consume time too much!!!

                    path[ptr][itW->into] = crtV;
                }
            }
        }
    }
    delete[] collected;
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

void MinHeap::adjust(int tar){
    int ptr;
    for (ptr = 1; ptr <= size; ++ptr)
        if (list[ptr] == tar) break;
    while ( compare(tar, list[ptr/2]) ){
        list[ptr] = list[ptr / 2];
        ptr /= 2;
    }
    list[ptr] = tar;
    return;
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