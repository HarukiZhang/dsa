#include "_haruki.h"
#include<iostream>
#include<functional>
#include<algorithm>
#include<random>
/*Using min heap to implement;*/
using namespace std;

constexpr int kMinData = 1 << 31;
constexpr int kStdCapacity = 127;//7 levels;

template<class ElemType, class FComp = less<ElemType> >
class Heap {
public:
    Heap()
        : capacity(kStdCapacity), data(new ElemType [capacity + 1])
    { data[0] = kMinData; }
    Heap(int _size)
        : capacity(_size), data(new ElemType [capacity + 1])
    { data[0] = kMinData; }
    ~Heap(){ delete[] data; }
    bool empty(){ return size == 0; }
    bool full(){ return size == capacity; }
    bool insert(ElemType x){
        if (full()) return false;
        ++size;
        int ptr;
        for (ptr = size; compare(x, data[ptr / 2]); ptr /= 2)
            data[ptr] = data[ptr / 2];
        data[ptr] = x;
        return true;
    }
    ElemType pop(){
        if (empty()) return kMinData;
        ElemType x = data[1];
        data[1] = data[size--];
        percolate(1);
        return x;
    }
    ElemType top(){ return data[1]; }
    void readIn(int* arr, int num){
        size = num > capacity ? capacity : num;
        for (int i = 1; i <= size; ++i)
            data[i] = arr[i - 1];
        biuldUp();
        return;
    }
    void traversal_lv(){
        int idx = 1;
        while (idx <= size) cout << data[idx++] << " ";
        return;
    }
private:
    void biuldUp(){
        for (int ptr = size / 2; ptr > 0; --ptr)
            percolate(ptr);
        return;
    }
    void percolate(int ptr){
        int parent, child;
        ElemType x = data[ptr];
        for (parent = ptr; (child = parent * 2) <= size; parent = child){
            if (child != size && compare(data[child + 1], data[child]))
                ++child;
            if (compare(data[child], x))//if x > child, percolate x down;
                data[parent] = data[child];
            else break;
        }
        data[parent] = x;
        return;
    }
protected:
    int size = 0;
    int capacity;
    ElemType* data;
    FComp compare;
};

constexpr int kFindSize = 10000;
constexpr int kDatabaseLen = 1'000'000;

int arr[kDatabaseLen + 10];
int out[kFindSize + 10];

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    LARGE_INTEGER t0, t1, t2, t3;
    int N = kDatabaseLen, M = kFindSize;
    
    seed_seq seed = {2022, 300, 200};
    mt19937 generator {seed};
    for (int i = 0; i < N; ++i)
        arr[i] = generator();
    

    QueryPerformanceCounter(&t0);
    Heap<int> minHeap{ M };
    minHeap.readIn(arr, M);
    for (int i = M; i < N; ++i){
        if (arr[i] > minHeap.top()){
            if (minHeap.full()) minHeap.pop();
            minHeap.insert(arr[i]);
        }
    }
    QueryPerformanceCounter(&t1);
    for (int i = 0; !minHeap.empty(); ++i)
        out[i] = minHeap.pop();
    
    QueryPerformanceCounter(&t2);
    sort(arr, arr + N, greater<int>());
    QueryPerformanceCounter(&t3);
    
    for (int i = 0; i < M; ++i)
        if (arr[M - i - 1] != out[i]){
            cout << "Wrong" <<endl;
            break;
        }
    cout << "Correct!" << endl;
    
    printPerfCounter(t0, t1, "heap : ");
    printPerfCounter(t2, t3, "sort : ");
    return 0;
}