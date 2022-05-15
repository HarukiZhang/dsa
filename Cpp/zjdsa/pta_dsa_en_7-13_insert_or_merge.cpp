/*
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, 
and growing a sorted output list. Each iteration, insertion sort removes 
one element from the input data, finds the location it belongs within the 
sorted list, and inserts it there. It repeats until no input elements remain.

Merge sort works as follows: Divide the unsorted list into N sublists, each 
containing 1 element (a list of 1 element is considered sorted). Then 
repeatedly merge two adjacent sublists to produce new sorted sublists until 
there is only 1 sublist remaining.

Now given the initial sequence of integers, together with a sequence which 
is a result of several iterations of some sorting method, can you tell which 
sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives 
a positive integer N (≤100). Then in the next line, N integers are given as 
the initial sequence. The last line contains the partially sorted sequence 
of the N numbers. It is assumed that the target sequence is always ascending. 
All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or 
"Merge Sort" to indicate the method used to obtain the partial result. 
Then run this method for one more iteration and output in the second line 
the resuling sequence. It is guaranteed that the answer is unique for each 
test case. All the numbers in a line must be separated by a space, and there 
must be no extra space at the end of the line.
*/
#include<iostream>
#include<vector>
using namespace std;

constexpr int kMaxSize = 128;

int N;
int origin[kMaxSize], partial[kMaxSize];

void insertion_sort(int arr[], int size);
void insertion_sort_one_turn(int arr[], int size, int idx);
void merge(int arr[], int size, int iRt, int tmpArr[]);
void merge_sort_recur(int arr[], int size, int tmpArr[]);
void merge_sort(int arr[], int size);
void merge_sort_nonrec(int arr[], int size, int intvl);
void merge_sort_one_turn(int arr[], int size, int intvl);
int getMaxIntvl();
bool judge_insertion(int &idx);
void solution();

int main(){
    freopen("E:\\in.txt", "r", stdin);
    solution();

    //debug:
    // cin >> N;
    // for (int i = 0; i < N; ++i)
    //     cin >> origin[i];
    // merge_sort_one_turn(origin, N, 1);
    // merge_sort_one_turn(origin, N, 2);
    // for (int i = 0; i < N; ++i)
    //     cout << origin[i] << ' ';
    
    return 0;
}

/*
Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
Sample Output 2:
Merge Sort
1 2 3 8 4 5 7 9 0 6
*/

void solution(){
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> origin[i];
    for (int i = 0; i < N; ++i)
        cin >> partial[i];

    int idx;
    if (judge_insertion(idx)){
        cout << "Insertion Sort" << endl;
        insertion_sort_one_turn(partial, N, idx);
    }
    else {
        int intvl = getMaxIntvl();
        cout << "Merge Sort" << endl;
        merge_sort_one_turn(partial, N, intvl);
    }
    for (int i = 0; i < N; ++i){
        if (i) cout << ' ';
        cout << partial[i];
    }
    return;
}

bool judge_insertion(int &idx){
    idx = 1;
    //count max asceding substr length;
    int i;
    for (i = 0; i < N - 1 && partial[i] <= partial[i + 1]; ++i) ++idx;
    //compare post-n-nums whether intact;
    for (++i; i < N && partial[i] == origin[i]; ++i);
    return i == N;
    return;
}

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

void merge_sort_nonrec(int arr[], int size){
    int *tmpArr = new int [size];
    int intvl = 2;
    while (intvl < size){
        int i;
        for (i = 0; i + intvl < size; i += intvl)
            merge(arr + i, intvl, intvl >> 1, tmpArr);
        if (i + (intvl >> 1) < size)
            merge(arr + i, size - i, intvl >> 1, tmpArr);
        intvl <<= 1;//intvl *= 2;
    }
    merge(arr, size, intvl >> 1, tmpArr);
    delete[] tmpArr;
    return;
}

void merge_sort_one_turn(int arr[], int size, int intvl){
    int *tmpArr = new int[size];
    intvl <<= 1;
    int i;
    for (i = 0; i + intvl <= size; i += intvl)
        merge(arr + i, intvl, intvl >> 1, tmpArr);
    //no matter how many item left, have to use at-least (intvl/2) as left sub str;
    if (i + (intvl >> 1) < size)
        merge(arr + i, size - i, intvl >> 1, tmpArr);
    //else : if less than (intvl/2) item left, just keep the crt order;
    delete[] tmpArr;
    return;
}

int getMaxIntvl(){
    //before using this func, 
    //the seq has to be assured that it is the mid-proc of merge sort;
    int intvl = 2;//so the interval is at-least 2;
    //assume that the seq is proceeded at-least one turn, 
    //so the initial intvl is 2;
    //and the first is to test the interval of 4;
    for (; intvl <= N; intvl <<= 1){
        int next_itvl = intvl << 1;
        for (int i = 0; i + intvl < N; i += next_itvl){
            //only need to test the order between two sub-interval;
            if (partial[i + intvl - 1] > partial[i + intvl])
                return intvl;
        }
    }
    return intvl >> 1;
}