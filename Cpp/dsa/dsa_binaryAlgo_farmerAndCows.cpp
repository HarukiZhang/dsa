#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int>::iterator MYIT;
vector<int> myvec;

MYIT bSearch(MYIT left, MYIT right, int tar){
    int drdmid;
    MYIT mid;
    while (left <= right){
        mid = left + ((right - left) / 2);
        drdmid = *mid;
        if (drdmid == tar)
            return mid;
        if (drdmid < tar)
            left = mid + 1;
        else 
            right = mid - 1;
    }
    // To ensure : the iter returned >= the loc of target;
    // if (drdmid < tar) ++mid;
    // if (drdmid > tar) --mid;
    return mid;
}


int main() {
    freopen("E:\\Downloads\\in.txt", "r", stdin);
    int locN, cN, input;
    cin >> locN >> cN;
    for (int i = 0; i < locN; ++i){
        cin >> input;
        myvec.push_back(input);
    }
    sort(myvec.begin(), myvec.end());
    int firstLoc = *myvec.begin(),
        lastLoc = *myvec.rbegin(),
        barnTotalLen = lastLoc - firstLoc,
        maxTheoreticalDistance = barnTotalLen / (cN - 1),
        restCowsN,
        restSpace,
        drdmyit;
    MYIT myit;

    int minDist = 1, 
        maxDist = maxTheoreticalDistance,
        currentDist,
        optimDist = 1;
    while (minDist <= maxDist){
        currentDist = minDist + (maxDist - minDist) / 2;

        bool flag_forw = false, flag_reve = false;
        
        // Reverse settling:
        restCowsN = cN - 1;
        restSpace = barnTotalLen - restCowsN * currentDist;
        for (int j = lastLoc - currentDist; j >= firstLoc; j -= currentDist){
            myit = bSearch(myvec.begin(), myvec.end(), j);
            drdmyit = *myit;
            if (drdmyit != j){
                if (drdmyit > j){
                    --myit;
                    drdmyit = *myit;
                }
                restSpace -= j - drdmyit;
                j = drdmyit;
            }
            --restCowsN;
            if (restSpace < 0) break;
        }
        if (restCowsN <= 0) flag_reve = true;
        
        // Forward settling:
        restCowsN = cN - 1;
        restSpace = barnTotalLen - restCowsN * currentDist;
        for (int j = firstLoc + currentDist; j <= barnTotalLen; j += currentDist){
            myit = bSearch(myvec.begin(), myvec.end(), j);
            // bSearch only return iter that >= the loc of tar j;
            drdmyit = *myit;
            if (drdmyit != j){
                if (drdmyit < j){
                    ++myit;
                    drdmyit = *myit;
                }
                restSpace -= drdmyit - j;
                j = drdmyit;
            }
            --restCowsN;// One cow is settled;
            if (restSpace < 0) break;
        }
        if (restCowsN <= 0) flag_forw = true;

        // Record the current distance;
        if (flag_forw || flag_reve){
            if (optimDist < currentDist)
                optimDist = currentDist;
        }

        // With binary search method to decide next distance to be tried;

        if (!flag_forw && !flag_reve){//both failed : too far;
            maxDist = currentDist - 1;
        }
        else {// if any of each succeed : too near or just-fit;
            minDist = currentDist + 1;
        }
    }
    cout << optimDist;
    return 0;
}

/*
INPUT:
12 8
1
3
6
11
18
27
38
41
56
73
92
113

OUTPUT:
10
*/