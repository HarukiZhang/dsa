#include<cstdio>

using namespace std;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    int counter[128]{};
    int n;
    char ch;
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i){
        while (scanf("%c", &ch) != EOF && ch != '\n')
            ++counter[ch];
        scanf("%c", &ch);//for empty row;
        int max = 0;
        for (int j = 'a'; j <= 'z'; ++j){
            if (counter[j] > max){
                ch = (char)j;
                max = counter[j];
            }
            counter[j] = 0;//reset counter;
        }
        printf("%c %d\n", ch, max);
    }
    fclose(stdin);
    return 0;
}