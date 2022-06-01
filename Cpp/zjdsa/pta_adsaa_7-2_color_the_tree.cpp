#include<iostream>
using namespace std;

constexpr int kMaxLen = 64;

struct Node {
    bool red = false;
    int key, left = -1, right = -1;
};

int K, N;
Node list[kMaxLen];

int main(){
    ios::sync_with_stdio(false);
    cin >> K;
    while (K--){
        cin >> N;
        for (int i = 0 ; i < N; ++i){
            cin >> list[i].key;
        }
        for (int i = N - 2; i >= 0; --i){
            int crt = N - 1, last = crt;
            bool isleft = false;
            while (crt != -1){
                last = crt;
                if (list[i].key < list[crt].key){
                    isleft = true;
                    crt = list[crt].left;                    
                }
                else {
                    isleft = false;
                    crt = list[crt].right;
                }
            }
            if (isleft) list[last].left = i;
            else list[last].right = i;
        }
        //how to check validity of RBT?
    }
}