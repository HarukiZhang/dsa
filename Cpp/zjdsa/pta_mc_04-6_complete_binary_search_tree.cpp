#include<iostream>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

constexpr int kMaxLen = 1024;

struct Node {
    int data, lchild, rchild;
};

Node CBST[kMaxLen];
/*Note: std::size may lead to ambiguous reference;*/
int N, entry = 0, idx_cnt = 0;
int buffer[kMaxLen];

int biuldTree(int buf[], int len);
void traversal_level();

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> buffer[i];
        CBST[i].lchild = CBST[i].rchild = -1;//initialize child ptr;
    }
    /*ascending sorted order == inOrder traversal sequence;*/
    sort(buffer, buffer + N);
    entry = biuldTree(buffer, N);
    traversal_level();
    return 0;
}

int getIdx(int num){
    //how many level of tree is full excluded bottom;
    int cmpltd_level = ceil(log2(num + 1)) - 1;
    //how many nodes within completed level;
    int cmpltd_tree_num = (1 << cmpltd_level) - 1;
    //offset indicates whether lack of node in the left half side of bottom;
    int offset = num - cmpltd_tree_num - (1 << cmpltd_level) / 2;
    //more than 0, suggests not lack nodes;
    if (offset > 0) offset = 0;
    //the num of nodes == index of root;
    return cmpltd_tree_num + offset;
}

int biuldTree(int buf[], int len){
    if (len == 1){//recursion termination clause;
        CBST[idx_cnt].data = buf[0];
        return idx_cnt++;
    }
    int idx = getIdx(len);
    Node &crtN = CBST[idx_cnt];
    int retIdx = idx_cnt++;
    crtN.data = buf[idx];
    crtN.lchild = biuldTree(buf, idx);//idx will be at-least 1;
    int right_len = len - idx - 1;
    //can't let right len be 0, otherwise, getIdx() cannot compute correct idx;
    if (right_len != 0)
        crtN.rchild = biuldTree(buf + idx + 1, right_len);
    return retIdx;
}

void traversal_level(){
    bool fir = true;
    queue<int> que;
    if (entry >= 0)
        que.push(entry);
    while ( !que.empty() ){
        int crt = que.front();
        que.pop();
        if (fir) fir = false;
        else cout << " ";
        cout << CBST[crt].data;
        if ( CBST[crt].lchild >= 0) que.push(CBST[crt].lchild);
        if ( CBST[crt].rchild >= 0) que.push(CBST[crt].rchild);
    }
    return;
}