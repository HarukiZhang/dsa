/*
将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。

输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。
下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M个下标。

输出格式:
对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字间以1个空格分隔，
行末不得有多余空格。

输入样例:
5 3
46 23 26 24 10
5 4 3
输出样例:
24 23 10
46 23 10
26 10
*/
#include<iostream>
#include<vector>
using namespace std;

constexpr int kMaxLen = 1024, kInfty = -10001;

class MinHeap {
public:
    MinHeap(){
        list[0] = kInfty;
    }
    void insert(int x){
        int ptr = ++size;
        for (; list[ptr / 2] > x; ptr /= 2)
            list[ptr] = list[ptr / 2];
        list[ptr] = x;
        return;
    }
    void printPath(int ptr){
        bool fir = true;
        for (int i = ptr; i > 0; i /= 2){
            if (fir) fir = false;
            else cout << " ";
            cout << list[i];
        }
        cout << endl;
        return;
    }
private:
    int size = 0, capacity;
    int list[kMaxLen];
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    MinHeap minheap;
    int intmp;
    for (int i = 0; i < N; ++i){
        cin >> intmp;
        minheap.insert(intmp);
    }
    for (int i = 0; i < M; ++i){
        cin >> intmp;
        minheap.printPath(intmp);
    }
    return 0;
}