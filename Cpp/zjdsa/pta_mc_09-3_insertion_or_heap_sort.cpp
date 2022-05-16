#include<iostream>
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

void heap_sort(){
    //find heap bottom;
    //tail is the first elem (reversely) that smaller than top;
    int i = N - 1, t = part[0];
    for (; i > 0 && part[i] >= t; --i);
    //swap max with tail;
    part[0] = part[i];
    part[i] = t;
    t = part[0];
    //percolate down;
    int fa = 0, sn;
    for (--i; (sn = (fa << 1) + 1) <= i; fa = sn){
        if (sn != i && part[sn + 1] > part[sn]) ++sn;
        if (t < part[sn]) part[fa] = part[sn];
        else break;
    }
    part[fa] = t;
    return;
}


int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> ori[i];
    for (int i = 0; i < N; ++i)
        cin >> part[i];
    int idx = 1;
    for (; idx < N && part[idx - 1] <= part[idx]; ++idx);
    int ti = idx;
    for (; ti < N && ori[ti] == part[ti]; ++ti);
    if (ti == N){
        cout << "Insertion Sort" << endl;
        insertion_sort(idx);
    }
    else {
        cout << "Heap Sort" << endl;
        heap_sort();
    }
    for (ti = 0; ti < N; ++ti){
        if (ti) cout << ' ';
        cout << part[ti];
    }
    return 0;
}