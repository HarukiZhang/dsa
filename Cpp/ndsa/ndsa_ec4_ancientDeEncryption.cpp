/*描述
古罗马帝国有一个拥有各种部门的强大政府组织。其中一个部门就是保密服务部门。为了保险起见，
在省与省之间传递的重要文件中的大写字母是加密的。当时最流行的加密方法是替换和重新排列。

替换方法是将所有出现的字符替换成其它的字符。有些字符会替换成它自己。例如：替换规则可以是
将'A' 到 'Y'替换成它的下一个字符，将'Z'替换成 'A'，如果原词是 "VICTORIOUS" 则它变成 
"WJDUPSJPVT"。

排列方法改变原来单词中字母的顺序。例如：将顺序例如将顺序 < 2 1 5 4 3 7 6 10 9 8 > 应用
到 "VICTORIOUS" 上，则得到"IVOTCIRSUO"。

人们很快意识到单独应用替换方法或排列方法加密，都是很不保险的。但是如果结合这两种方法，在
当时就可以得到非常可靠的加密方法。所以，很多重要信息先使用替换方法加密，再将加密的结果用
排列的方法加密。用两种方法结合就可以将"VICTORIOUS" 加密成"JWPUDJSTVP"。

考古学家最近在一个石台上发现了一些信息。初看起来它们毫无意义，所以有人设想它们可能是用替
换和排列的方法被加密了。人们试着解读了石台上的密码，现在他们想检查解读的是否正确。他们需
要一个计算机程序来验证，你的任务就是写这个验证程序。

输入
输入有两行。第一行是石台上的文字。文字中没有空格，并且只有大写英文字母。第二行是被解读出
来的加密前的文字。第二行也是由大写英文字母构成的。
两行字符数目的长度都不超过100。
输出
如果第二行经过某种加密方法后可以产生第一行的信息，输出 "YES"，否则输出"NO"。
样例输入
JWPUDJSTVP
VICTORIOUS
样例输出
YES
来源
2159

思路：
    一个字符串可以按照上述“替换”和“重排序”的方法加密，并能够解密的充分必要条件是：
        同一个串内的不同字符的个数，在加密前、后要保持不变；*/
#include<cstdio>
#include<algorithm>

using namespace std;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    char bufA[128]{}, bufG[128]{};
    int cntA[26]{}, cntG[26]{};
    int idx = 0;
    scanf("%s", bufA);
    while (bufA[idx])
        ++cntA[bufA[idx++] - 'A'];
    idx = 0;
    scanf("%s", bufG);
    while (bufG[idx]){
        ++cntG[bufG[idx++] - 'A'];
    }
    /*In order to differentiate different letters to constitute a word,
    in the one encryption, two different letters can not be transformed 
    to one same letter; otherwise, the encryption is not reversible;
    
    Therefore, no matter the rule of substitution, and re-ordering,
    the number of each different char within one string should be UNCHANGED
    before or after encryption;*/
    
    sort(cntA, cntA + 26);
    sort(cntG, cntG + 26);

    for (int i = 0; i < 26; ++i){
        if (cntA[i] != cntG[i]){
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}