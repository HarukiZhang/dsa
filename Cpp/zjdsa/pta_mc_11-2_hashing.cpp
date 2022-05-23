#include<iostream>
#include<cmath>
using namespace std;

constexpr int kMaxLen = 10010;
int MSize, N;

int list[kMaxLen];

bool testPrime(int n){
    if (n < 2) return false;
    else if (n == 2) return true;
    int stp = ceil(sqrt(n));
    if (!(n & 1)) return false;//if n is even num;
    for (int i = 3; i < stp; i += 2)
        if (n % i == 0) return false;
    return true;
}

void getPrime(int &num){
    if (num <= 2) num = 2;
    else if (num & 1) while (!testPrime(num)) num += 2;
    else for (++num; !testPrime(num); num += 2);
    return;
}

inline int hash_func(int x){
    return x % MSize;
}

int probe(int h, int num){
    int base = 0, stp = MSize >> 1;
    int idx = h;
    while (base <= stp){
        if (list[idx] == -1 || list[idx] == num) return idx;
        ++base;
        idx = h + (base * base);
        idx %= MSize;
    }
    return -1;
}

int insert(int x){
    int hash = hash_func(x);
    int idx = probe(hash, x);
    if (idx != -1) list[idx] = x;
    return idx;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> MSize >> N;
    getPrime(MSize);

    for (int i = 0; i < MSize; ++i)
        list[i] = -1;
    
    int t;
    for (int i = 0; i < N; ++i){
        cin >> t;
        int idx = insert(t);
        if (i) cout << ' ';
        if (idx != -1)
            cout << idx;
        else cout << '-';
    }
    return 0;
}