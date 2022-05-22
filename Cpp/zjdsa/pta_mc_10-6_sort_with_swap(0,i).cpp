/*
Given any permutation of the numbers {0, 1, 2,..., N−1}, it is easy to sort them 
in increasing order. But what if Swap(0, *) is the ONLY operation that is allowed 
to use? For example, to sort {4, 0, 2, 1, 3} we may apply the swap operations in 
the following way:

Swap(0, 1) => {4, 1, 2, 0, 3}
Swap(0, 3) => {4, 1, 2, 3, 0}
Swap(0, 4) => {0, 1, 2, 3, 4}
Now you are asked to find the minimum number of swaps need to sort the given 
permutation of the first N nonnegative integers.

Input Specification:
Each input file contains one test case, which gives a positive N (≤10^5) 
followed by a permutation sequence of {0, 1, ..., N−1}. All the numbers in a 
line are separated by a space.

Output Specification:
For each case, simply print in a line the minimum number of swaps need to sort the 
given permutation.

Sample Input:
10
3 5 7 2 6 4 9 0 8 1
Sample Output:
9
*/
#include<iostream>
using namespace std;

constexpr int kMaxLen = 100010;

int N;
int list[kMaxLen];
bool visited[kMaxLen];

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> N;
    if (N == 1) {
        //when N == 1, the formula used below is false;
        //N == 1, only one number who is 0, need not any swap;
        cout << 0;
        return 0;
    }
    //read in and count single unit num;
    //single unit num, ie, those who are already in its right place;
    int single_n = 0;
    for (int i = 0; i < N; ++i){
        cin >> list[i];
        if (list[i] == i) {
            ++single_n;
            visited[i] = true;
        }
    }
    //check whether the fisrt elem is 0, which means initially, 0 is out of any ring;
    //that is 0 is a single unit, so for any ring, we need to firstly swap 0 into it;
    bool flag = false;
    if (list[0] == 0){
        flag = true;
    }
    int ring_n = 0;//ring num, the number of rings;
    int j, t;
    for (int i = 0; i < N; ++i){
        if (visited[i] == false){
            if (list[i] != i){
                j = i;
                while (j != list[j]){
                    t = list[j];
                    visited[j] = true;
                    list[j] = j;
                    j = t;
                }
                ++ring_n;
            }
        }
    }
    //There are N elems; only those who are not in it right place need to be swapped;
    //If n elems in a ring, n - 1 swaps are needed for replace them all into right place;
    //For those rings that do not contain 0 in it, the first step is to swap 0 in it,
    //    and thus the number of elem in the ring will increase by 1;
    //    so, for those rings do not contain 0 in it, actually need 2 more swaps 
    //    to finish the work;
    int res = N - single_n - ring_n;
    if (flag)
        res += ring_n << 1;
    else res += (ring_n - 1) << 1;
    cout << res;
    return 0;
}