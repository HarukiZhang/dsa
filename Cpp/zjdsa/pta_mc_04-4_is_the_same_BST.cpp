/*
给定一个插入序列就可以唯一确定一棵二叉搜索树。
然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。
例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。
于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，
分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，
作为初始插入序列。随后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，
输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
输出样例:
Yes
No
No
*/
#include<iostream>
#include<vector>
using namespace std;

constexpr int kMaxNode = 16;

int templ[2][kMaxNode];//0 : left, 1 : right;
bool visited[kMaxNode]{};

void insert(int ptr, int x){
    int last = ptr;
    while (ptr != 0){
        last = ptr;
        if (x < ptr){
            ptr = templ[0][ptr];
        }
        else {
            ptr = templ[1][ptr];
        }
    }
    if (x < last)
        templ[0][last] = x;
    else templ[1][last] = x;
    return;
}

void check(int root, int num){
    /*checking logic:
    When inserting new node into a tree, there should be no path passing 
        through an unvisited node;
    And if not able to find crt input node at all,
        it is not neither a same BST;
    Thus,
        no need for extra space for storage of each case;
    */
    /*initialization*/
    for (int j = 1; j <= num; ++j)
        visited[j] = false;
    /*each test case*/
    bool flag = true;
    int inpN;
    for (int j = 1; j <= num; ++j){
        cin >> inpN;
        if (flag == false ) continue;

        /*analogue the process of inserting a node*/
        int ptr = root, last = ptr;
        while (ptr != 0 && ptr != -1){
            last = ptr;
            if (inpN < ptr){
                ptr = templ[0][ptr];
            }
            else if (inpN > ptr){
                ptr = templ[1][ptr];
            }
            else {//found the crt input;
                visited[ptr] = true;
                /*if set true only when the crt node is found,
                    then no other node should pass an unvisited place
                    in their inserting process;*/
                ptr = 0;//to let while-loop stop;
            }

            if (visited[last] == false){//if pass through an unvisitd node;
                flag = false;
                break;
            }
        }
    }

    if (flag) printf("Yes\n");
    else printf("No\n");
    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N, L;
    while (cin >> N){
        if (N == 0) break;
        cin >> L;

        /*initialization*/
        templ[0][0] = templ[1][0] = -1;
        for (int i = 1; i <= N; ++i)
            templ[0][i] = templ[1][i] = 0;

        /*biuld template tree*/
        int theRoot;
        cin >> theRoot;
        int inputNode;
        for (int i = 2; i <= N; ++i){
            cin >> inputNode;
            insert(theRoot, inputNode);
        }

        /*check*/
        for (int i = 0; i < L; ++i){
            check(theRoot, N);
        }
    }
    return 0;
}