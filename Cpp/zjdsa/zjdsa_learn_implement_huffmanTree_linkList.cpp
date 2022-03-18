/*For now, this implementation of Huffman Tree can not code and decode Huffamn code;
For one reason, the HfmTNode do not have parent ptr, so that it is difficult to 
traverse at ease;*/
#include<iostream>

using namespace std;

struct HfmTNode {    
    int weight;
    char data;
    bool isLeaf;
    HfmTNode* left;
    HfmTNode* right;
    HfmTNode() = default;
    HfmTNode(char d, int w, bool l)
        : weight(w), data(d), isLeaf(l), left(nullptr), right(nullptr) {}
};

class MinHeap {
public:
    MinHeap(){}
    MinHeap(HfmTNode* pArr[], int num){
        size = num;
        arr = new HfmTNode* [size + 2];
        capacity = size + 1;
        arr[0] = new HfmTNode {0, -1, 0};// lookout;
        for (int i = 1; i <= size; ++i)
            arr[i] = pArr[i - 1];
        for (int i = size / 2; i > 0; --i)
            percolate(i);
    }
    ~MinHeap(){
        delete[] arr;
    }
    bool empty(){ return size == 0; }
    int getSize(){ return size; }
    HfmTNode* pop(){
        HfmTNode* tmp = arr[1];
        arr[1] = arr[size--];
        percolate(1);
        return tmp;
    }
    bool insert(HfmTNode* node){
        if (size == capacity) return false;
        ++size;
        int i;
        for (i = size; arr[i / 2]->weight > node->weight; i /= 2)
            arr[i] = arr[i / 2];
        arr[i] = node;
        return true;
    }
private:
    void percolate(int ptr){
        int parent, child;
        HfmTNode* tmp = arr[ptr];
        parent = ptr;
        for (; (child = parent * 2) <= size; parent = child){
            if (child != size && arr[child]->weight > arr[child + 1]->weight)
                ++child;
            if (tmp->weight > arr[child]->weight)
                arr[parent] = arr[child];
            else break;
        }
        arr[parent] = tmp;
        return;
    }
private:
    HfmTNode** arr;
    int size, capacity;
};

class HfmTree {
public:
    HfmTree() : root(new HfmTNode){}
    HfmTree(HfmTNode* pArr[], int num){
        HfmTNode* tmp;
        MinHeap minHeap {pArr, num};
        int stp = minHeap.getSize();
        for (int i = 1; i < stp; ++i){//do minHeap.size - 1 times;
            tmp = new HfmTNode;
            tmp->left = minHeap.pop();
            tmp->right = minHeap.pop();
            tmp->isLeaf = false;
            tmp->weight = tmp->left->weight + tmp->right->weight;
            minHeap.insert(tmp);
        }
        root = minHeap.pop();
    }
    ~HfmTree(){
        delete root;
    }
private:
    HfmTNode* root;
};


int main(){
    freopen("E:\\in.txt", "r", stdin);
    int N, t;
    char ch;
    HfmTNode* ptrArr[12];
    HfmTNode* tmp;
    cin >> N >> ws;
    for (int i = 0; i < N; ++i){
        cin >> ch >> ws >> t >> ws;
        *(ptrArr + i) = new HfmTNode {ch, t, true};
    }
    HfmTree huffmanTree {ptrArr, N};
    for (int i = 0; i < N; ++i)
        delete *(ptrArr + i);
}