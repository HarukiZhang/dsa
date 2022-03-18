#include <cstdio>
#include <cstring>

char text[100010] = {};
char doubled_chars[100010] = {};

int main () {
    fgets(text, 100010, stdin);
    int ln = strlen(text);
    char* pText = text;
    char* pDbd = doubled_chars;
    int countDbdChars = 0;
    int i = 0;
    for (; i < ln - 1; i++){
        char* isInDbd = NULL;
        for (int k = 0; k < strlen(doubled_chars); k++){
            isInDbd = strchr(doubled_chars, *(pText + i));
        }
        if (isInDbd != NULL) continue;
        int j = i + 1;
        for (; j < ln - 1; j++){
            if (*(pText + i) == *(pText + j)){
                *(pDbd + countDbdChars) = *(pText + i);
                *(pDbd + countDbdChars + 1) = '\0';
                countDbdChars++;
                break;
            }
        }
        if (j == ln - 1) {
            printf("%c", *(pText + i));
            return 0;
        }
    }
    if (i == ln - 1) printf("no");
}

/*
041:找第一个只出现一次的字符
查看提交统计提问
总时间限制: 1000ms 内存限制: 65536kB
描述
给定一个只包含小写字母的字符串，请你找到第一个仅出现一次的字符。如果没有，输出no。

输入
一个字符串，长度小于100000。
输出
输出第一个仅出现一次的字符，若没有则输出no。
样例输入
abcabd
样例输出
c
*/