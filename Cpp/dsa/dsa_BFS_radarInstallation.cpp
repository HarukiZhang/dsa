/*Problem Description:
Assume the coasting is an infinite straight line. Land is in one side of coasting, sea in 
the other. Each small island is a point locating in the sea side. And any radar installation, 
locating on the coasting, can only cover d distance, so an island in the sea can be covered 
by a radius installation, if the distance between them is at most d.

We use Cartesian coordinate system, defining the coasting is the x-axis. The sea side is 
above x-axis, and the land side below. Given the position of each island in the sea, and 
given the distance of the coverage of the radar installation, your task is to write a program 
to find the minimal number of radar installations to cover all the islands. Note that the 
position of an island is represented by its x-y coordinates.

INPUT:
    The input consists of several test cases. The first line of each case contains two integers n 
    (1<=n<=1000) and d, where n is the number of islands in the sea and d is the distance of 
    coverage of the radar installation. This is followed by n lines each containing two integers 
    representing the coordinate of the position of each island. Then a blank line follows to 
    separate the cases.

    The input is terminated by a line containing pair of zeros

OUTPUT:
    For each test case output one line consisting of the test case number followed by the 
    minimal number of radar installations needed. "-1" installation means no solution for that 
    case.
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include<cmath>
/*Solution explanation:
Convert a 2-dimentional problem into a linear problem:
    Draw a circle with radar's cover range d in each island position as the center;
    The interception of circle with the x-axis constituated a range in which the radar
    could be set to cover this island;
    Thereafter, this problem became a linear problem and can be solve with gready algo;
*/
using namespace std;
typedef pair<float, float> PFF;
int islandN, radarD;
vector<PFF> intervals;

struct compRule {
    bool operator()(const PFF& a, const PFF& b){
        return a.first < b.first;
    }
};

int main(){
    int cntCase = 1;
    while (true){
        cin >> islandN >> radarD;
        if (islandN == 0) return 0;
        float tx, ty, dev, curRtBd;
        vector<PFF>::iterator it;
        int cnt;
        bool flag = true;
        for (int i = 0; i < islandN; ++i){
            cin >> tx >> ty;
            if (ty > radarD){
                flag = false;
            }
            dev = powf(radarD * radarD - ty * ty, 0.5f);
            intervals.push_back(make_pair(tx - dev, tx + dev));
        }
        if (flag){
            sort(intervals.begin(), intervals.end(), compRule());
            it = intervals.begin();
            curRtBd = it->second;
            cnt = 1;
            for (++it; it != intervals.end(); ++it){
                /*When i-th elem's left boundary go beyond the current right boundary,
                we need to set a radar for previous islands, and another radar for the i-th
                island;*/
                if (it->first > curRtBd){
                    ++cnt;
                    curRtBd = it->second;
                }
                /*There's another possibility that one elem's range is too big, so that
                a smaller one may be totally enclosed within the big range;*/
                else if (it->second < curRtBd)
                    curRtBd = it->second;
            }
            cout << "Case " << cntCase << ": " << cnt << "\n" << flush;
        }
        else {
            cout << "Case " << cntCase << ": -1\n" << flush;

        }
        intervals.clear();
        ++cntCase;
    }
}

/*
SampleIN:
3 2
1 2
-3 1
2 1

1 2
0 2

0 0

SampleOUT:
Case 1: 2
Case 2: 1
*/