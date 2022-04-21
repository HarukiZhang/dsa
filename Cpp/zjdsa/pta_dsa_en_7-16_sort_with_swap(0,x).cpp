/*
Given any permutation of the numbers {0, 1, 2,..., N−1}, it is easy to sort 
them in increasing order. But what if Swap(0, *) is the ONLY operation that 
is allowed to use? For example, to sort {4, 0, 2, 1, 3} we may apply the swap 
operations in the following way:

Swap(0, 1) => {4, 1, 2, 0, 3}
Swap(0, 3) => {4, 1, 2, 3, 0}
Swap(0, 4) => {0, 1, 2, 3, 4}
Now you are asked to find the minimum number of swaps need to sort the given 
permutation of the first N nonnegative integers.

Input Specification:
Each input file contains one test case, which gives a positive N (≤10 
5
 ) followed by a permutation sequence of {0, 1, ..., N−1}. All the numbers in 
 a line are separated by a space.

Output Specification:
For each case, simply print in a line the minimum number of swaps need to sort 
the given permutation.
*/
#include<iostream>
using namespace std;

constexpr int kMaxSize = 100010;

int N;
int origin[kMaxSize];

int loop_swap(int idx){
    int t, cnt = 0, 
        init = origin[idx], //record the value in the initial position;
        i = origin[idx];  //set pointer;
    bool flag = false;//whether crt loop contains 0 in it;
    do {
        if (origin[i] == 0)//look out whether crt loop contains 0;
            flag = true;
        t = origin[i];
        origin[i] = i;
        i = t;
        ++cnt;
    } while (i != init);
    //cnt == the num of elememts;
    if (flag) cnt -= 1;//if 0-loop, at-least n - 1 swaps;
    else cnt += 1;
    //firstly, need to swap 0 into the loop;
    //then, the elem num of the loop increases 1;
    //so, it needs n + 1 - 1 swaps;
    //finally, add on the initial swap that moves 0 into the loop;
    //totally, n + 1 swaps;
    return cnt;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> N;
    int nTime = 0;
    for (int i = 0; i < N; ++i)
        cin >> origin[i];
    for (int i = 0; i < N; ++i){
        if (origin[i] != i){
            nTime += loop_swap(i);
        }
    }
    cout << nTime;
    return 0;
}

/*
Sample Input:
10
3 5 7 2 6 4 9 0 8 1
Sample Output:
9
*/