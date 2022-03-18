#include <iostream>
using namespace std;

void print02(short n){
    // is this the first digit for a number;
    bool isFir = true;
    if (n == 0){
        cout << "0";
        return;
    }
    for (int i = 15; i >= 0; --i){
        if (n >> i & 1){
            if (isFir)
                isFir = false;
            // after printing the first bi-digit, insert a '+' sign;
            else cout << "+";

            // 0b10 : 2 to the 1;
            if (i == 1) cout << "2";
            // 0b1 : 2 to the 0;
            else if (i == 0) cout << "2(0)";
            else {
                cout << "2(";
                // recursion;
                print02(i);
                cout << ")";
            }
        }
    }
    return;
}

int main() {
    short a;
    cin >> a;
    print02(a);
    cout.flush();
}

/*
73
2(2(2)+2)+2(2+2(0))+2(0)
*/