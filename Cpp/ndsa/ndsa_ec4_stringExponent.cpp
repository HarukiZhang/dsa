#include<cstdio>

using namespace std;

char str[1000010];
int goodPrefix[1000010];

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    int idx, last;
    char ch;
    while (true){
        scanf("%c", &ch);
        if (ch == '.') break;

        idx = 0;
        last = goodPrefix[idx] = -1;
        str[idx] = ch;
        goodPrefix[++idx] = ++last;
        while (true){
            scanf("%c", &ch);
            if (ch == '\n') break;
            
            while (last >= 0 && ch != str[last]){
                last = goodPrefix[last];
            }
            str[idx] = ch;
            goodPrefix[++idx] = ++last;
        }
        int tmp = idx - goodPrefix[idx];
        if (goodPrefix[idx] != 0 && goodPrefix[idx] % tmp == 0)
            printf("%d\n", idx / tmp);
        else
            printf("1\n");
    }
}