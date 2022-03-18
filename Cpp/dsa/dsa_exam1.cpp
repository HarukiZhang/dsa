#include<cstdio>
#include<vector>
using namespace std;

int T, N;
vector<int> myVec;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    scanf("%d", &T);
    for (int i = 0; i < T; ++i){
        int sumO = 0, sumE = 0, inp, last;
        bool flag = true;
        scanf("%d", &N);
        if (N < 2){
            scanf("%d", &inp);
            printf("%d\n", inp);
            continue;
        }
        scanf("%d", &inp);
        myVec.push_back(inp);
        last = inp;
        scanf("%d", &inp);
        if (inp > last) myVec.push_back(inp);
        else {
            myVec.push_back(last);
            flag = false;
        }
        for (int j = 2; j < N; ++j){
            scanf("%d", &inp);

            if (flag){//the last elem was chosen;
                int tmp = inp + myVec[j - 2];
                if (tmp > myVec[j - 1]){
                    myVec.push_back(tmp);
                    flag = true;
                }
                else {
                    myVec.push_back(myVec[j - 1]);
                    flag = false;
                }
            }
            else {
                myVec.push_back(myVec[j - 1] + inp);
                flag = true;
            }
        }
        printf("%d\n", myVec.back());
        myVec.clear();
    }
}

/*
描述
阿福是一名经验丰富的大盗。趁着月黑风高，阿福打算今晚洗劫一条街上的店铺。

这条街上一共有 N 家店铺，每家店中都有一些现金。阿福事先调查得知，只有当他同时洗劫了两家相邻的店铺时，街上的报警系统才会启动，然后警察就会蜂拥而至。

作为一向谨慎作案的大盗，阿福不愿意冒着被警察追捕的风险行窃。他想知道，在不惊动警察的情况下，他今晚最多可以得到多少现金？

输入
输入的第一行是一个整数 T (T <= 50) ，表示一共有 T 组数据。
接下来的每组数据，第一行是一个整数 N (1 <= N <= 100, 000) ，表示一共有 N 家店铺。第二行是 N 个被空格分开的正整数，表示每一家店铺中的现金数量。每家店铺中的现金数量均不超过 1000 。
输出
对于每组数据，输出一行。该行包含一个整数，表示阿福在不惊动警察的情况下可以得到的现金数量。
样例输入
2
3
1 8 2
4
10 7 6 14
样例输出
8
24
提示
对于第一组样例，阿福选择第 2 家店铺行窃，获得的现金数量为 8 。
对于第二组样例，阿福选择第 1 和 4 家店铺行窃，获得的现金数量为 10 + 14 = 24 。
*/