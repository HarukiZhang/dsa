#include<iostream>
using namespace std;
int main () {
    if (__cplusplus == 201703L) cout << "17";
    else if (__cplusplus == 201402L) cout << "14";
    else if (__cplusplus == 201103L) cout << "11";
    else if (__cplusplus == 199711L) cout << "98";
    else cout << "pre-standard";
    return 0;
}