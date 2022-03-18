#include<cstdio>
#include<vector>
using namespace std;

int rSta, cSta, rTar, cTar;
struct NODE {
    int row, col,
        hCost, gCost,
        fCost;
    NODE(int r, int c, int gC) : row(r), col(c), gCost(gC) {
        hCost = 
    }
};