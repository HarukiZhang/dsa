/*Problem name : Seek The Name, Seek The Fame;*/
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 1000090
#define base 161
typedef unsigned long long ull;
ull p[N], hs[N];
char str[N];
ull gethash(int l, int r)
{
    return hs[r] - p[r - l + 1] * hs[l - 1];
}

void cal()
{
    hs[0] = 0;
    int len = strlen(str + 1);
    for (int i = 1; i <= len; i++)
        hs[i] = hs[i - 1] * base + str[i];
}

void slove()
{
    cal();
    int len = strlen(str + 1);
    int res = 0, f = 0;
    for (int i = 1; i <= len; i++)
    {
        if (gethash(1, 1 + i - 1) == gethash(len - i + 1, len))
            if (!f)
            {
                cout << i;
                f = 1;
            }
            else
                cout << " " << i;
    }
    cout << endl;
}

int main()
{

    p[0] = 1;
    for (int i = 1; i <= N; i++)
        p[i] = p[i - 1] * base;

    while (scanf("%s", str + 1) != EOF)
    {
        slove();
    }
}