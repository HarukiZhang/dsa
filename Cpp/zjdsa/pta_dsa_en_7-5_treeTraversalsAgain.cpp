/*
An inorder binary tree traversal can be implemented in a non-recursive way with a
stack. For example, suppose that when a 6-node binary tree (with the keys numbered
from 1 to 6) is traversed, the stack operations are:

    push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5);
    push(6); pop(); pop().

Then a unique binary tree (shown below) can be generated from this sequence
of operations. Your task is to give the postorder traversal sequence of this tree.

                                1
                             /     \
                            2       5
                           / \     /
                          3   4   6

Input Specification:
Each input file contains one test case. For each case, the first line contains a
positive integer N (≤30) which is the total number of nodes in a tree (and hence
the nodes are numbered from 1 to N). Then 2N lines follow, each describes a stack
operation in the format: "Push X" where X is the index of the node being pushed
onto the stack; or "Pop" meaning to pop one node from the stack.

Output Specification:
For each test case, print the postorder traversal sequence of the corresponding
tree in one line. A solution is guaranteed to exist. All the numbers must be
separated by exactly one space, and there must be no extra space at the end of
the line.

Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
Sample Output:
3 4 2 6 5 1
*/
#include <cstdio>
#include <stack>
using namespace std;
struct TNode
{
    int lf, rt;
} binT[32]{};
stack<int> myStk;
void postOrderTravs(int n);
int main()
{
    // freopen("E:\\in.txt", "r", stdin);

    int N, crtN, prevN, root;
    char buf[8], lastOp;
    scanf("%d ", &N);
    N *= 2;
    scanf("%s", buf);
    scanf("%d", &crtN);
    myStk.push(crtN);
    lastOp = 'u';
    root = crtN;
    for (int i = 1; i < N; ++i)
    {
        scanf("%s", buf);
        if (buf[1] == 'u')
        {
            scanf("%d", &crtN);

            if (lastOp == 'u')
            {
                /*push after push :
                    suggest now we are go down along the left subBranch*/
                prevN = myStk.top();
                binT[prevN].lf = crtN;
            }
            else
            {
                /*push after pop:
                    suggest crtNode is the RIGHT subTree of last Node;*/
                binT[prevN].rt = crtN;
                prevN = crtN;
            }
            myStk.push(crtN);
            lastOp = 'u';
        }
        else
        {
            prevN = myStk.top();
            myStk.pop();
            lastOp = 'o';
        }
    }
    while (!myStk.empty())
        myStk.pop();
    postOrderTravs(root);
    return 0;
}
void postOrderTravs(int n)
{
    static int fir = true;
    if (n > 0)
    {
        postOrderTravs(::binT[n].lf);
        postOrderTravs(::binT[n].rt);
        if (fir)
        {
            printf("%d", n);
            fir = false;
        }
        else
            printf(" %d", n);
    }
    return;
}
