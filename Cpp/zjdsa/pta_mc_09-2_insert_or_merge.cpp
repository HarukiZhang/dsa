#include<iostream>
#include<vector>
using namespace std;

constexpr int kMaxLen = 128;

int N;
int ori[kMaxLen], part[kMaxLen];

void insertion_sort(int i){
    int t = part[i];
    for (; i > 0 && part[i - 1] > t; --i)
        part[i] = part[i - 1];
    part[i] = t;
    return;
}

int get_interval(){
    int itvl = 1;
    while (itvl < N) itvl <<= 1;
    itvl >>= 1;//get max power of 2 as initial guess for interval;
    bool flag = false;
    for (; itvl > 2; itvl >>= 1){//interval cannot be lesser than 2;
        int i;
        for (i = 1; i < itvl && part[i - 1] < part[i]; ++i);
        if (i == itvl){
            int j = itvl >> 1;
            for (; j < N && part[j] >= part[j - 1]; j += itvl);
            if (j >= N) flag = true;
        }
        if (flag) break;
    }
    return itvl;
}

/*practical result is slower than above version;*/
int get_interval_optim(){
    int itvl = 2;
    for (; itvl < N; itvl <<= 1){
        int nxt_itvl = itvl << 1,
            i = 0;
        for (; i + itvl < N; i += nxt_itvl)
            if (part[i + itvl -1] > part[i + itvl])
                return itvl;
    }
    return itvl;
}

void merge(int sta[], int len, int itvl){
    if (len < 2) return;
    int lf = 0, rt = itvl,
        oi = 0;
    while (lf < itvl && rt < len){
        if (sta[lf] < sta[rt]) ori[oi++] = sta[lf++];
        else ori[oi++] = sta[rt++];
    }
    while (lf < itvl) ori[oi++] = sta[lf++];
    while (rt < len) ori[oi++] = sta[rt++];
    for (int i = 0; i < len; ++i) sta[i] = ori[i];
    return;
}

void merge_sort(int itvl){
    int next_itvl = itvl << 1;
    int i;
    for (i = 0; i < N - next_itvl; i += next_itvl){
        merge(part + i, next_itvl, itvl);
    }
    if (N - i > itvl)
        merge(part + i, N - i, itvl);
    return;
}

void output(){
    for (int i = 0; i < N; ++i){
        if (i) cout << ' ';
        cout << part[i];
    }
    return;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> ori[i];
    for (int i = 0; i < N; ++i)
        cin >> part[i];

    bool isIns = true;
    int fi = 1;
    for (; fi < N && part[fi] >= part[fi - 1]; ++fi);
    int idx = fi;
    for (; fi < N && part[fi] == ori[fi]; ++fi);
    if (fi != N) isIns = false;
    if (isIns){
        cout << "Insertion Sort" << endl;
        insertion_sort(idx);
    }
    else {
        cout << "Merge Sort" << endl;
        int itvl = get_interval_optim();
        merge_sort(itvl);
    }
    output();
    return 0;
}