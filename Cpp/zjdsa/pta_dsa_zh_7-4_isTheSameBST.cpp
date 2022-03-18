/*是否同一棵二叉搜索树
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的
插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。
于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个
数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。随后L行，每行给出N个
插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，
否则输出“No”。

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
using namespace std;
struct Node { int val, lf, rt; };
int main(){
    freopen("E:\\in.txt", "r", stdin);

    /*Static list storage;*/
    Node tree[12]{};
    int N, L, prtLoc, smpl[12], cmpTbl[2][12]{};
    while (true){
        cin >> N;
        if (N == 0)
            return 0;
        cin >> L;
        for (int i = 0; i < N; ++i){
            cin >> tree[i].val;
            tree[i].lf = tree[i].rt = -1;//set nullptr;
        }
        /*According to template sequence, biuld the template tree
        and record each node's parent idx to compareTable, which is a hash table;
            Row 0 : parent idx;
            Row 1 : a check board for whether current node has been inserted;*/
        cmpTbl[0][tree[0].val] = -1;//root has no parent;
        for (int i = 1; i < N; ++i){
            int j = 0;
            while (j < i){
                if (tree[i].val > tree[j].val){
                    if (tree[j].rt != -1){//not nullptr;
                        j = tree[j].rt;
                    }
                    else {
                        tree[j].rt = i;
                        /*tree node value is regarded as hash value;*/
                        cmpTbl[0][tree[i].val] = tree[j].val;
                        break;
                    }
                }
                else {//problem do not have equal val for each node;
                    if (tree[j].lf != -1){
                        j = tree[j].lf;
                    }
                    else {
                        tree[j].lf = i;
                        cmpTbl[0][tree[i].val] = tree[j].val;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < L; ++i){
            for (int j = 0; j < N; ++j){
                cin >> smpl[j];
                cmpTbl[1][j + 1] = 0;//reset 0 for each sequence; idx starts from 1;
            }
            int k;
            for (k = 0; k < N; ++k){
                cmpTbl[1][smpl[k]] = 1;
                /*Check hash table to find whether current node's parent node 
                has already been inserted before;*/
                prtLoc = cmpTbl[0][smpl[k]];
                if (prtLoc > -1 && !cmpTbl[1][prtLoc]){//parent's YET been inserted;
                    cout << "No" << endl;
                    break;
                }
            }
            /*If every node is inserted after its parent;*/
            if (k == N)
                cout << "Yes" << endl;
        }
    }
    return 0;
}