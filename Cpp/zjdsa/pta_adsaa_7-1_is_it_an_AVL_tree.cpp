#include<iostream>
using namespace std;

constexpr int kMaxLen = 128;

struct Node {
    int key, height, left, right;
};

int K, N;;
Node list[kMaxLen];

int main(){
    ios::sync_with_stdio(false);
    int last, crt, idx, lH, rH, fB, cH;
    bool isleft, flag;
    //initialization;
    for (int i = 0; i < kMaxLen; ++i)
        list[i].parent = list[i].height = list[i].left = list[i].right = -1;
    cin >> K;
    for (int k = 0; k < K; ++k){
        cin >> N;
        //insert as BST;
        for (int i = 0; i < N; ++i){
            cin >> list[i].key;
            if (i == 0) continue;//the first insertion is different;
            last = 0; crt = 0; isleft = true;
            while (crt != -1){
                last = crt;
                if (list[i].key < list[crt].key){
                    crt = list[crt].left;
                    isleft = true;
                }
                else {
                    crt = list[crt].right;
                    isleft = false;
                }
            }
            if (isleft) list[last].left = i;
            else list[last].right = i;
        }
        idx = N; flag = true;
        while (idx--){
            //get height of left and right;
            rH = lH = fB = 0;//if leaf node, height == 0;
            if (list[idx].left != -1) lH = list[list[idx].left].height + 1;
            if (list[idx].right != -1) rH = list[list[idx].right].height + 1;
            cH = lH > rH ? lH : rH;
            if (cH > list[idx].height) list[idx].height = cH;
            fB = lH - rH;
            fB = fB < 0 ? -fB : fB;//get absolute;
            if (fB > 1){
                flag = false;
                break;
            }
        }
        if (flag) cout << "Yes" << endl;
        else cout << "No" << endl;
        //re-initialize;
        for (int i = 0; i < N; ++i)
            list[i].parent = list[i].height = list[i].left = list[i].right = -1;
    }
    return 0;
}