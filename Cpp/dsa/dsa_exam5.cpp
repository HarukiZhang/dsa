/*描述
给出两个单词（开始单词和结束单词）以及一个词典。找出从开始单词转换到结束单词，所需要的最短转换序列。
转换的规则如下：
    1、每次只能改变一个字母
    2、转换过程中出现的单词(除开始单词和结束单词)必须存在于词典中

例如：
    开始单词为：hit
    结束单词为：cog
    词典为：[hot,dot,dog,lot,log,mot]
    那么一种可能的最短变换是： hit -> hot -> dot -> dog -> cog,
    所以返回的结果是序列的长度5；

注意：
    1、如果不能找到这种变换，则输出0；
    2、词典中所有单词长度一样；
    3、所有的单词都由小写字母构成；
    4、开始单词和结束单词可以不在词典中。

输入
    共两行，第一行为开始单词和结束单词（两个单词不同），以空格分开。
    第二行为若干的单词（各不相同），以空格分隔开来，表示词典。
    单词长度不超过5,单词个数不超过30。
输出
    输出转换序列的长度。

*/
#include<iostream>
#include<string>
#include<queue>
#include<utility>
using namespace std;
/*单词长度不超过5,单词个数不超过30。*/
string dict[32], WordS, WordE;
int WLen, DLen, min = 0xffff;
bool cList[32];
queue<pair<string, int> > myQue;

inline int isConvertable(const string& w1, const string& w2){
    int cnt = 0, idx;
    for (int i = 0; i < WLen; ++i){
        if (w1[i] != w2[i]){
            ++cnt;
            idx = i;            
        }
    }
    if (cnt > 1) return -1;
    return idx;
}

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    cin >> WordS >> WordE;
    WLen = WordS.length();
    DLen = 0;
    string word;
    while (cin >> word){
        dict[DLen] = word;
        cList[DLen] = true;
        ++DLen;
    }

    myQue.push(make_pair(WordS, 1));

    while (!myQue.empty()){

        string curW = myQue.front().first;
        int hrch = myQue.front().second;

        if (isConvertable(curW, WordE) != -1){
            cout << hrch + 1 << "\n" << flush;
            return 0;
        }

        for (int i = 0; i < DLen; ++i){
            
            if (cList[i]){
                if (isConvertable(curW, dict[i]) != -1){
                    myQue.push(make_pair(dict[i], hrch + 1));
                    cList[i] = false;
                }
            }
        }

        myQue.pop();
    }

    cout << 0 << "\n" << flush;
}

/*
样例输入
hit cog
hot dot dog lot log
样例输出
5
*/

/*
dog tab
lon len aem aec lom aoc mom acc mog fog aom cac ccc leg  cab log

10
*/

/*
dol dog
lon len aem aec lom aoc mom acc mog fog aom cac ccc leg  cab log lol

2
*/