#include<iostream>
using namespace std;

constexpr int kMaxLen = 64;

struct Node {
    bool red = true;
    int key, left = -1, right = -1, maxh = 0, minh = 0;
};

int K, N;
Node list[kMaxLen];

void get_index();
void height_check(int idx, bool &h_flag);

int main(){
    freopen("E:\\in.txt", "r", stdin);
    // ios::sync_with_stdio(false);
    cin >> K;
    while (K--){
        cin >> N;
        bool flag = true;
        if (N == 0) flag = false;
        else {
            //input;
            for (int i = 0 ; i < N; ++i) cin >> list[i].key;
            get_index();
            if (N - 1 >= 0) height_check(N - 1, flag);
        }
        if (flag) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

void height_check(int idx, bool &h_flag){
    //core logic: for any node, among its simple routes to leaf,
    //the longest route is at-most twice the length of the shortest one;
    //this property is assured by RB-property 4 and 5;
    //ie, 4) no repeated red node to be adjacent;
    //and 5) for any node, all its simple routes towards leaf have same black height;
    if (list[idx].left != N)
        height_check(list[idx].left, h_flag);
    if (list[idx].right != N)
        height_check(list[idx].right, h_flag);

    int max = list[list[idx].left].maxh;
    if (list[list[idx].right].maxh > max)
        max = list[list[idx].right].maxh;
    int min = list[list[idx].left].minh;
    if (list[list[idx].right].minh < min)
        min = list[list[idx].right].minh;

    list[idx].maxh = ++max;
    list[idx].minh = ++min;
    
    if (max > 2 * min) h_flag = false;
    return;
}

void get_index(){
    //initialization;
    for (int i = 0; i <= N; ++i){
        list[i].left = list[i].right = N;
        list[i].red = true;
        list[i].maxh = list[i].minh = 0;
    }
    //indexing;
    list[N].red = false;//regard the N-th Node as Nil node;
    list[N - 1].red = false;//paint root to black;
    for (int i = N - 2; i >= 0; --i){//N - 2 : the first node under root;
        int crt = N - 1, last = crt;
        bool isleft = false;
        while (crt != N){
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
    return;
}