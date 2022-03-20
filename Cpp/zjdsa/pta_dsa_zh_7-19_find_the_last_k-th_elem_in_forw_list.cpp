/*
给定一系列正整数，请设计一个尽可能高效的算法，查找倒数第K个位置上的数字。

输入格式:
输入首先给出一个正整数K，随后是若干非负整数，最后以一个负整数表示结尾（该负数不算在序列内，不要处理）。

输出格式:
输出倒数第K个位置上的数据。如果这个位置不存在，输出错误信息NULL。

输入样例:
4 1 2 3 4 5 6 7 8 9 0 -1
输出样例:
7
*/
#include<cstdio>
#include<vector>
using namespace std;

/*
Use vector to substitute linked-list for storage;
Limit access method as sequential iterater;

Logic: use two pointer to iterate whole list, and control the distance between them;
*/

vector<int> list_mimic;

int main(){
    int K;
    scanf("%d", &K);
    if (K < 0){ printf("NULL\n"); return 0; }

    /*Firstly, input*/
    int tmp;
    while (scanf("%d", &tmp) && tmp >= 0){
        list_mimic.push_back(tmp);
    }
    /*Start to find*/
    int dist = 0;
    vector<int>::iterator tar, tail;
    tar = list_mimic.end();
    tail = list_mimic.begin();
    while (tail != list_mimic.end() && dist < K){
        ++tail;
        ++dist;
    }
    if (dist == K)
        tar = list_mimic.begin();
    while (tail != list_mimic.end()){
        ++tar;
        ++tail;
    }    
    if (tar != list_mimic.end()) printf("%d\n", *tar);
    else printf("NULL\n");
    return 0;
}