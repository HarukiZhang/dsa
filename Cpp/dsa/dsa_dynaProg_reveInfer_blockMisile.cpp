#include<iostream>
using namespace std;
int mslsH[30]{};
int maxBlockN[30]{};
int mslN;

/*Query the max number of misiles that can be blocked on and after the idx loc*/
int blockMisile(int idx){
    // The max in the final loc is 1;
    maxBlockN[mslN - 1] = 1;
    // Loop starts from the second last loc, and stops at the param idx;
    for (int i = mslN - 2; i >= idx; --i){
        // Search for the max blockNum after the current misile having 
        // been blocked successfully;
        int maxBlockTmp = 0;
        for (int i1 = i + 1; i1 < mslN; ++i1){
            // Quali 1 : height is lower than the current;
            if (mslsH[i1] <= mslsH[i]){
                // Quali 2 : the max comparing to those after it;
                if (maxBlockTmp < maxBlockN[i1])
                    maxBlockTmp = maxBlockN[i1];
            }
        }
        // Record current max blocking number;
        maxBlockN[i] = maxBlockTmp + 1;
    }
    // Finally search the whole blocking number array for the max;
    int res = maxBlockN[0];
    for (int i = 1; i < mslN; ++i){
        if (maxBlockN[i] > res)
            res = maxBlockN[i];
    }
    return res;
}

int main(){
    int inp;
    cin >> mslN;
    for (int i = 0; i < mslN; ++i){
        cin >> inp;
        mslsH[i] = inp;
    }
    cout << blockMisile(0);
}