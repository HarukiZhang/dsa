#include<iostream>

using namespace std;

constexpr int kCharacterType = 128;
constexpr int kTreeLen = kCharacterType * 2;
constexpr int kMinWeight = -1;

struct HfmTNode {
    char data;
    int weight;
    int parent, lchild, rchild;
} huffmanTree[kTreeLen]{}, minHeap[kTreeLen]{};

int heapSize = 0, heapCap = kTreeLen - 1, hfmIdx;

void biuldMinHeap(HfmTNode* minHp, int num);
void biuldMinHeap(HfmTNode* minHp, int* hushT);//biuld heap from hush table;
void percolate(HfmTNode* minHp, int ptr);
bool pop(HfmTNode* minHp, HfmTNode& x);
bool insert(HfmTNode* minHp, HfmTNode x);
void biuldHfmTree(HfmTNode* hfmT, HfmTNode* minHp);
void showHfmCode(HfmTNode* hfmT);
void codeHfm(HfmTNode* hfmT, char* textBuf, char* codeBuf);
void decodeHfm(HfmTNode* hfmT, char* hfmCode);
void showHfmTbl();//print whole static list of Huffman tree;

void statisticText(char* tbuf, int* hushT){
    for (int i = 0; tbuf[i]; ++i)
        ++hushT[(int)tbuf[i]];
    return;
}

char textBuff[1024], codeBuff[1024];
int hushTbl[kCharacterType]{};

int main(){
    freopen("E:\\in.txt", "r", stdin);

    cin.getline(textBuff, 1023);//read original text into textBuff;
    statisticText(textBuff, hushTbl);//get statistic of text and store into hushTbl;
    biuldMinHeap(minHeap, hushTbl);//biuld heap from hush table;
    biuldHfmTree(huffmanTree, minHeap);
    showHfmCode(huffmanTree);//print char, frequency, and huffman code of the char;
    cout << "Coding:" << endl;
    codeHfm(huffmanTree, textBuff, codeBuff);//code whole text into codeBuff;
    cout << codeBuff << endl;
    cout << "Decoding:" << endl;
    decodeHfm(huffmanTree, codeBuff);//according to above-biult huffman tree,
                                     //decode huffman code into character sequence;
    return 0;
}

void biuldMinHeap(HfmTNode* minHp, int* hushT){
    minHp[0].weight = kMinWeight;
    int heapIdx = 1;
    for (int i = 0; i < kCharacterType; ++i){
        if (hushT[i]){
            minHp[heapIdx].data = (char)i;
            minHp[heapIdx].weight = hushT[i];
            ++heapIdx;
        }
    }
    heapSize = --heapIdx;
    for (int p = heapSize / 2; p > 0; --p)
        percolate(minHp, p);
    return;
}

void biuldMinHeap(HfmTNode* minHp, int num){
    /*read in*/
    int t;
    char c;
    minHp[0].weight = kMinWeight;
    for (int i = 1; i <= num; ++i){
        cin >> c >> ws >> t >> ws;
        minHp[i].data = c;
        minHp[i].weight = t;
    }
    heapSize = num;
    for (t = heapSize / 2; t > 0; --t)
        percolate(minHp, t);
    return;
}

void percolate(HfmTNode* minHp, int ptr){
    int parent, child;
    HfmTNode t = minHp[ptr];
    for (parent = ptr; (child = parent * 2) <= heapSize; parent = child){
        if (child != heapSize && minHp[child].weight > minHp[child + 1].weight)
            ++child;
        if (t.weight > minHp[child].weight)
            minHp[parent] = minHp[child];
        else break;
    }
    minHp[parent] = t;
    return;
}

bool pop(HfmTNode* minHp, HfmTNode& x){
    if (heapSize == 0) return false;
    x = minHp[1];
    minHp[1] = minHp[heapSize--];
    percolate(minHp, 1);
    return true;
}

bool insert(HfmTNode* minHp, HfmTNode x){
    if (heapSize == heapCap) return false;
    ++heapSize;
    int ptr;
    for (ptr = heapSize; minHp[ptr / 2].weight > x.weight; ptr /= 2)
        minHp[ptr] = minHp[ptr / 2];
    minHp[ptr] = x;
    return true;
}

void biuldHfmTree(HfmTNode* hfmT, HfmTNode* minHp){
    hfmIdx = 1;
    int lf, rt;
    while (heapSize > 1){
        pop(minHp, hfmT[lf = hfmIdx++]);
        pop(minHp, hfmT[rt = hfmIdx++]);
        HfmTNode t { '\0', hfmT[lf].weight + hfmT[rt].weight, 0, lf, rt };
        insert(minHp, t);
    }
    pop(minHp, hfmT[hfmIdx]);
    /*update parent ptr*/
    hfmT[0].parent = -1;//head node;
    for (int i = hfmIdx; i > 0; --i){
        hfmT[hfmT[i].lchild].parent = i;
        hfmT[hfmT[i].rchild].parent = i;
    }
    return;
}

