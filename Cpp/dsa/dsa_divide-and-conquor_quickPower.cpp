#include<iostream>
#include<cmath>
using namespace std;

int qPow(int base, int sups){
    if (sups == 0)
        return 1;
    if (sups == 1)
        return base;
    if (sups == 2)
        return base * base;
    int res = qPow(base, sups / 2) /*if even*/
        * qPow(base, sups - sups / 2);//if odd
    return res;
}

int qPow1(int base, int sups){
    if (sups == 0)
        return 1;
    if (sups & 1)//odd num;
        return base * qPow1(base, sups - 1);
    else {// even num;
        int res = qPow1(base, sups / 2);
        return res * res;
    }
}

/*This should be the fastest for no recursive calling*/
int qPow2(int base, int sups){
    int res = 1;
    while (sups){
        if (sups & 1)//if sups is odd;
            res *= base;
        base *= base;
        sups >>= 1;
    }
    return res;
}

int main(){
    cout << qPow2(5, 7) << "\n" << flush;
    cout << qPow2(-3, 7) << "\n" << flush;
    cout << qPow2(-4, 6) << "\n" << flush;
    cout << qPow2(-6, 5) << "\n" << flush;
    cout << qPow2(24, 6) << "\n" << flush;
}