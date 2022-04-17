#include<iostream>
#include<vector>
using namespace std;

constexpr int kMaxSize = 128;

int N;
int origin[kMaxSize], partial[kMaxSize];

void insertion_sort(int arr[], int size){
    for (int i = 1; i < size; ++i){
        int tmp = arr[i],
            j = i;
        for ( ; j > 0 && arr[j - 1] > tmp; --j)
            arr[j] = arr[j - 1];
        arr[j] = tmp;
    }
    return;
}

void insertion_sort_one_turn(int arr[], int size, int idx){
    int tmp = arr[idx], j = idx;
    for (; j > 0 && arr[j - 1] > tmp; --j)
        arr[j] = arr[j - 1];
    arr[j] = tmp;
    return;
}

void merge(int arr[], int size, int iRt, int tmpArr[]){
    int idx1 = 0, idx2 = iRt, idx3 = 0;
    while (idx1 < iRt && idx2 < size){
        if (arr[idx1] < arr[idx2]) tmpArr[idx3++] = arr[idx1++];
        else tmpArr[idx3++] = arr[idx2++];
    }
    while (idx1 < iRt) tmpArr[idx3++] = arr[idx1++];
    while (idx2 < size) tmpArr[idx3++] = arr[idx2++];
    for (int i = 0; i < size; ++i) arr[i] = tmpArr[i];
    return;
}

void merge_sort_recur(int arr[], int size, int tmpArr[]){
    if (size > 2){
        merge_sort_recur(arr, size / 2, tmpArr);
        merge_sort_recur(arr + (size / 2), size - size / 2, tmpArr);
    }
    merge(arr, size, size / 2, tmpArr);
    return;
}

void merge_sort(int arr[], int size){
    int *tmpArr = new int[size];
    merge_sort_recur(arr, size, tmpArr);
    delete[] tmpArr;
    return;
}

void merge_sort_nonrec(int arr[], int size, int base){
    int *tmpArr = new int [size];
    while (base < size){
        int i;
        for (i = 0; i + base < size; i += base)
            merge(arr + i, base, base / 2, tmpArr);
        if (i < size) merge(arr + i, size - i, (size - i) / 2, tmpArr);
        base <<= 1;//base *= 2;
    }
    merge(arr, size, base >> 1, tmpArr);
    delete[] tmpArr;
    return;
}

void merge_sort_one_turn(int arr[], int size, int base){
    int *tmpArr = new int[size];
    base <<= 1;
    int i;
    for (i = 0; i + base < size; i += base)
        merge(arr + i, base, base / 2, tmpArr);
    if (i < size)
        merge(arr + i, size - i, (size - i + 1) / 2, tmpArr);
    delete[] tmpArr;
    return;
}

int getMaxIntvl(){
    int intvl = 2;
    for (; intvl <= N; intvl <<= 1){
        for (int i = 0; i + intvl < N; i += 2 * intvl){
            if (partial[i + intvl - 1] > partial[i + intvl])
                return intvl;
        }
    }
    return intvl >> 1;
}

void judge(){
    bool isIns = true;
    int maxAscendLen = 0;
    //count max asceding substr length;
    int i;
    for (i = 0; i < N; ++i){
        ++maxAscendLen;
        if (partial[i] > partial[i + 1]) break;
    }
    //compare post-n-nums whether intact;
    for (++i; i < N; ++i)
        if (partial[i] != origin[i]){
            isIns = false;
            break;
        }
    if (isIns){
        cout << "Insertion Sort" << endl;
        insertion_sort_one_turn(partial, N, maxAscendLen);
    }
    else {//is merge sort;
        //get max interval of merge sort;
        int intvl = getMaxIntvl();
        cout << "Merge Sort" << endl;
        merge_sort_one_turn(partial, N, intvl);
    }
    bool fir = true;
    for (int i = 0; i < N; ++i){
        if (fir) fir = false;
        else cout << ' ';
        cout << partial[i];
    }
    return;
}

void solution(){
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> origin[i];
    for (int i = 0; i < N; ++i)
        cin >> partial[i];

    judge();

    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    solution();

    // cin >> N;
    // for (int i = 0; i < N; ++i)
    //     cin >> origin[i];
    // merge_sort_one_turn(origin, N, 1);
    // merge_sort_one_turn(origin, N, 2);
    // for (int i = 0; i < N; ++i)
    //     cout << origin[i] << ' ';
    
    return 0;
}