#include<iostream>
#include<stack>
using namespace std;

constexpr int kMaxLen = 64;

struct Node {
    bool red = true;
    int key, parent = -1, left = -1, right = -1, bheight = 0;
};

int K, N;
Node list[kMaxLen];

bool psudo_fix_up(int idx);
int hcheck(int idx);

int main(){
    freopen("E:\\in.txt", "r", stdin);
    // ios::sync_with_stdio(false);
    cin >> K;
    while (K--){
        cin >> N;
        //input;
        for (int i = 0 ; i < N; ++i){
            cin >> list[i].key;
        }
        //indexing and painting;
        list[N].red = false;//regard the N-th Node as Nil node;
        for (int i = 0; i < N; ++i){
            list[i].parent = list[i].left = list[i].right = N;
            list[i].red = true;            
        }
        list[N - 1].red = false;//paint root to black;
        for (int i = N - 2; i >= 0; --i){
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
            list[i].parent = last;
        }
        stack<int> stk;
        int idx = N - 1;
        bool flag = true;
        while (idx != N || !stk.empty()){
            while (idx != N){
                if (list[idx].right != N)
                    stk.push(list[idx].right);
                if (list[idx].red == true){
                    flag = psudo_fix_up(idx);
                    if (!flag) break;
                }
                idx = list[idx].left;
            }
            if (!flag) break;
            if (!stk.empty()){
                idx = stk.top();
                stk.pop();
            }
        }
        hcheck(N - 1);
        if (flag) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

int hcheck(int idx){
    int bhl = 0, bhr = 0;
    if (list[idx].left != N){
        bhl = hcheck(list[idx].left);
    }
    if (list[idx].right != N){
        bhr = hcheck(list[idx].right);
    }
    if (bhl == bhr){
        if (!list[list[idx].left].red || !list[list[idx].right].red)
            list[idx].bheight = bhl + 1;
        else list[idx].bheight = bhl;
        return list[idx].bheight;
    }
    else {
        return -1;
    }
}

bool psudo_fix_up(int idx){
    //only red node should call this function;
    int p = list[idx].parent, gp = list[p].parent;
    while (list[p].red == true){
        if (p = list[gp].left){
            int uc = list[gp].right;
            if (list[uc].red == true){
                list[gp].red = true;
                list[uc].red = false;
                list[p].red = false;
                idx = gp;
                p = list[idx].parent;
                gp = list[p].parent;
            }
            else return false;
        }
        else {
            int uc = list[gp].left;
            if (list[uc].red == true){
                list[gp].red = true;
                list[uc].red = false;
                list[p].red = false;
                idx = gp;
                p = list[idx].parent;
                gp = list[p].parent;
            }
            else return false;
        }
    }
    list[N - 1].red = false;//force root to be black;
    return true;
}