#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

int getNextPrime(int n){
    int baseN = n;
    while (true){
        bool list[100]{};
        int stp = ceil(sqrt(baseN));
        for (int inc = 2; inc <= stp; ++inc){
            int sta = baseN % inc;
            if (sta != 0) sta = inc - sta;
            for (int i = sta; i + inc < 100; i += inc)
                list[i] = true;
        }
        for (int i = 0; i < 100; ++i)
            if (list[i] == false)
                return baseN + i;
        baseN += 100;
    }
}

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

int getNextPrime_old(int n){
    if ( isPrime(n) ) return n;
    int res;
    for (res = n + 1; !isPrime(res); ++res);
    return res;
}

int main(){

    constexpr int kTest = (1 << 30) + 12128773;
    cout << getNextPrime_old(kTest) << endl;
    cout << getNextPrime(kTest);

    return 0;
}