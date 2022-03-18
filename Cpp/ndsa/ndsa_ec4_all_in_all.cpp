/*描述
你设计了一个新的加密技术，可以用一种聪明的方式在一个字符串的字符间插入随机的字符串从而对信息
进行编码。由于专利问题，我们将不会详细讨论如何在原有信息中产生和插入字符串。不过，为了验证你
的方法，有必要写一个程序来验证原来的信息是否全在最后的字符串之中。

给定两个字符串s和t，你需要判断s是否是t的“子列”。也就是说，如果你去掉t中的某些字符，剩下字符
将连接而成为s。

输入
输入包括多个测试样例。每一个都是由空格分隔的由字母数字ASCII字符组成的两个特定的字符串s和t。
s和t的长度不超过100000。
输出
对于每个测试样例，如果s是t的“子列”，则输出”Yes”，否则输出”No”
样例输入
sequence subsequence
person compression
VERDI vivaVittorioEmanueleReDiItalia
caseDoesMatter CaseDoesMatter
样例输出
Yes
No
Yes
No
来源
Ulm Local 2002*/
#include<cstdio>

using namespace std;

char origin[100'010];

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    int ptr, ch;
    while (true) {
        ptr = 0;
        origin[ptr++] = (char)getchar();
        if (feof(stdin)) break;
        do {
            origin[ptr++] = (char)getchar();
        } while (origin[ptr] != ' ');
        origin[ptr] = '\0';
        ptr = 0;
        do {
            ch = getchar();
            if (origin[ptr] && origin[ptr] == ch) ++ptr;
        } while (ch != '\n' && ch != EOF);
        if (origin[ptr] == '\0') printf("Yes\n");
        else printf("No\n");
    }
}