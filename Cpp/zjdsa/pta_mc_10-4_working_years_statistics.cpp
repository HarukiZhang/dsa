#include<iostream>
using namespace std;

constexpr int kMaxLen = 64;

int N;
int counter[kMaxLen]{};

int main(){
    cin >> N;
    int tmp;
    for (int i = 0; i < N; ++i){
        cin >> tmp;
        ++counter[tmp];
    }
    for (int i = 0; i < kMaxLen; ++i){
        if (counter[i]) cout << i << ':' << counter[i] << endl;
    }
    return 0;
}