#include<iostream>
#include<vector>
#include<queue>
using namespace std;

constexpr int kMaxSize = 1024, kInfty = ~(1<<31);

int tableSize;
int indegrees[kMaxSize]{},
    hashTable[kMaxSize];   //records original data;
vector<int> graph[kMaxSize];//linked-list storage;
struct Elem {
    int data, index;
    bool operator<(const Elem &e) const {
        return data > e.data;
    }
};
priority_queue<Elem> minheap;//sort and print;

void topoSort(){
    Elem tmpE;
    bool fir = true;
    while (!minheap.empty()){
        tmpE = minheap.top();
        minheap.pop();
        for (int edge : graph[tmpE.index]){
            --indegrees[edge];//associative loc indegree decreases;
            if (indegrees[edge] == 0){//
                minheap.push(Elem {hashTable[edge], edge});
            }
        }
        if (fir) fir = false;
        else cout << ' ';
        cout << tmpE.data;
    }
    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);

    cin >> tableSize;
    int shouldBe, offset;
    Elem tmpE;
    for (int i = 0; i < tableSize; ++i){
        cin >> hashTable[i];
        if (hashTable[i] < 0){
            indegrees[i] = kInfty;//just ignore it;
            continue;
        }
        shouldBe = hashTable[i] % tableSize;
        if (shouldBe != i){
            offset = i - shouldBe;
            if (offset < 0) offset += tableSize;
            indegrees[i] = offset;
            for (int j = shouldBe; j != i; j = (j + 1) % tableSize){
                graph[j].push_back(i);
            }
        }
        else {
            // indegrees[i] = 0;
            tmpE.data = hashTable[i];
            tmpE.index = i;
            minheap.push(tmpE);
        }
    }
    topoSort();
    return 0;
}