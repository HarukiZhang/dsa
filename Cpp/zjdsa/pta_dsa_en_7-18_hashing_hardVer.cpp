/*
Given a hash table of size N, we can define a hash function H(x)=x%N. 
Suppose that the linear probing is used to solve collisions, 
we can easily obtain the status of the hash table with a given sequence 
of input numbers.

However, now you are asked to solve the reversed problem: reconstruct the 
input sequence from the given status of the hash table. Whenever there are 
multiple choices, the smallest number is always taken.

Input Specification:
Each input file contains one test case. For each test case, the first line 
contains a positive integer N (≤1000), which is the size of the hash table. 
The next line contains N integers, separated by a space. A negative integer 
represents an empty cell in the hash table. It is guaranteed that all the 
non-negative integers are distinct in the table.

Output Specification:
For each test case, print a line that contains the input sequence, with the 
numbers separated by a space. Notice that there must be no extra space at the 
end of each line.

Sample Input:
11
33 1 13 12 34 38 27 22 32 -1 21
Sample Output:
1 13 12 21 33 34 38 27 22 32
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

constexpr int kMaxSize = 1024;
int tableSize;
struct Elem {
    int index, data, shouldBe;
    bool operator<(const Elem &e) const {
        return data > e.data;//min heap;
    }
};

bool inserted[kMaxSize]{};//by order of hashTable;
priority_queue<Elem> minHeap;
queue<Elem> que;//for temporary storing invalid elem;

//complexity : O(N); N = tableSize;
bool checkAvail(Elem &elem){
    //backward check whether all clear between index and shouldBe;
    int idx = elem.shouldBe, stp = elem.index;
    while (idx != stp){
        if (inserted[idx] == false){
            elem.shouldBe = idx;//next time only need to check from crt blocking cell;
            return false;
        }
        idx = (idx + 1) % tableSize;//increment;
    }
    return true;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);

    cin >> tableSize;
    Elem tmpE;
    for (int i = 0; i < tableSize; ++i){
        tmpE.index = i;
        cin >> tmpE.data;
        if (tmpE.data < 0){//regard empty cell as a clear loc;
            inserted[i] = true;
            continue;
        }
        tmpE.shouldBe = tmpE.data % tableSize;
        minHeap.push(tmpE);//O(logN);
    }

    bool fir = true;
    while (!minHeap.empty()){
        while (!minHeap.empty()){
            tmpE = minHeap.top();
            minHeap.pop();
            //if an elem is just at its right place, output it;
            if (tmpE.index == tmpE.shouldBe) break;
            else if (checkAvail(tmpE)) break;//if all blocked elem is cleared;
            //else : all temporarily-invalid elem are pushed into a queue;
            que.push(tmpE);
        }
        if (fir) fir = false;
        else cout << ' ';
        cout << tmpE.data;
        inserted[tmpE.index] = true;//regard as cleared;
        //push back into min heap for next loop checking;
        while (!que.empty()){
            tmpE = que.front();
            que.pop();
            minHeap.push(tmpE);//O(logN);
        }
    }
    return 0;
}