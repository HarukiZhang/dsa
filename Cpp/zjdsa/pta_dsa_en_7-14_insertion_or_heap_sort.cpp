/*
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, 
and growing a sorted output list. Each iteration, insertion sort removes 
one element from the input data, finds the location it belongs within the 
sorted list, and inserts it there. It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region, and it 
iteratively shrinks the unsorted region by extracting the largest element 
and moving that to the sorted region. it involves the use of a heap data 
structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence which 
is a result of several iterations of some sorting method, can you tell which 
sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives 
a positive integer N (≤100). Then in the next line, N integers are given as 
the initial sequence. The last line contains the partially sorted sequence of 
the N numbers. It is assumed that the target sequence is always ascending. All 
the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or "Heap Sort" 
to indicate the method used to obtain the partial result. Then run this method 
for one more iteration and output in the second line the resulting sequence. It 
is guaranteed that the answer is unique for each test case. All the numbers in 
a line must be separated by a space, and there must be no extra space at the end 
of the line.
*/
#include<iostream>
using namespace std;

constexpr int kMaxSize = 128;

int origin[kMaxSize], partial[kMaxSize];
int N;

int test_insertion();//return max ascending sub str length;
void insertion_sort_one_turn(int arr[], int size, int idx);//idx :the 1st unsorted loc;
int get_heap_tail();//the most core algo; ie, to find the last elem within the heap;
void percDown(int arr[], int sta, int stp);//stp: the last elem within heap;
void heap_sort_one_turn(int arr[], int size, int idx);//idx : heap tail;

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> origin[i];
    for (int i = 0; i < N; ++i)
        cin >> partial[i];
    int idx = test_insertion();
    if (idx != -1){
        cout << "Insertion Sort" << endl;
        insertion_sort_one_turn(partial, N, idx);
    }
    else {
        cout << "Heap Sort" << endl;
        idx = get_heap_tail();
        heap_sort_one_turn(partial, N, idx);
    }
    for (int i = 0; i < N; ++i){
        if (i) cout << ' ';
        cout << partial[i];
    }
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
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:
Heap Sort
5 4 3 1 0 2 6 7 8 9
*/

int get_heap_tail(){
    //before using this func, the seq should be assured to be a mid-proc of heap sort;
    //note: heap is a complete BT;
    int idx = 0;
    //firstly, to find the most left sub tree node by checking left children;
    for (; idx < N && partial[(idx << 1) + 1] < partial[idx];//if my left child < me;
        idx = (idx << 1) + 1);//go to my this child;
    //secondly, to find the heap tail by checking siblings;
    for (; idx < N && partial[idx + 1] < partial[idx >> 1];//if my sibling < his parent;
        ++idx);//go to my this sibling;
    return idx;
}

void heap_sort_one_turn(int arr[], int size, int idx){
    swap(arr[idx], arr[0]);//put the max elem to the one left loc of sorted-region;
    percDown(arr, 0, idx - 1);//the scale of the heap decreases;
    return;
}

//just ordinary percolating down;
void percDown(int arr[], int sta, int stp){
    int parent = sta, child;
    int tmp = arr[sta];
    for (; (child = (parent << 1) + 1) <= stp; parent = child){
        if (child != stp && arr[child + 1] > arr[child])
            ++child;
        if (arr[child] > tmp)
            arr[parent] = arr[child];
        else break;
    }
    arr[parent] = tmp;
    return;
}

int test_insertion(){
    int idx = 0, maxAscdLen = 1;
    for (; idx < N && partial[idx] <= partial[idx + 1]; ++idx) ++maxAscdLen;
    for (++idx; idx < N && partial[idx] == origin[idx]; ++idx);
    if (idx == N) return maxAscdLen;
    else return -1;
}

void insertion_sort_one_turn(int arr[], int size, int idx){
    int tmp = arr[idx];
    for (; idx > 0 && arr[idx - 1] > tmp; --idx)
        arr[idx] = arr[idx - 1];
    arr[idx] = tmp;
    return;
}