#include<cstdio>
using namespace std;

constexpr int kLen = 80010;
int arr[kLen], N, rec[kLen]{};

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &arr[i]);
    long long max = 0;

    for (int i = 1; i < N; ++i){
        for (int j = i - 1; j >= 0; --j){
            if (arr[i] < arr[j]){
                rec[i] = rec[j] + 1;
                break;
            }
        }
        max += rec[i];
    }

    printf("%lld\n", max);
    return 0;
}

/*
描述
农夫John 的N(1 ≤ N ≤ 80,000)只奶牛中，有一些也许正在经历发型糟糕的一天。每只奶牛对自己乱糟糟的发型都有自知之明，农夫John想知道所有奶牛能看到其他奶牛头顶的数量之和。

任意奶牛i身高记为 hi (1 ≤ hi ≤ 1,000,000,000)，所有奶牛面向东方（本题示意图的右面）依次站成一条线。因此，奶牛i能够看到在它前面的（奶牛i+1，i+2…）所有身高比它低的奶牛，直到被一头比它高的奶牛挡住

考虑如下的例子：

        =
=       =
=   -   =         Cows facing right ->
=   =   =
= - = = =
= = = = = =
1 2 3 4 5 6 
奶牛#1 可以看见奶牛#2, 3, 4的头顶

奶牛#2 无法看到任何奶牛的头顶

奶牛#3可以看见奶牛#4的头顶

奶牛#4无法看到任何奶牛的头顶

奶牛#5可以看见奶牛#6的头顶

奶牛#6无法看到任何奶牛的头顶!

用ci表示奶牛i能够看到头顶的奶牛个数；请计算c1 至cN的和。对于上面这个例子，其和为：3 + 0 + 1 + 0 + 1 + 0 = 5。

输入
第1行：奶牛数N

第2行至N+1行：第i+1行包含一个整数，表示奶牛i的高度

输出
第1行：c1 至cN的累加和
样例输入
6
10
3
7
4
12
2
样例输出
5
*/