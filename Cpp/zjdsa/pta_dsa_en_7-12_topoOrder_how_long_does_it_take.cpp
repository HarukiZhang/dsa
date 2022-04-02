/*
Given the relations of all the activities of a project, 
you are supposed to find the earliest completion time of the project.

Input Specification:
Each input file contains one test case. 
Each case starts with a line containing two positive integers 

N (≤100), the number of activity check points 
    (the check points are numbered from 0 to N−1), and 
M, the number of activities. 

Then M lines follow, each gives the description of an activity. 
For the i-th activity, three non-negative numbers are given: 

S[i], E[i], and L[i], 

where

S[i] is the index of the starting check point, 
E[i] of the ending check point, and 
L[i] the lasting time of the activity. 

The numbers in a line are separated by a space.

Output Specification:
For each test case, if the scheduling is possible, 
print in a line its earliest completion time; 
or simply output "Impossible".
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

constexpr int kMaxChkPN = 100;

typedef int CheckPoint;//vertex idx;

struct Activity {//edge;
    CheckPoint end;
    int lasting;
};

vector<Activity> project[kMaxChkPN];//adjacent list;
vector<bool> in_degree_counter[kMaxChkPN];//reverse adjacent list;
                                          //need not real node in it;

int chkPN, actvN;

int isTopoOrder(){
    /*initialization*/
    queue<int> que;//container for 0-degreed vertices;
    int degrees[kMaxChkPN];//records of in-degree for each vertex;
    int cumulTimes[kMaxChkPN]{};//records for ECT, earliest-completion-time;
    for (int i = 0; i < chkPN; ++i)
        //using reversed adjacent list to count in-degree;
        degrees[i] = in_degree_counter[i].size();
    for (int i = 0; i < chkPN; ++i){
        if (degrees[i] == 0)
            que.push(i);
    }
    int vertN = 0, lasting_cnt = 0;
    /*algorithm*/
    while ( !que.empty() ){
        int crt = que.front();
        que.pop();
        ++vertN;
        for (Activity act : project[crt]){
            int time = act.lasting + cumulTimes[crt];
            if (cumulTimes[act.end] < time)
                cumulTimes[act.end] = time;

            --degrees[act.end];
            if (degrees[act.end] == 0)
                que.push(act.end);
        }
    }
    if ( vertN != chkPN)
        return -1;
    return cumulTimes[chkPN - 1];
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> chkPN >> actvN;
    int cpSta;
    Activity acti;
    for (int i = 0; i < actvN; ++i){
        cin >> cpSta >> acti.end >> acti.lasting;
        project[cpSta].push_back( acti );
        in_degree_counter[acti.end].push_back(true);
    }
    int completion_time = isTopoOrder();
    if ( completion_time != -1 )
        cout << completion_time;
    else
        cout << "Impossible";
    return 0;
}

/*
Sample Input 1:
9 12
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
5 4 0
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
Sample Output 1:
18
Sample Input 2:
4 5
0 1 1
0 2 2
2 1 3
1 3 4
3 2 5
Sample Output 2:
Impossible
*/