#include<cstdio>
#include<vector>
#include<utility>
using namespace std;

vector<pair<int, int> > maxVec, locVec;
int T, n, k;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    // freopen("E:\\Downloads\\myout.txt", "w", stdout);
    scanf("%d", &T);
    for (int cs = 0; cs < T; ++cs){
        scanf("%d %d", &n, &k);
        int inM, inP;
        /*Firstly push an (0,0) elem as a head of the sequence, so that
        in following algo-loop, we can go backward and access the elem before the actual
        first elem;*/
        locVec.push_back(make_pair(0, 0));
        maxVec.push_back(make_pair(0, 0));
        for (int lcn = 0; lcn < n; ++lcn){
            scanf("%d", &inM);
            locVec.push_back(make_pair(inM, 0));
        }
        for (int lcn = 1; lcn <= n; ++lcn){
            scanf("%d", &inP);
            locVec[lcn].second = inP;
        }
        /*The algo-loop:*/
        for (int i = 1; i <= n; ++i){
            int newLoc = locVec[i].first;
            int newPrf = locVec[i].second;
            int dist = newLoc - k;
            int j;
            for (j = i - 1; j >= 1; --j){
                /*According to the problem, dist must > maxVec[j].first,
                    rather than >= ;*/
                if (dist > maxVec[j].first){
                    /*Even if the distance is enough, if the profit is lower, 
                    do not call it;*/
                    int tmp = newPrf + maxVec[j].second;
                    if (tmp > maxVec[i - 1].second){
                        maxVec.push_back(make_pair(newLoc, tmp));
                        break;
                    }
                }
            }
            /*If the above loop has been breaked, j == 1 at-least;*/
            if (j < 1){
                if (newPrf > maxVec[i - 1].second)
                    maxVec.push_back(make_pair(newLoc, newPrf));
                else 
                    maxVec.push_back(make_pair(maxVec[i - 1].first, maxVec[i - 1].second));
            }
        }

        printf("%d\n", maxVec.back().second);
        maxVec.clear();
        locVec.clear();
    }
}

/*
36 59
5316 9441 10599 14691 16287 17147 22134 25211 25290 26647 26706 30104 33006 38240 40911 43370 47527 50048 51982 55914 57960 61437 62991 67955 72731 76060 81200 83308 86100 88750 93886 98963 103455 106922 109832 110059
100 133 280 559 327 97 537 951 340 291 581 901 451 465 39 935 471 794 806 32 946 777 231 922 269 423 674 508 816 751 54 278 797 446 251 537
*/
/*
描述
北大信息学院的同学小明毕业之后打算创业开餐馆.现在共有n 个地点可供选择。小明打算从中选择合适的位置开设一些餐馆。这 n 个地点排列在同一条直线上。我们用一个整数序列m1, m2, ... mn 来表示他们的相对位置。由于地段关系,开餐馆的利润会有所不同。我们用pi 表示在mi 处开餐馆的利润。为了避免自己的餐馆的内部竞争,餐馆之间的距离必须大于k。请你帮助小明选择一个总利润最大的方案。

输入
标准的输入包含若干组测试数据。输入第一行是整数T (1 <= T <= 1000) ，表明有T组测试数据。紧接着有T组连续的测试。每组测试数据有3行,
第1行:地点总数 n (n < 100), 距离限制 k (k > 0 && k < 1000).
第2行:n 个地点的位置m1 , m2, ... mn ( 1000000 > mi > 0 且为整数,升序排列)
第3行:n 个地点的餐馆利润p1 , p2, ... pn ( 1000 > pi > 0 且为整数)
输出
对于每组测试数据可能的最大利润
样例输入
2
3 11
1 2 15
10 2 30
3 16
1 2 15
10 2 30
样例输出
40
30
*/