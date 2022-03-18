/*描述
在这个问题中，将用英语给你一个或多个整数。你的任务是将这些数字转换成整型表示。数字范围
从-999,999,999到999,999,999.下面是你的程序必须考虑的详尽的英语单词表：

negative, zero, one, two, three, four,five, six, seven, eight, nine, ten, eleven, 
twelve, thirteen, fourteen,fifteen, sixteen, seventeen, eighteen, nineteen, twenty, 
thirty, forty, fifty,sixty, seventy, eighty, ninety, hundred, thousand, million

输入
输入包括多个样例，注意：

1.负数前面有词negative

2.当能用thousand的时候，将不用hundred。例如1500将写为"one thousand five hundred",
而不是"fifteen hundred".

输入将以一个空行结束
输出
输出将是每一个单独一行，每一个后面一个换行符
样例输入
six
negative seven hundred twenty nine
one million one hundred one
eight hundred fourteen thousand twenty two

样例输出
6
-729
1000101
814022
来源
CTU Open 2004,UVA 486

Logic:
    Relate the hash value of each English word to its arithmetic true value
        and store them in a map structure (binary tree);
    Regarding to the order of input, it is assured that there always be at least one
    factor between two words that can be regarded as a unit number;
    Unit number includes: hundred, thousand, million;
    Factors includes all words whose true value is lesser than 100;
    Note: factor can be two words, ie, twenty four;
        under such circumstance, we could set a condition that 
        each time when encountering a non-unit word, it is always added to tmp;
        only when encountering a unit word, we multiply it with the tmp;
    */

#include<iostream>
#include<cstring>
#include<map>

using namespace std;

map<unsigned int, int> myMap;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    const char words[512] = 
        "negative, zero, one, two, three, four, five, six, seven, eight, nine, ten, \
eleven, twelve, thirteen, fourteen, fifteen, sixteen, seventeen, eighteen, nineteen, \
twenty, thirty, forty, fifty, sixty, seventy, eighty, ninety, hundred, thousand, \
million,";
    int nums[64]{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 
        18, 19, 20, 30, 40, 50, 60, 70, 80, 90, 100, 1000, 1000000};

    int hashV, idx = 0, len, nidx = 0;
    len = strlen(words);
    while (words[idx]){
        hashV = words[idx++];
        do {
            hashV = (hashV << 1) + words[idx++];
        } while (words[idx] != ',');
        idx = idx + 2;
        myMap.insert(make_pair(hashV, nums[nidx++]));
    }
    bool neg;
    int trueVal, tmp, crtNum;
    char buf[512];
    while (cin.getline(buf, 510)){

        if (!buf[0]) break;

        neg = false;
        trueVal = 0;
        idx = 0;
        tmp = 0;
        while (buf[idx]){
            hashV = buf[idx++];
            while (buf[idx] && buf[idx] != ' '){
                hashV = (hashV << 1) + buf[idx++];
            }
            if (buf[idx]) ++idx;
            crtNum = myMap[hashV];

            switch (crtNum){
            case -1 : neg = true; break;
            case 100 : tmp *= crtNum; break;
            case 1000 :
            case 1000000 :
                tmp *= crtNum;
                trueVal += tmp;
                tmp = 0;
                break;
            default: tmp += crtNum; break;
            }
        }
        trueVal += tmp;

        if (neg) trueVal *= -1;
        cout << trueVal << endl;
    }
}


/*
one hundred twenty three million 
    four hundred fifty six thousand 
        seven hundred eighty nine
123'456'789
*/