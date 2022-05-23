#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<bitset>
using namespace std;

int modular_exponentiation(int a, int b, int n){
    int c = 0;
    int d = 1;
    int bk;
    for (int i = 31; i >= 0; --i){
        c <<= 1;
        d = (d * d) % n;
        bk = b >> i & 1;
        if (bk == 1){
            ++c;
            d = (d * a) % n;
        }
    }
    return d;
}

bool test_prime_me(int n){
    return modular_exponentiation(2, n - 1, n) == 1;
}

int get_prime_me(int num){
    if (num <= 2)
        num = 2;
    else if (num & 1)
        while (!test_prime_me(num)) num += 2;
    else
        for (++num; !test_prime_me(num); num += 2);
    return num;
}

bool testPrime(int n){
    if (n < 2) return false;
    else if (n == 2) return true;
    int stp = ceil(sqrt(n));
    if (!(n & 1)) return false;
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

int main(){
    int t;
    while (cin >> t){
        cout << get_prime_me(t) << ' ';
        getPrime(t);
        cout << t << endl;
    }
    return 0;
}