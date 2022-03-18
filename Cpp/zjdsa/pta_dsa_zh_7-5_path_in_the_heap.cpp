#include<iostream>
#include<queue>

using namespace std;

/*Required by problem : kMaxSize = 1000;*/
constexpr int kMaxSize = 128;
constexpr int kMinData = 1 << 31;

template<typename ElemType>
class MinHeap {
private:
    ElemType* data;
    int size = 0;
    int capacity = kMaxSize - 1;
public:
    MinHeap()
        : data{new ElemType [kMaxSize]}
    {
        data[0] = kMinData;
    }
    ~MinHeap(){ delete[] data; }
    bool empty(){ return size == 0; }
    bool full(){ return size == kMaxSize - 1; }
    void readIn(int num){
        size = num < capacity ? num : capacity;
        for (int i = 1; i <= size; ++i)
            scanf("%d", &data[i]);
        return;
    }
    void biuldUp();
    void percolate(int ptr);
    void printPath(int idx);
    void traversal_lv();
    bool insert(ElemType x);
    ElemType deleteMin();
};

int main(){
    freopen("E:\\in.txt", "r", stdin);
    MinHeap<int> myHeap;
    int N, t;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i){
        scanf("%d", &t);
        myHeap.insert(t);
    }
    int min = myHeap.deleteMin();
    myHeap.traversal_lv();
    return 0;
}

template<typename ElemType>
bool MinHeap<ElemType>::insert(ElemType x){
    if (full()) return false;
    ++size;//prepare one place;
    int ptr;
    for (ptr = size; data[ptr / 2] > x; ptr /= 2)
        data[ptr] = data[ptr / 2];//percolating down;
    data[ptr] = x;//set into the proper loc;
    return true;
}

template<typename ElemType>
ElemType MinHeap<ElemType>::deleteMin(){
    if (empty()) return kMinData;
    ElemType x = data[1];
    data[1] = data[size--];
    percolate(1);
    return x;
}

template<typename ElemType>
void MinHeap<ElemType>::printPath(int idx){
    if (idx > 0){
        printf("%d", data[idx]);
        idx /= 2;
    }
    while (idx > 0){
        printf(" %d", data[idx]);
        idx /= 2;
    }
    return;
}

template<typename ElemType>
void MinHeap<ElemType>::percolate(int ptr){
    int parent, child;
    ElemType X = data[ptr];
    for (parent = ptr; parent * 2 <= size; parent = child){
        child = parent * 2;
        if (child != size && data[child] > data[child + 1])
            ++child;
        if (X > data[child])//minHeap;
            data[parent] = data[child];
        else break;
    }
    data[parent] = X;
    return;
}

template<typename ElemType>
void MinHeap<ElemType>::biuldUp(){
    for (int i = size / 2; i > 0; --i)
        percolate(i);
    return;
}

template<typename ElemType>
void MinHeap<ElemType>::traversal_lv(){
    for (int i = 1; i <= size; ++i)
        printf("%d ", data[i]);
    return;
}