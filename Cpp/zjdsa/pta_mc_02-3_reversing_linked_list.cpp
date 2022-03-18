/*Reversing linked list
Given a constant K and a singly linked list L, you are supposed to reverse the links 
of every K elements on L. For example, given L being 1→2→3→4→5→6, if K=3, then you 
must output 3→2→1→6→5→4; if K=4, you must output 4→3→2→1→5→6.

Input Specification:
Each input file contains one test case. For each case, the first line contains the 
address of the first node, a positive N (≤10^5) which is the total number of nodes, 
and a positive K (≤N) which is the length of the sublist to be reversed.
The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next

where Address is the position of the node, Data is an integer, and Next is the 
position of the next node.

Output Specification:
For each case, output the resulting ordered linked list. Each node occupies a line, 
and is printed in the same format as in the input.

Sample Input:
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
*/
#include<cstdio>

using namespace std;

constexpr int kMaxListLen = 100010;

struct Node {
    int Data, Next;
};

Node list[kMaxListLen]{};

int evalNum(char* buf){
    if (buf[0] == '-') return -1;
    int res = 0;
    int stp = 0;
    while(buf[stp] == '0') ++stp;
    int unit = 1;
    for (int i = 4; i >= stp; --i){
        res += unit * (int)(buf[i] - '0');
        unit *= 10;
    }
    return res;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    for (int i = 0; i < kMaxListLen; ++i)
        list[i].Next = -1;

    char addrIn[6], nextIn[6];
    int N, K;
    scanf("%s %d %d ", addrIn, &N, &K);
    int firstAddr = evalNum(addrIn);
    int dataIn, addr;
    for (int i = 0; i < N; ++i){
        scanf("%s %d %s ", addrIn, &dataIn, nextIn);
        addr = evalNum(addrIn);
        list[addr].Data = dataIn;
        list[addr].Next = evalNum(nextIn);
    }
    int actLen = 0;
    for (int i = firstAddr; i != -1; i = list[i].Next)
        ++actLen;

    int pRvd, pOld, pNxt;

    pRvd = firstAddr;
    pOld = list[pRvd].Next;
    pNxt = list[pOld].Next;
    for (int k = 1; k < K; ++k){
        list[pOld].Next = pRvd;
        pRvd = pOld;
        pOld = pNxt;
        if (pNxt != -1) pNxt = list[pNxt].Next;
    }
    list[firstAddr].Next = pOld;
    int lastRear = firstAddr;
    firstAddr = pRvd;
    for (int i = K; actLen - i >= K ; i += K){
        pRvd = pOld;
        pOld = pNxt;
        pNxt = list[pNxt].Next;
        int tmpFirst = pRvd;
        for (int k = 1; k < K; ++k){
            list[pOld].Next = pRvd;
            pRvd = pOld;
            pOld = pNxt;
            if (pNxt != -1) pNxt = list[pNxt].Next;
        }
        list[tmpFirst].Next = pOld;
        list[lastRear].Next = pRvd;
        lastRear = tmpFirst;
    }

    for (int i = firstAddr; i != -1; i = list[i].Next){
        if (list[i].Next != -1)
            printf("%05d %d %05d\n", i, list[i].Data, list[i].Next);
        else printf("%05d %d -1\n", i, list[i].Data);
    }
    return 0;
}