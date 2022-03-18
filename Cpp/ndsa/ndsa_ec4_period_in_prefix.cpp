#include <cstdio>

using namespace std;

constexpr int kMax = 1000000;
char str[kMax];
int next[kMax];

int main()
{
    int len, nCase = 1, idx, last;
    while (true)
    {
        scanf("%d", &len);
        if (len == 0)
            return 0;
        idx = 0;
        scanf("%c", &str[idx]); // ignore '\n';

        printf("Test case #%d\n", nCase++);

        fgets(str, kMax, stdin);
        next[0] = -1;
        last = -1;
        while (idx < len)
        {
            while (last >= 0 && str[idx] != str[last])
                last = next[last];
            next[++idx] = ++last;
            /*The len of prefix is just equal to the idx of next arr;
                Only when total len can be divisable by len of prefix,
                the str is repeatedly measurable;*/
            if (next[idx] > 0 && idx % (idx - next[idx]) == 0)
            {
                printf("%d %d\n", idx, idx / (idx - next[idx]));
            }
        }
        printf("\n");
    }
}