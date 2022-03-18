#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<utility>
/*There seems to be some problem with the POJ system so that it won't give any feedback at all;
    So, I dont konw whether this version of solution is correct for all datasets,
    but has already been verified with sample data;*/
using namespace std;
int p1Full, p2Full, goalVol;
struct NODE {
    /*p[0] : amount of pot 1; p[1] : pot 2;*/
    int p[2];
    NODE(){}
    NODE(int p1, int p2) { p[0] = p1; p[1] = p2; }
    NODE(const NODE& n) { p[0] = n.p[0]; p[1] = n.p[1]; }
    void operator=(const NODE& n){ p[0] = n.p[0]; p[1] = n.p[1]; }
    void fill(int n){
        if (n != 1)
            p[1] = p2Full;
        else p[0] = p1Full;
    }
    void pour(int n){
        //Default: pour 1 to 2;
        int pr = 0;
        int rv = 1;
        int rvVol = p2Full;
        if (n != 1){
        /*Pour 2 to 1;*/
            pr = 1;
            rv = 0;
            rvVol = p1Full;
        }
        /*Before using method.pour(), status in both pots should have been checked;*/
        int restVol = rvVol - p[rv];
        if (p[pr] <= restVol){
        /*Pour all of p2 into p1;*/
            p[rv] += p[pr];
            p[pr] = 0;
        }
        else {
        /*Pour till the recipient is full;*/
            p[pr] = p[pr] - restVol;
            p[rv] = rvVol;
        }
    }
    void drop(int n){
        if (n != 1)
            p[1] = 0;
        else p[0] = 0;
    }
};
bool ctrlTbl[110][110];
queue<NODE> myQue;
/*.first:                .second:
    Fill(1)    : 0          subscript of father node;
    Fill(2)    : 1
    Drop(1)    : 2
    Drop(2)    : 3
    Pour(1, 2) : 4
    Pour(2, 1) : 5 */
vector<pair<int, int> > myVec;
stack<int> myStk;

void findWays(){
    NODE node {0,0};
    myQue.push(node);
    /*Push a stop sign into vector;*/
    myVec.push_back(make_pair(-1,-1));
    ctrlTbl[0][0] = true;

    int cnt = 0;
    while (!myQue.empty()){
        NODE& curNode = myQue.front();
        int p1 = curNode.p[0], p2 = curNode.p[1];
        /*Search all potential related status (node);*/
        if (p1 != p1Full){
            /*Fill(1)*/
            node = curNode;
            node.fill(1);
            if (!ctrlTbl[node.p[0]][node.p[1]]){
                myQue.push(node);
                myVec.push_back(make_pair(0, cnt));
                /*Filling action could only let target pot reach the goal;*/
                if (node.p[0] == goalVol) break;
                ctrlTbl[node.p[0]][node.p[1]] = true;
            }

            if (p2 != 0){
                /*Pour(2,1)*/
                node = curNode;
                node.pour(2);
                if (!ctrlTbl[node.p[0]][node.p[1]]){
                    myQue.push(node);
                    myVec.push_back(make_pair(5, cnt));
                    /*Pouring act may let
                        pouring pot reach goal if there are some left;
                        receiving pot reach if the sum of two is just;*/
                    if (node.p[0] == goalVol || node.p[1] == goalVol) break;
                    ctrlTbl[node.p[0]][node.p[1]] = true;
                }
            }
        }
        if (p2 != p2Full){
            /*Fill(2)*/
            node = curNode;
            node.fill(2);
            if (!ctrlTbl[node.p[0]][node.p[1]]){
                myQue.push(node);
                myVec.push_back(make_pair(1, cnt));
                if (node.p[1] == goalVol) break;
                ctrlTbl[node.p[0]][node.p[1]] = true;
            }
            if (p1 != 0){
                /*Pour(1,2)*/
                node = curNode;
                node.pour(1);
                if (!ctrlTbl[node.p[0]][node.p[1]]){
                    myQue.push(node);
                    myVec.push_back(make_pair(4, cnt));
                    if (node.p[0] == goalVol || node.p[1] == goalVol) break;
                    ctrlTbl[node.p[0]][node.p[1]] = true;
                }
            }
        }
        if (p1 != 0){
            /*Drop(1)*/
            node = curNode;
            node.drop(1);
            if (!ctrlTbl[node.p[0]][node.p[1]]){
                myQue.push(node);
                myVec.push_back(make_pair(2, cnt));
                /*Droping action could not reach the goal;*/
                ctrlTbl[node.p[0]][node.p[1]] = true;
            }
        }
        if (p2 != 0){
            /*Drop(2)*/
            node = curNode;
            node.drop(2);
            if (!ctrlTbl[node.p[0]][node.p[1]]){
                myQue.push(node);
                myVec.push_back(make_pair(3, cnt));
                ctrlTbl[node.p[0]][node.p[1]] = true;
            }
        }
        myQue.pop();
        /*Counter increment when each time myQue pop an element;*/
        ++cnt;
    }
    /*Breaking condition was never reached in above loop;*/
    if (myQue.empty()){
        cout << "impossible\n" << flush;
        return;
    }
    /*Backward search the shortest route;*/
    myStk.push(myVec.back().first);
    int idx = myVec.back().second;
    while (idx){
        myStk.push(myVec[idx].first);
        idx = myVec[idx].second;
    }
    /*Print min steps, which == the lenght of printing stack;*/
    cout << myStk.size() << "\n" << flush;
    /*Print each step;*/
    while (!myStk.empty()){
        /*Decoder:
            Fill(1)    : 0
            Fill(2)    : 1
            Drop(1)    : 2
            Drop(2)    : 3
            Pour(1, 2) : 4
            Pour(2, 1) : 5 
        */
        switch (myStk.top()) {
            case 0: cout << "FILL(1)\n" << flush; break;
            case 1: cout << "FILL(2)\n" << flush; break;
            case 2: cout << "DROP(1)\n" << flush; break;
            case 3: cout << "DROP(2)\n" << flush; break;
            case 4: cout << "POUR(1,2)\n" << flush; break;
            case 5: cout << "POUR(2,1)\n" << flush; break;
            default: cout << "printing switch wrong\n" << flush;
        }
        myStk.pop();
    }
}

int main(){
    cin >> p1Full >> p2Full >> goalVol;
    findWays();
}

/*
描述
You are given two pots, having the volume of A and B liters respectively. The following operations can be performed:

FILL(i)        fill the pot i (1 ≤ i ≤ 2) from the tap;
DROP(i)      empty the pot i to the drain;
POUR(i,j)    pour from pot i to pot j; after this operation either the pot j is full (and there may be some water left in the pot i), or the pot i is empty (and all its contents have been moved to the pot j).
Write a program to find the shortest possible sequence of these operations that will yield exactly C liters of water in one of the pots.

输入
On the first and only line are the numbers A, B, and C. These are all integers in the range from 1 to 100 and C≤max(A,B).

输出
The first line of the output must contain the length of the sequence of operations K. The following K lines must each describe one operation. If there are several sequences of minimal length, output any one of them. If the desired result can’t be achieved, the first and only line of the file must contain the word ‘impossible’.

样例输入
3 5 4
样例输出
6
FILL(2)
POUR(2,1)
DROP(1)
POUR(2,1)
FILL(2)
POUR(2,1)
*/