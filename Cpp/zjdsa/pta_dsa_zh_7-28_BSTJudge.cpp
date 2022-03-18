#include <cstdio>
#include <stack>

constexpr int btLen = 1010;
struct TNode
{
    int val, lf, rt;
};
TNode binTree[btLen];
std::stack<int> preot;

void postorderTraverse(int crtN);
void postorderTraverse_Rv(int crtN);

int main()
{
    // freopen("E:\\in.txt","r",stdin);
    int N, ptr, idx;
    scanf("%d", &N);
    /*initiate binTree array;*/
    for (int i = 0; i < N; ++i)
        binTree[i].lf = binTree[i].rt = -1;
    /*biuld BinTree in form of static list table;*/
    scanf("%d", &binTree[0].val);
    for (int i = 1; i < N; ++i)
    {
        scanf("%d", &binTree[i].val);
        ptr = 0;
        while (true)
        {
            if (binTree[i].val < binTree[ptr].val)
            {
                if (binTree[ptr].lf != -1)
                    ptr = binTree[ptr].lf;
                else
                {
                    binTree[ptr].lf = i;
                    break;
                }
            }
            else if (binTree[ptr].rt != -1)
                ptr = binTree[ptr].rt;
            else
            {
                binTree[ptr].rt = i;
                break;
            }
        }
    }
    bool flag = true, flagR = true;
    /*preorder traversal LR;*/
    ptr = idx = 0;
    while (ptr != -1 || !preot.empty())
    {
        while (ptr != -1)
        {
            /*visit*/
            if (binTree[ptr].val != binTree[idx++].val)
            {
                flag = false;
                ptr = -1;
                while (!preot.empty())
                    preot.pop();
                break;
            }
            if (binTree[ptr].rt != -1)
                preot.push(binTree[ptr].rt);
            ptr = binTree[ptr].lf;
        }
        if (!preot.empty())
        {
            ptr = preot.top();
            preot.pop();
        }
    }
    if (!flag)
    {
        /*preorder traverse reversed-image;*/
        ptr = idx = 0;
        while (ptr != -1 || !preot.empty())
        {
            while (ptr != -1)
            {
                /*visit*/
                if (binTree[ptr].val != binTree[idx++].val)
                {
                    flagR = false;
                    ptr = -1;
                    while (!preot.empty())
                        preot.pop();
                    break;
                }
                if (binTree[ptr].lf != -1)
                    preot.push(binTree[ptr].lf);
                ptr = binTree[ptr].rt;
            }
            if (!preot.empty())
            {
                ptr = preot.top();
                preot.pop();
            }
        }
    }
    if (flag)
    {
        printf("YES\n");
        postorderTraverse(0);
    }
    else if (flagR)
    {
        printf("YES\n");
        postorderTraverse_Rv(0);
    }
    else
        printf("NO\n");
}

void postorderTraverse(int crtN)
{
    static bool firChar = true;
    if (crtN != -1)
    {
        if (::binTree[crtN].lf != -1)
            postorderTraverse(::binTree[crtN].lf);
        if (::binTree[crtN].rt != -1)
            postorderTraverse(::binTree[crtN].rt);
        if (firChar)
        {
            printf("%d", ::binTree[crtN].val);
            firChar = false;
        }
        else
            printf(" %d", ::binTree[crtN].val);
    }
}

void postorderTraverse_Rv(int crtN)
{
    static bool firCharR = true;
    if (crtN != -1)
    {
        if (::binTree[crtN].rt != -1)
            postorderTraverse_Rv(::binTree[crtN].rt);
        if (::binTree[crtN].lf != -1)
            postorderTraverse_Rv(::binTree[crtN].lf);
        if (firCharR)
        {
            printf("%d", ::binTree[crtN].val);
            firCharR = false;
        }
        else
            printf(" %d", ::binTree[crtN].val);
    }
}