void showHfmCode(HfmTNode* hfmT){
    char buf[kTreeLen]{};
    int stp = hfmIdx, ptr, idx, ibf;
    cout << "char\tfrequency\tHuffman Code" << endl;
    for (int i = 1; i < stp; ++i){
        if (hfmT[i].data != '\0'){
            cout << hfmT[i].data << "\t" << hfmT[i].weight << "\t";
            idx = i;
            ptr = hfmT[idx].parent;
            ibf = 0;
            do {
                if (hfmT[ptr].lchild == idx)
                    buf[ibf++] = '0';
                else buf[ibf++] = '1';
                idx = ptr;
                ptr = hfmT[idx].parent;
            } while (ptr != 0);
            while (ibf > 0) cout << buf[--ibf];
            cout << "\n" << flush;
        }
    }
    return;
}

void codeHfm(HfmTNode* hfmT, char* textBuf, char* codeBuf){
    int codeBufIdx = 0;
    for (int i = 0; textBuf[i]; ++i){
        char& crtChar = textBuf[i];
        /*find it*/
        int ptr;
        for (ptr = 1; ptr < hfmIdx; ++ptr)
            if (hfmT[ptr].data == crtChar) break;
        /*code*/
        char printBuf[kCharacterType];
        int iBuf = 0;
        int last = ptr;
        int crt = hfmT[last].parent;
        do {
            if (hfmT[crt].lchild == last)
                printBuf[iBuf++] = '0';
            else printBuf[iBuf++] = '1';
            last = crt;
            crt = hfmT[crt].parent;
        } while (crt != 0);
        /*print*/
        while (iBuf > 0){
            codeBuf[codeBufIdx++] = printBuf[--iBuf];
        };
    }
    codeBuf[codeBufIdx] = 0;
    return;
}

void decodeHfm(HfmTNode* hfmT, char* hfmCode){
    int ptr = hfmIdx, idx = 0;
    while (hfmCode[idx]){
        if (hfmCode[idx] == '1'){
            ptr = hfmT[ptr].rchild;
        }
        else {
            ptr = hfmT[ptr].lchild;
        }
        if (hfmT[ptr].data){
            cout << hfmT[ptr].data;
            ptr = hfmIdx;
        }
        ++idx;
    }
    return;
}

void showHfmTbl(){
    cout << "idx\tch\tweig\tparent\tlchild\trchild\n" << flush;
    for (int i = 0; i <= hfmIdx; ++i){
        HfmTNode& cn = huffmanTree[i];
        cout << i << "\t" << cn.data << "\t" << cn.weight << "\t"
            << cn.parent << "\t" << cn.lchild << "\t"
            << cn.rchild << "\n" << flush;
    }
}

/*Test data:
10
a 7
b 4
c 6
d 19
e 27
f 5
g 6
h 6
i 15
j 2

*/

/*
char    frequency       Huffman Code
j       2       01100
b       4       01101
f       5       0100
h       6       0101
c       6       0111
g       6       1100
a       7       1101
i       15      111 
d       19      00  
e       27      10 
*/

/*test decode:
huffman code: 1101011011101011000100011101010010
original: abajfchde

*/

/*test code:
char    frequency       Huffman Code
.       1       10111010
P       1       10111011
z       1       10101000
R       1       10101001
A       1       01001010
T       1       01001011
U       1       10101100
k       1       10101101
-       1       10101010
I       1       10101011
V       1       10101110
p       1       10101111
M       1       0100100
'       2       1011100
b       3       010011
v       3       001100
m       3       001101
y       4       101100
w       4       101101
f       5       101111
h       5       00100
u       5       00101
g       6       00111
l       6       01000
c       7       10000
d       8       10001
t       8       10100
s       12      0101
r       14      0110
a       15      0111
i       15      1001
o       18      1110
n       19      1111
e       19      000
        33      110
Huffman code:
010010101101010100100101010101011001011111111010101001001111100110111111011100100010010011101110110100000010011001111111100011101011111110011000110100001101101110100101000110101001011001000011101110111111010110100100111011010111101000000100011101011111110011011010101011010101100111000010001101111000011101100100010110011010100101101111011010001000100000111100010000101110011100111111011001111011111010000001101100100110001001111100111110101000111011000111000101000001000111001001110110011010101110010000111100011001001101100101101101011101100101101001001111110111000101110001111110001100000011011110011010001111101001100111111111111110001011111100000001000111000100000110101101011101011100110000111111100010111111000010011111001111100010010010101110100001001101001001101010000001111010100100100110101111110010010110010100001011000101111011001101110001100000011011001001001110010110000111010110110111000101110100111110011000111010110011110111111011101011111101010110010101101011001111001111100010111010
Decoding:
A Russian-born oligarch and former oil tycoon who fled for Israel nearly two decades ago after being targeted by Vladimir Putin's government announced he was renouncing his citizenship Tuesday over Moscow's invasion of Ukraine.


Original Text:
A Russian-born oligarch and former oil tycoon who fled for Israel nearly two decades ago after being targeted by Vladimir Putin's government announced he was renouncing his citizenship Tuesday over Moscow's invasion of Ukraine. 

*/