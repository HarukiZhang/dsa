#include<iostream>
#include<vector>
using namespace std;

constexpr int kMaxSize = 100010;
constexpr int kRadix = 51;//ages from 0 to 50;

int N;
int list[kMaxSize];
int bucket[kRadix]{};

void read();
void output();
inline void swap(int &a, int &b);

void insertion_sort(int arr[], int size);
void heap_sort(int arr[], int size);
void quick_sort(int arr[], int size);
void bucket_sort(int arr[], int size);

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; ++i)
        list[i] = -1;
    read();
    //sort ........
    // quick_sort(list, N);
    bucket_sort(list, N);
    // insertion_sort(list, N);
    // output();
    return 0;
}

void bucket_sort(int arr[], int size){
    //sorting;
    for (int i = 0; i < size; ++i)
        ++bucket[arr[i]];
    //output;
    for (int i = 0; i < kRadix; ++i)
        if (bucket[i] != 0)
            cout << i << ':' << bucket[i] << endl;
    return;
}

void quick_sort(int arr[], int size){
    int lf = 0, rt = size - 1;
    while (lf < rt){
        while (lf < rt && arr[rt] >= arr[lf]) --rt;
        swap(arr[lf], arr[rt]);
        while (lf < rt && arr[lf] <= arr[rt]) ++lf;
        swap(arr[lf], arr[rt]);
    }
    int diff = lf;
    if (diff > 0){
        if (diff > 100) quick_sort(arr, diff);
        else insertion_sort(arr, diff);
    }
    diff = size - lf - 1;
    if (diff > 0){
        if (diff > 100) quick_sort(arr, diff);
        else insertion_sort(arr, diff);
    }
    return;
}

inline void percDown(int arr[], int sta, int stp){//for max heap;
    int parent, child;
    parent = sta;
    int tmp = arr[parent];
    for (; (child = parent * 2 + 1) < stp; parent = child){
        if (child < stp - 1 && arr[child + 1] > arr[child])
            ++child;//if rtSub == lfSub, choose lfSub;
        if (tmp < arr[child])
            arr[parent] = arr[child];
        else break;
    }
    arr[parent] = tmp;
    return;
}

void heap_sort(int arr[], int size){
    for (int i = N / 2 - 1; i >= 0; --i)
        percDown(arr, i, N);
    for (int i = N - 1; i > 0; --i){
        swap(arr[0], arr[i]);//swap max value to crt tail and ignore it;
        percDown(arr, 0, i);
    }
    return;
}

void insertion_sort(int arr[], int size){
    for (int i = 0; i < size; ++i){
        int tmp = arr[i], j;
        for (j = i - 1; j >= 0; --j){
            if (arr[j] <= tmp){
                arr[j + 1] = tmp;
                break;
            }
            arr[j + 1] = arr[j];
        }
        if (j == -1)
            arr[0] = tmp;
    }
    return;
}

void swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
    return;
}

void read(){
    for (int i = 0; i < N; ++i)
        cin >> list[i];
    return;
}

void output(){
    int cnt = 1, crt = list[0], last;
    cout << crt << ':';
    for (int i = 1; i < N; ++i){
        last = crt;
        crt = list[i];
        if (crt == last) ++cnt;
        else {
            cout << cnt << endl;
            cnt = 1;
            cout << crt << ':';
        }
    }
    cout << cnt << endl;
}