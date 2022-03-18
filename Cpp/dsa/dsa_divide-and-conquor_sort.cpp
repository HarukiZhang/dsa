#include<iostream>
#include<utility>
#include<random>
#include<string>
using namespace std;

void myMerge(int* arr, int st, int md, int tl, int* tmp){
    int ofsT = 0, ofs1 = st, ofs2 = md + 1;
    while (ofs1 <= md && ofs2 <= tl){
        if (arr[ofs1] < arr[ofs2])
            tmp[ofsT++] = arr[ofs1++];
        else
            tmp[ofsT++] = arr[ofs2++];
    }
    while (ofs1 <= md)
        tmp[ofsT++] = arr[ofs1++];
    while (ofs2 <= tl)
        tmp[ofsT++] = arr[ofs2++];
    for (int i = 0; i < ofsT; ++i)
        arr[st + i] = tmp[i];
}

void myMergeSort(int* arr, int start, int tail, int* tmp){
    if (start < tail){

        int mid = (start + tail) / 2;

        myMergeSort(arr, start, mid, tmp);
        myMergeSort(arr, mid + 1, tail, tmp);

        myMerge(arr, start, mid, tail, tmp);

    }
}

void myQSort(int* arr, int st, int ed){
    if (st >= ed) return;
    int k = arr[st], lf = st, rt = ed;
    while (lf < rt){
        while (lf < rt && arr[rt] >= k) --rt;
        swap(arr[lf], arr[rt]);
        while (lf < rt && arr[lf] <= k) ++lf;
        swap(arr[lf], arr[rt]);
    }//after while-loop, arr[lf] == k;
    myQSort(arr, st, lf - 1);
    myQSort(arr, lf + 1, ed);
}

int arr1[100];
int tmp1[100];

int main(){
    string str{"haruki's seed"};
    seed_seq mySeed (str.begin(), str.end());
    minstd_rand genRand{mySeed};
    for (int i = 0; i < 100; ++i){
        arr1[i] = genRand();
    }
    myMergeSort(arr1, 0, 99, tmp1);

    cout << "Complete";
}