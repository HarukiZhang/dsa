/*Problem Description
h:  He has h hours available (1 <= h <= 16), 
n:  there are n lakes in the area (2 <= n <= 25) all reachable along a single, one-way road.
    John starts at lake 1, but he can finish at any lake he wants. He can only travel from one 
    lake to the next one, but he does not have to stop at any lake unless he wishes to.
ti: For each i = 1,...,n - 1, the number of 5-minute intervals it takes to travel from lake i 
    to lake i + 1 is denoted ti (0 < ti <=192). 
    For example, t3 = 4 means that it takes 20 minutes to travel from lake 3 to lake 4.
fi: For each lake i, the number of fish expected to be caught in the initial 5 minutes, denoted fi
    ( fi >= 0 ), is known. 
di: Each 5 minutes of fishing decreases the number of fish expected to be caught in the next 
    5-minute interval by a constant rate of di (di >= 0). 
    If the number of fish expected to be caught in an interval is less than or equal to di , 
    there will be no more fish left in the lake in the next interval.

Write a program to help John plan his fishing trip to maximize the number of fish expected 
to be caught. The number of minutes spent at each lake must be a multiple of 5.

INPUT:
    You will be given a number of cases in the input. 
    Each case starts with a line containing n. 
    This is followed by a line containing h. 
    Next, there is a line of n integers specifying fi (1 <= i <=n), 
    then a line of n integers di (1 <=i <=n), 
    and finally, a line of n - 1 integers ti (1 <=i <=n - 1). 
    Input is terminated by a case in which n = 0.

OUTPUT:
    For each test case, print the number of minutes spent at each lake, separated by commas, 
    for the plan achieving the maximum number of fish expected to be caught (you should print 
    the entire plan on one line even if it exceeds 80 characters). This is followed by a line 
    containing the number of fish expected.
    If multiple plans exist, choose the one that spends as long as possible at lake 1, even if 
    no fish are expected to be caught in some intervals. If there is still a tie, choose the 
    one that spends as long as possible at lake 2, and so on. Insert a blank line between cases.
*/
#include<iostream>
#include<list>
using namespace std;

short lakeN, totHours,
    fis[30], dis[30], tis[30],
    timePlan[30][30];

struct NODE {
    /*f : the expected num of fish that could be captured in lake iL when j interval passed;
      iL: the current lake no.;
      j : the interval passed at iL lake, BUT this value can be omitted;*/
    short f, iL;
    NODE(short f_, short iL_): f(f_), iL(iL_){}
    bool operator<(const NODE& n){
        if (f != n.f)
            return f < n.f;
        else
        /*Notify that this operator is not really for comparing the size or 
            quantity of a node, rather, it is an method to decide which node should be put
            before the other in the node list;*/
            return iL > n.iL;
    }
};
list<NODE> myLst;

void findMax(){
    /*totIntv: totally left time interval (for each, 5 minutes);*/
    short totIntv = totHours * 12;
    NODE node {-1, -1};
    myLst.push_back(node);
    /*i: the Lake that finally john go to;*/
    for (short i = 1; i <= lakeN; ++i){
        totIntv -= tis[i - 1];
        /*Merge sort each dataset into the list;*/
        node.f = fis[i];
        node.iL = i;
        auto it = myLst.begin();
        /*No node could be lesser than {-1, -1};*/
        while (node < *it) ++it;
        myLst.insert(it, node);
        int j = 2;
        short fishN = fis[i] - dis[i];
        while (j <= totIntv && fishN > 0){
            node.f = fishN;
            while (node < *it) ++it;
            myLst.insert(it, node);
            ++j;
            fishN -= dis[i];
        }
        node.f = 0;
        for (; j <= totIntv; ++j){
            while (node < *it) ++it;
            myLst.insert(it, node);
        }
        /*Record max expectation of fish num on timePlan[i][0];
          Record corresponding time plan following it;*/
        it = myLst.begin();
        for (int k = 0; k < totIntv; ++k, ++it){
            timePlan[i][0] += it->f;
            timePlan[i][it->iL] += 5;
        }
    }
    /*Firstly, find the max expectation;*/
    short* maxExp = timePlan[1];
    for (int i = 2; i <= lakeN; ++i){
        if (timePlan[i][0] > maxExp[0])
            maxExp = timePlan[i];
    }
    /*Then, find out whether there's any same value of expection,
        and dicide which to go according to requirement of probelm;*/
    for (int i = 1; i <= lakeN; ++i){
        if (timePlan[i][0] == maxExp[0]){
            for (int j = 1; j <= lakeN; ++j){
                /*The longer John stays at a former lake, the more fit this answer is to 
                the problem requirement;*/
                if (timePlan[i][j] > maxExp[j]){
                    maxExp = timePlan[i];
                    break;
                }
                /*There's possibility to meet self again;*/
                else if (timePlan[i][j] < maxExp[j])
                    break;
            }
        }
    }
    /*Output:*/
    for (int i = 1; i < lakeN; ++i){
        cout << maxExp[i] << ", ";
    }
    cout << maxExp[lakeN] << "\n" << flush;
    cout << "Number of fish expected: " << maxExp[0] << "\n" << flush;
    cout << "\n" << flush;
}

int main(){
    while (true){
        cin >> lakeN;
        if (lakeN == 0) return 0;

        cin >> totHours;
        for (int i = 1; i <= lakeN; ++i)
            cin >> fis[i];
        for (int i = 1; i <= lakeN; ++i)
            cin >> dis[i];
        for (int i = 1; i < lakeN; ++i)
            cin >> tis[i];  
        
        findMax();

        /*Need to clear all static value;*/
        for (int i = 1; i <= lakeN; ++i){
            fis[i] = 0;
            dis[i] = 0;
            tis[i] = 0;
            for (int j = 0; j <= lakeN; ++j)
                timePlan[i][j] = 0;
        }
        myLst.clear();
    }
}

/*
样例输入
2 
1 
10 1 
2 5 
2
4 
4 
10 15 20 17 
0 3 4 3 
1 2 3 
4 
4 
10 15 50 30 
0 3 4 3 
1 2 3 

0 
样例输出
45, 5 
Number of fish expected: 31 

240, 0, 0, 0 
Number of fish expected: 480 

115, 10, 50, 35 
Number of fish expected: 724 
*/