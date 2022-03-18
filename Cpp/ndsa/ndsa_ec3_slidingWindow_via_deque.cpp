#include<cstdio>
#include<deque>
using namespace std;
struct Node { int loc, val; };
deque<Node> myDq;
int n, k, arr[1'000'010];
int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);
    Node tmp;
    int i;
    /*min Queue*/
    for (i = 0; i < k; ++i){
        while (!myDq.empty() && myDq.back().val > arr[i])
            myDq.pop_back();
        tmp.loc = i;
        tmp.val = arr[i];
        myDq.push_back(tmp);
    }
    printf("%d", myDq.front().val);
    for (; i < n; ++i){
        while (!myDq.empty() && myDq.back().val > arr[i])
            myDq.pop_back();
        tmp.loc = i;
        tmp.val = arr[i];
        myDq.push_back(tmp);
        if (myDq.front().loc < i - k + 1)
            myDq.pop_front();
        printf(" %d", myDq.front().val);
    }
    printf("\n");
    myDq.clear();
    /*max Queue*/
    for (i = 0; i < k; ++i){
        while (!myDq.empty() && myDq.back().val < arr[i])
            myDq.pop_back();
        tmp.loc = i;
        tmp.val = arr[i];
        myDq.push_back(tmp);
    }
    printf("%d", myDq.front().val);
    for (; i < n; ++i){
        while (!myDq.empty() && myDq.back().val < arr[i])
            myDq.pop_back();
        tmp.loc = i;
        tmp.val = arr[i];
        myDq.push_back(tmp);
        if (myDq.front().loc < i - k + 1)
            myDq.pop_front();
        printf(" %d", myDq.front().val);        
    }
    printf("\n");
    return 0;
}

/*
描述
给定一个长度为n（n<=10^6）的数组。有一个大小为k的滑动窗口从数组的最左端移动到最右端。你可以看到窗口中的k个数字。窗口每次向右滑动一个数字的距离。
下面是一个例子：
数组是 [1 3 -1 -3 5 3 6 7]， k = 3。

窗口位置	最小值	最大值
[1  3  -1] -3  5  3  6  7 	-1	3
 1 [3  -1  -3] 5  3  6  7 	-3	3
 1  3 [-1  -3  5] 3  6  7 	-3	5
 1  3  -1 [-3  5  3] 6  7 	-3	5
 1  3  -1  -3 [5  3  6] 7 	3	6
 1  3  -1  -3  5 [3  6  7]	3	7


你的任务是得到滑动窗口在每个位置时的最大值和最小值。


输入
输入包括两行。
第一行包括n和k，分别表示数组的长度和窗口的大小。
第二行包括n个数字。
输出
输出包括两行。
第一行包括窗口从左至右移动的每个位置的最小值。
第二行包括窗口从左至右移动的每个位置的最大值。
样例输入
8 3
1 3 -1 -3 5 3 6 7
样例输出
-1 -3 -3 -3 3 3
3 3 5 5 6 7
*/