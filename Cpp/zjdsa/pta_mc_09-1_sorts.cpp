#include<iostream>
using namespace std;

constexpr int kMaxLen = 100;
constexpr int kCutOff = 50;

void insertion_sort(int *sta, int *end){
    for (int *p = sta + 1; p < end; ++p){
        int tmp = *p, *q = p;
        for (; q > sta && *(q - 1) > tmp; --q)
            *q = *(q - 1);
        *q = tmp;
    }
    return;
}

inline void select_pivot(int *sta, int *tail){
    int *md = sta + ((tail - sta) >> 1);
    int t;
    if (*sta > *md){
        if (*sta > *tail){
            if (*md > *tail){//sta > md > tail;
                t = *md; *md = *sta; *sta = t;      
            }
            else {//sta > tail >= md;
                t = *tail; *tail = *sta; *sta = t;
            }
        }
    }
    else {//sta <= md;
        if (*sta < *tail){
            if (*tail < *md){//sta <= tail < md;
                t = *tail; *tail = *sta; *sta = t;
            }
            else {//sta <= md < tail;
                t = *md; *md = *sta; *sta = t;
            }
        }
    }
    return;
}

void q_sort(int *sta, int *end){
    if (end - sta < kCutOff) {
        insertion_sort(sta, end);
        return;
    }
    int *lf = sta, *rt = end -1, t;
    select_pivot(lf, rt);
    while (lf < rt){
        while (lf < rt && *rt >= *lf) --rt;
        t = *lf; *lf = *rt; *rt = t;
        while (lf < rt && *lf <= *rt) ++lf;
        t = *lf; *lf = *rt; *rt = t;
    }
    q_sort(sta, lf);
    q_sort(rt + 1, end);
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
        
    // q_sort(list, list + N);
    select_pivot(list, list + (N - 1));

    for (int i = 0; i < N; ++i){
        if (i) cout << ' ';
        cout << list[i];
    }
    return 0;
}