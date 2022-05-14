#include<iostream>
using namespace std;

constexpr int kMaxLen = 100;

void q_sort(int *sta, int *end){
    if (sta >= end) return;
    int *lf = sta, *rt = end -1, t;
    while (lf < rt){
        while (lf < rt && *rt >= *lf) --rt;
        t = *lf; *lf = *rt; *rt = t;
        while (lf < rt && *lf < *rt) ++lf;
        t = *lf; *lf = *rt; *rt = t;
    }
    q_sort(sta, lf);
    q_sort(rt + 1, end);
    return;
}

void insertion_sort(int *sta, int *end){
    for (int *p = sta + 1; p < end; ++p){
        int tmp = *p, *q = p;
        for (; q > sta && *(q - 1) > tmp; --q)
            *q = *(q - 1);
        *q = tmp;
    }
    return;
}

int list[kMaxLen];

int main(){
    // ios::sync_with_stdio(false);
    freopen("E:\\in.txt", "r", stdin);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> list[i];
    insertion_sort(list, list + N);
    for (int i = 0; i < N; ++i){
        if (i) cout << ' ';
        cout << list[i];
    }
    return 0;
}