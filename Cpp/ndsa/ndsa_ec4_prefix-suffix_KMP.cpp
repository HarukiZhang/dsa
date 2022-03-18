/*Problem name : Seek The Name, Seek The Fame;
描述
The little cat is so famous, that many couples tramp over hill and dale to Byteland, 
and asked the little cat to give names to their newly-born babies. They seek the name, 
and at the same time seek the fame. In order to escape from such boring job, the 
innovative little cat works out an easy but fantastic algorithm:

Step1. Connect the father's name and the mother's name, to a new string S.
Step2. Find a proper prefix-suffix string of S (which is not only the prefix, but also 
the suffix of S).

Example: Father='ala', Mother='la', we have S = 'ala'+'la' = 'alala'. Potential 
prefix-suffix strings of S are {'a', 'ala', 'alala'}. Given the string S, could you 
help the little cat to write a program to calculate the length of possible 
prefix-suffix strings of S? (He might thank you by giving your baby a name:)

输入
The input contains a number of test cases. Each test case occupies a single line that 
contains the string S described above.

Restrictions: Only lowercase letters may appear in the input. 
1 <= Length of S <= 400000.
输出
For each test case, output a single line with integer numbers in increasing order, 
denoting the possible length of the new baby's name.
样例输入
ababcababababcabab
aaaaa
样例输出
2 4 9 18
1 2 3 4 5*/
#include<cstdio>
#include<cstring>

char buf[100];
int next[100];
int ans[100];

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int idx, last;

    while (scanf("%s", buf) != EOF){
        idx = 0;
        last = next[idx] = -1;
        while (buf[idx]){
            while (last >= 0 && buf[idx] != buf[last])
                last = next[last];
            next[++idx] = ++last;
        }
        int i = idx;
        int j = 0;
        while (i > 0)
                i = ans[j++] = next[i];
        j -= 2;//ignore -1 and 0;
        while (j >= 0)
            printf("%d ", ans[j--]);
        printf("%d\n", idx);
    }
}

/*
0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17       index
a  b  a  b  c  a  b  a  b  a  b  a  b  c  a  b  a  b       origin
d  0  0  1  2  0  1  2  3  4  3  4  3  4  5  6  7  8  9    prefix

Example:
    check prefix[18] == 9, which means [0,8] == [9,17];
    within [0,8], we could find [0,3] == [5,8] according to prefix[9];
    because [0,8] == [9,17], then we know [0,3] == [5,8] == [9,12] == [14,17];
*/
