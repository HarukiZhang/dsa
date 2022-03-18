/*Logic:
    Referring to code sequence, ie, zero-one-string, we can learn that the relative
    location of a node to its huffman tree root;
    According to the defination of huffman tree, however, no char node should be a
    non-leaf node (branch node whose degree is 2 rather than 0);
    And if a code sequence itself whole constitutes the prefix of other code, this
    set of codes is an invalid Huffman code;

    But above mentioned logic only can be a exclusion rule to rule out who is not 
    Huffamn code, but is not sufficient to judge which one is correct Huffman code;

    The problem is now on : how to compute optimal code length according to given char
    frequency;
        Try: mimic construction of a huffman tree, that is to compute WPL value;
            For even thought there are isomorphic construction of Huffman tree, those
            that have same nodes' weights would have same WPL value;
        The sum of weight of each non-leaf nodes  == WPL;
            For branch nodes contain not only weight info of leaf node, but also
            info of path length; just regard each tree as an scaffold;

    Or maybe, the optimal length should not be considered;
    Only need to judge whether prefix is overlapped;
*/
#include<cstdio>
using namespace std;

typedef unsigned long long ULL;
constexpr int kTreeLen = 128;
constexpr int kHashLen = 128;

struct HpNode {
    bool isLeaf;
    int freq;
};

class MinHeap {
public:
    MinHeap(HpNode* arr)
        : size(0), cap(kTreeLen), data(arr)
    {
        data[0].freq = -1;
    }
    ~MinHeap(){}
    bool empty(){
        return size == 0;
    }
    bool insert(HpNode x){
        if (size == cap) return false;
        int p = ++size;
        for (; data[p / 2].freq > x.freq; p /= 2)
            data[p] = data[p / 2];
        data[p] = x;
        return true;
    }
    HpNode pop(){
        HpNode t = data[1];
        data[1] = data[size--];
        percolate(1);
        return t;
    }
    void percolate(int p){
        int parent, child;
        HpNode t = data[p];
        for (parent = p; (child = parent * 2) <= size; parent = child){
            if (child != size && data[child].freq > data[child + 1].freq)
                ++child;
            if (t.freq > data[child].freq) data[parent] = data[child];
            else break;
        }
        data[parent] = t;
        return;
    }
    int getSize(){
        return size;
    }
    void clear(){
        size = 0;
        return;
    }
private:
    int size;
    int cap;
    HpNode* data;
};

struct HfmTNode {
    bool isLeaf;
    ULL ptrH;
    int lchild, rchild;
};

class HfmT_BST {
public:
    HfmT_BST(HfmTNode* lst)
        : size(0), cap(kTreeLen), list(lst)
    {}
    ~HfmT_BST(){}
    bool empty(){ return size == 0; }
    bool insert(HfmTNode x){
        if (size == cap) return false;
        if (list[1].ptrH == 0){//ptrH >= 1;
            list[++size] = x;
            return true;
        }
        bool isLChild;
        int last = 1, crt = 1;
        while (crt != 0){
            if (x.ptrH < list[crt].ptrH){
                last = crt;
                crt = list[crt].lchild;
                isLChild = true;
            }
            else {//greater_equal
                last = crt;
                crt = list[crt].rchild;
                isLChild = false;
            }
        }
        list[++size] = x;
        if (isLChild) list[last].lchild = size;
        else list[last].rchild = size;
        return true;
    }
    int find(ULL tar){
        if (size == 0) return -1;
        int ptr = 1;
        while (ptr != 0){
            if (tar < list[ptr].ptrH) ptr = list[ptr].lchild;
            else if (tar > list[ptr].ptrH) ptr = list[ptr].rchild;
            else {//ptr found;
                if (list[ptr].isLeaf) return 1;// leaf node;
                else return 0;//path node;
            }
        }
        return -1;//ptr not found;
    }
private:
    int size;
    int cap;
    HfmTNode* list;
};

