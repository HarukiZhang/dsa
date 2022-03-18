#include<iostream>
using namespace std;

/*The key logic:
    Multiple dimention is related to the number of unknown value in the question of the problem;
    
    Regarding transfer function:
    Due to that this kind of problem has optimal sub-structure, that is, the sub-problem destructured
    from the main problem always has its own most applicable solution, 
    and usually, this optimal solution is to search for minimum or maximum,
    So, to construct the transfer function, it could be considered to use maximum/minimum search,
    especially when the problem has its binary branch after being performed one sub-step;
    */

constexpr short kMax = 0x7fff;

/*Recursion:*/
short cuttingCake(short w, short h, short m){
    /*m stands for cutting times*/
    if (w * h < m + 1)
        return kMax;
    else if (m == 0)
        return w * h;
    
    short sV = kMax, sH = kMax, si = kMax, sj = kMax;

    for (int i = 1; i < w; ++i){
        for (int k = 0; k < m; ++k){
            short cutLeft = cuttingCake(i, h, k);
            short cutRight = cuttingCake(w - i, h, m - 1 - k);
            short optimV = cutLeft > cutRight ? cutLeft : cutRight;
            if (optimV < si)
                si = optimV;
        }
        if (si < sV)
            sV = si;
    }
    for (int j = 1; j < h; ++j){
        for (int k = 0; k < m; ++k){
            short cutUp = cuttingCake(w, j, k);
            short cutDown = cuttingCake(w, h - j, m - 1 - k);
            short optimH = cutUp > cutDown ? cutUp : cutDown;
            if (optimH < sj)
                sj = optimH;
        }
        if (sj < sH)
            sH = sj;
    }

    short res = sV < sH ? sV : sH;
    return res;
}

/*DynaProg in main()*/
constexpr short kInp = 20;
short mtx[22][22][22];

int main() {
    /*Firstly, compute all matrix to the input max, and while reading input directly search
    result from the matrix*/
    short cutTimes = kInp - 1;
    //pre-define values when cuttingTimes == 0, value = width * height;
    for (short i = 1; i <= kInp; ++i)
        for (short j = 1; j <= kInp; ++j)
            mtx[0][i][j] = i * j;
    
    for (short k = 1; k <= cutTimes; ++k){
        for (short i = 1; i <= kInp; ++i){
            for (short j = 1; j <= kInp; ++j){
                //
                if (i * j < k + 1)
                    mtx[k][i][j] = kMax;
                /*mirror-reflection*/
                else if (j < i)
                    mtx[k][i][j] = mtx[k][j][i];
                else {
                    /*searching for minimal by vertic/horizantal indices is the same as 
                    searching by cutingTimes indices*/
                    short sV = kMax, si = kMax;
                    short sH = kMax, sj = kMax;
                    for (short kk = 0; kk < k; ++kk){
                        short iStp = i / 2, jStp = j / 2;
                        for (short ii = 1; ii <= iStp; ++ii){
                            short ctLf = mtx[kk][ii][j];
                            short ctRt = mtx[k - 1 - kk][i - ii][j];
                            short tmp = ctLf > ctRt ? ctLf : ctRt;
                            if (tmp < si)
                                si = tmp;
                        }
                        if (si < sV)
                            sV = si;
                        for (short jj = 1; jj <= jStp; ++jj){
                            short ctUp = mtx[kk][i][jj];
                            short ctDw = mtx[k - 1 - kk][i][j - jj];
                            short tmp = ctUp > ctDw ? ctUp : ctDw;
                            if (tmp < sj)
                                sj = tmp;
                        }
                        if (sj < sH)
                            sH = sj;
                    }
                    mtx[k][i][j] = sV < sH ? sV : sH;
                }
            }
        }
    }
    
    short wIn, hIn, pieces;
    while (cin >> wIn >> hIn >> pieces){
        if (wIn == 0 && wIn == hIn && wIn == pieces)
            return 0;
        cout << mtx[pieces - 1][wIn][hIn] << "\n" << flush;
    }
}



/*
1 ≤ w, h, m ≤ 20
m ≤ wh
*/