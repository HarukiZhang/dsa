#include<iostream>
#include<vector>
using namespace std;


constexpr int kN1 = 10, kN2 = 5;

int main(){

int a = 3, b = 5;
decltype(a) c = a;
decltype((b)) d = a;
++c;
++d;

cout << a << endl
    << b << endl
    << c << endl
    << d << endl;

}