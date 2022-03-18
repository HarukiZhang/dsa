#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 100;
int n, k, num[N];
struct Que
{
    int loc, x;
    Que() {}
    Que(int _loc, int _x) : loc(_loc), x(_x) {}
} minQ[N], maxQ[N]; //一个最小队列，一个最大队列
int iLfN, iRtN, iLfX, iRtX;
int main()
{
    freopen("E:\\Downloads\\in.txt", "r", stdin);

    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);

    iLfN = iRtN = 0;
    int i;
    for (i = 0; i < k; i++)
    { //队列初始化
        while (iRtN > 0 && minQ[iRtN - 1].x > num[i])
            iRtN--;
        minQ[iRtN++] = Que(i, num[i]);
    }
    printf("%d", minQ[iLfN].x);
    for (; i < n; i++)
    {
        //循环比较队尾元素与插入元素的大小，直到对尾元素<=插入元素或者队为空
        while (iRtN > iLfN && minQ[iRtN - 1].x > num[i])
            iRtN--;
        //入队
        minQ[iRtN++] = Que(i, num[i]);
        //判断队首元素是否还在查询范围之内
        while (minQ[iLfN].loc < i - k + 1)
            iLfN++;
        printf(" %d", minQ[iLfN].x);
    }
    printf("\n");

    //与上面求最小值相同
    iLfX = iRtX = 0;
    for (i = 0; i < k; i++)
    {
        while (iRtX > 0 && maxQ[iRtX - 1].x < num[i])
            iRtX--;
        maxQ[iRtX++] = Que(i, num[i]);
    }
    printf("%d", maxQ[iLfX].x);
    for (; i < n; i++)
    {
        while (iRtX > iLfX && maxQ[iRtX - 1].x < num[i])
            iRtX--;
        maxQ[iRtX++] = Que(i, num[i]); //入队
        while (maxQ[iLfX].loc < i - k + 1)
            iLfX++;
        printf(" %d", maxQ[iLfX].x);
    }
    return 0;
}