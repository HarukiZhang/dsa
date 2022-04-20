#include<iostream>
#include<vector>

using namespace std;

constexpr int kMaxSize = 100010;
constexpr int kRadix = 10, kBucketLen = 19, kOffset = 9;
/*
Radix for int is still 10, but prepare 9 more buckets for negative digits;
  Buckets        : -9 -8 ... -1 0  1 ... 9  ;
  Correspond idx : 0  1 ...   8 9 10 ... 18 ;
so, need to left-shift all digit 
so that negative digits are arranged to positive indices;
*/

typedef struct Node *PtrToNode;
struct Node {
    int key;
    PtrToNode next;
};

struct HeadNode {
    PtrToNode head, tail;
};
typedef struct HeadNode Bucket[kBucketLen];

int N;
int origin[kMaxSize];

int getDigit(int x , int d){
    int r;
    for (int i = 1; i <= d; ++i){
        r = x % kRadix;
        x /= kRadix;
    }
    return r;
}

void radix_sort_LSD(int arr[], int size, int maxDig){
    //initialization;
    Bucket bucket;
    PtrToNode tmp, p, list = nullptr;
    for (int i = 0; i < kBucketLen; ++i)//initialize buckect null;
        bucket[i].head = bucket[i].tail = nullptr;
    for (int i = 0; i < size; ++i){//reversely store origin seq into initial link-list;
        tmp = new Node {arr[i], list};
        list = tmp;
    }
    //start to sort;
    for (int dig = 1; dig <= maxDig; ++dig){
        //allocation;
        p = list;
        while (p){
            int d = getDigit(p->key, dig);
            int idx = d + kOffset;//let minus num shift left to positive pos;
            //erase from list;
            tmp = p;
            p = p->next;
            //insert into bucket[idx];
            tmp->next = nullptr;
            if (bucket[idx].head == nullptr)
                bucket[idx].head = bucket[idx].tail = tmp;
            else {//insert at tail side;
                bucket[idx].tail->next = tmp;//insert elem after tail;
                bucket[idx].tail = tmp;//record tail elem of crt list at bucket;
            }
        }
        //collection;
        list = nullptr;
        for (int i = kBucketLen - 1; i >= 0; --i){
            if (bucket[i].head){
                bucket[i].tail->next = list;
                list = bucket[i].head;
                bucket[i].head = bucket[i].tail = nullptr;//clear buckets;
            }
        }
    }

    for (int i = 0; i < size; ++i){
        tmp = list;
        list = list->next;
        arr[i] = tmp->key;
        delete tmp;
    }
    return;
}

int main(){
    ios::sync_with_stdio(false);
    // freopen("E:\\in.txt", "r", stdin);
    
    cin >> N;
    int maxValue = 0, minValue = 0;
    for (int i = 0; i < N; ++i){
        cin >> origin[i];
        if (origin[i] > maxValue)
            maxValue = origin[i];
        if (origin[i] < minValue)
            minValue = origin[i];
    }
    int maxDigit = 0;
    while (maxValue != 0 || minValue != 0){
        if (maxValue != 0) maxValue /= kRadix;
        if (minValue != 0) minValue /= kRadix;
        ++maxDigit;
    }
    radix_sort_LSD(origin, N, maxDigit);
    for (int i = 0; i < N; ++i){
        if (i) cout << ' ';
        cout << origin[i];
    }
    return 0;
}