/*loop search is also not so bad, cause data amount is not so big (not bigger than 128)
So, even if using BST to search, time comsumption did not decrease so well;*/

/*Find func used for loop search;
    ptr not found return -1;
    ptr found but is a path node return 0;
    ptr fount and is leaf return 1;*/
int findNode(HfmTNode* hfmT, int tLen, ULL ptr){
    for (int i = 0; i < tLen; ++i){
        if (hfmT[i].ptrH == ptr){
            if (hfmT[i].isLeaf){
                return 1;
            }
            else return 0;
        }
    }
    return -1;
}

int hashTbl[kHashLen]{};
HpNode heapArr[kTreeLen + 2]{};

int compute_WPL(int nodeNum){
    int t;
    char ch;
    MinHeap mHeap {heapArr};
    for (int i = 0; i < nodeNum; ++i){
        scanf("%c %d ", &ch, &t);
        hashTbl[(int)ch] = t;
        mHeap.insert(HpNode {true, t});//set to leaf-node;
    }
    /*compute WPL, which is the optimal path length;*/
    int resWPL = 0;
    while (mHeap.getSize() > 1){
        HpNode tmp = mHeap.pop();
        int crtSum = tmp.freq;
        if (!tmp.isLeaf) resWPL += tmp.freq;
        tmp = mHeap.pop();
        crtSum += tmp.freq;
        if (!tmp.isLeaf) resWPL += tmp.freq;
        mHeap.insert(HpNode {false, crtSum});//concatenated node is not leaf-node;
    }
    resWPL += mHeap.pop().freq;//final root node of total minHeap;
    return resWPL;
}

void judge_correctness(int nodeNum, int stdWPL){
    int csN;
    char ch, buf[kTreeLen];
    scanf("%d ", &csN);
    for (int k = 0; k < csN; ++k){
        /*for each student's submission*/
        int crtWPL = 0;
        /*use static linkList with struct node to denote a huffman tree;*/
        HfmTNode hfmTList[kTreeLen + 2]{};
        HfmT_BST hfmTree{hfmTList};
        bool flag = true;//flag == false for submission is wrong;
        for (int i = 0; i < nodeNum; ++i){
            scanf("%c %s ", &ch, &buf);
            if (!flag) continue;
            int codeLen = 0;
            ULL ptr = 1ULL;
            while (buf[codeLen]){
                ptr = ptr << 1;
                if (buf[codeLen] == '1')
                    ++ptr;//1 for rchild;
                /*if any other char node in the path, 
                    overlapped prefix exists;*/
                int fSign = hfmTree.find(ptr);
                if (fSign == 1){//ptr found and is leaf;
                    flag = false;
                    break;
                }
                else if (fSign == -1){//ptr not found;
                    if (buf[codeLen + 1])//avoid to mistakely set self as path node;
                        hfmTree.insert(HfmTNode{false, ptr, 0, 0});
                }
                //if ptr found but is path node, do nothing;
                ++codeLen;
            }
            /*check whether ptr of crt leaf node is on the path node;*/
            if (hfmTree.find(ptr) != -1){
                //as long as ptr is found, no matter leaf or path;
                flag = false;
            }
            else //no ptr is found;
                hfmTree.insert(HfmTNode{true, ptr, 0, 0});//register a leaf node;
            crtWPL += codeLen * hashTbl[(int)ch];
            if (crtWPL > stdWPL) flag = false;
        }
        if (flag) printf("Yes\n");
        else printf("No\n");
    }
    return;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);
    int N;
    scanf("%d ", &N);
    int stdWPL = compute_WPL(N);
    judge_correctness(stdWPL);
    return 0;
}

/*Test data:
7
A 1 B 1 C 1 D 3 E 3 F 6 G 6
4
A 00000
B 00001
C 0001
D 001
E 01
F 10
G 11
A 01010
B 01011
C 0100
D 011
E 10
F 11
G 00
A 000
B 001
C 010
D 011
E 100
F 101
G 110
A 00000
B 00001
C 0001
D 001
E 00
F 10
G 11

*/