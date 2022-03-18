//http://dsalgo.openjudge.cn/linearlists/1/
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node
{
    int coef, expo;
    bool operator<(const Node& rt) const {
        return expo > rt.expo;
    }
};

Node inp[512];
Node res[512];

int main(){
    for (int i = 0; i < 512; ++i)
        inp[i].expo = -1;

    int cN, cfin, epin;
    scanf("%d", &cN);
    for (int k = 0; k < cN; ++k){

        int itm = 0;
        for (int i = 0; i < 2; ++i){
            while (true){
                scanf("%d %d", &cfin, &epin);
                if (epin < 0)
                    break;
                inp[itm].coef = cfin; inp[itm].expo = epin;
                ++itm;
            }
        }

        sort(inp, inp + itm);

        int ii = 0, ir = 0, curE, nexE;
        while (ii < itm){
            curE = inp[ii].expo;
            res[ir].coef += inp[ii].coef;
            res[ir].expo = inp[ii].expo;

            nexE = inp[ii + 1].expo;
            
            ++ii;
            if (curE != nexE)
                ++ir;
        }

        int stp = ir - 1;
        for (int i = 0; i < stp; ++i){
            if (res[i].coef != 0)
                printf("[ %d %d ] ", res[i].coef, res[i].expo);
        }
        if (res[stp].coef != 0)
            printf("[ %d %d ]", res[stp].coef, res[stp].expo);
        printf("\n");

        for (int i = 0; i <= itm; ++i){
            inp[i].coef = res[i].coef = 0;
            inp[i].expo = res[i].expo = -1;
        }
    }
}

/*
样例输入
2
-1 17 2 20 5 9 -7 7 10 4 22 2 -15 0 16 5 0 -1
2 19 7 7 3 17 4 4 15 10 -10 5 13 2 -7 0 8 -8
-1 17 2 23 22 2 6 8 -4 7 -18 0 1 5 21 4 0 -1
12 7 -7 5 3 17 23 4 15 10 -10 5 13 5 2 19 9 -7
样例输出
[ 2 20 ] [ 2 19 ] [ 2 17 ] [ 15 10 ] [ 5 9 ] [ 6 5 ] [ 14 4 ] [ 35 2 ] [ -22 0 ]


[ 2 23 ] [ 2 19 ] [ 2 17 ] [ 15 10 ] [ 6 8 ] [ 8 7 ] [ -3 5 ] [ 44 4 ] [ 22 2 ] [ -18 0 ]
*/

/*Test sample:

1
-2 2 0 -1
2 2 0 -1


*/