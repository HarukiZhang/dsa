/*
The task of this problem is simple: insert a sequence of distinct positive integers 
into a hash table, and output the positions of the input numbers. The hash function 
is defined to be H(key)=key%TSize where TSize is the maximum size of the hash table. 
Quadratic probing (with positive increments only) is used to solve the collisions.

Note that the table size is better to be prime. If the maximum size given by the user 
is not prime, you must re-define the table size to be the smallest prime number which 
is larger than the size given by the user.

Input Specification:
Each input file contains one test case. For each case, the first line contains two 
positive numbers: MSize (≤10 
4
 ) and N (≤MSize) which are the user-defined table size and the number of input 
 numbers, respectively. Then N distinct positive integers are given in the next 
 line. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print the corresponding positions (index starts from 0) of the 
input numbers in one line. All the numbers in a line are separated by a space, and 
there must be no extra space at the end of the line. In case it is impossible to 
insert the number, print "-" instead.

Sample Input:
4 4
10 6 4 15
Sample Output:
0 1 4 -
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
using namespace std;

constexpr int kMaxSize = 10010;

int size_input, input_num, tblSize;
int hashTbl[kMaxSize];

bool isPrime(int n){
    if (n < 2) return false;//1
    else if (n < 4) return true;//2 and 3;
    else {
        int stp = ceil(sqrt(n));
        for (int i = 2; i <= stp; ++i)
            if (n % i == 0)
                return false;
        return true;
    }
}

int getNextPrime(int n){
    if ( isPrime(n) ) return n;
    int res;
    for (res = n + 1; !isPrime(res); ++res);
    return res;
}

int hashFunc(int x){
    return x % tblSize;
}
int probe_quadratic(int idx){
    int i = 1, tmpidx, stp = tblSize / 2;
    while (true){
        tmpidx = (idx + i * i) % tblSize;
        if (hashTbl[tmpidx] == -1) break;
        ++i;
        if (i > stp) return -1;
    }
    return tmpidx;
}

int insert(int x){
    int idx = hashFunc(x);
    if (hashTbl[idx] != -1)
        idx = probe_quadratic(idx);
    if (idx != -1)
        hashTbl[idx] = x;
    return idx;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);

    cin >> size_input >> input_num;
    tblSize = getNextPrime(size_input);
    memset(hashTbl, -1, sizeof(int) * tblSize);
    int intmp;
    bool fir = true;
    for (int i = 0; i < input_num; ++i){
        cin >> intmp;
        intmp = insert(intmp);
        if (fir) fir = false;
        else cout << " ";
        if (intmp != -1) cout << intmp;
        else cout << "-";
    }
    return 0;
}