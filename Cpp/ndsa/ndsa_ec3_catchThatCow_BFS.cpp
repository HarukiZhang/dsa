#include<iostream>
#include<queue>
#include<vector>
using namespace std;
constexpr int kBound = 100'000;

struct Node {
    int loc;
    int step;
    Node(){}
    Node(int l, int s) : loc{l}, step{s} {}
};

queue<Node> myQue;
bool guideP[kBound + 10]{};
int N, K;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    cin >> N >> K;
    Node x{N, 0}, tmp;
    myQue.push(x);
    guideP[N] = true;
    while (!myQue.empty()){
        x = myQue.front();
        if (x.loc == K){
            cout << x.step << endl;
            return 0;
        }
        tmp.loc = x.loc + 1;
        if (tmp.loc <= kBound && !guideP[tmp.loc]){
            myQue.push(Node(tmp.loc, x.step + 1));
            guideP[tmp.loc] = true;
        }
        tmp.loc = x.loc - 1;
        if (tmp.loc >= 0 && !guideP[tmp.loc]){
            myQue.push(Node(tmp.loc, x.step + 1));
            guideP[tmp.loc] = true;
        }
        tmp.loc = x.loc * 2;
        if (tmp.loc <= kBound && !guideP[tmp.loc]){
            myQue.push(Node(tmp.loc, x.step + 1));
            guideP[tmp.loc] = true;
        }
        myQue.pop();
    }
    return 0;
}