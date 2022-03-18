/*6:大整数乘法
描述
求两个不超过200位的非负整数的积。

输入
有两行，每行是一个不超过200位的非负整数，没有多余的前导0。
输出
一行，即相乘后的结果。结果里不能有多余的前导0，即如果结果是342，那么就不能输出为0342。

提示
30%的数据，输入的两个整数不超过8位。
*/
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

struct HugeInt
{
    /*Each line is a nonnegative integer with no more than 200 digits.*/
    char num[510]{};
    short dig;
    HugeInt(){}
    HugeInt(const HugeInt& hn): dig(hn.dig){
        for (int i = 0; i < dig; ++i)
            num[i] = hn.num[i];
        num[dig] = 0;
    }
    void input(){
        scanf("%s", num);
        dig = strlen(num);
        reverse(num, num + dig);
    }
    void output(){
        for (int i = dig - 1; i >= 0; --i)
            printf("%c", num[i]);
        printf("\n");
    }
    HugeInt operator+(const HugeInt& hn){
        HugeInt tmp;
        int i = 0;
        bool c = false;
        while (i < dig && i < hn.dig){
            tmp.num[i] = num[i] - '0' + hn.num[i] - '0';
            if (c)
                tmp.num[i] += '\1';
            if (tmp.num[i] >= '\12'){
                tmp.num[i] -= '\12';
                c = true;
            }
            else c = false;
            tmp.num[i] += '0';
            ++i;
        }
        while (i < dig){
            tmp.num[i] = num[i];
            if (c)
                tmp.num[i] += '\1';
            if (tmp.num[i] >= '\72'){
                tmp.num[i] -= '\72';
                c = true;
            }
            else c = false;
            ++i;
        }
        while (i < hn.dig){
            tmp.num[i] = hn.num[i];
            if (c)
                tmp.num[i] += '\1';
            if (tmp.num[i] >= '\72'){
                tmp.num[i] -= '\72';
                c = true;
            }
            else c = false;
            ++i;
        }
        if (c)
            tmp.num[i++] = '1';
        tmp.dig = i;
        return tmp;
    }
    void operator*(const HugeInt& hn){
        HugeInt tmp;
        int i, j, k;
        char carry = '\0', addend;
        for (i = 0; i < dig; ++i){
            addend = num[i] - '0';
            if (addend == 0)
                continue;
            for (j = 0; j < hn.dig; ++j){
                k = i + j;
                tmp.num[k] += (hn.num[j] - '0') * addend;
                if (carry)
                    tmp.num[k] += carry;
                if (tmp.num[k] >= '\12'){
                    carry = tmp.num[k] / '\12';
                    tmp.num[k] -= carry * '\12';
                }
                else carry = '\0';
            }
            while (carry){
                k = i + j;
                tmp.num[k] += carry;
                if (tmp.num[k] >= '\12'){
                    tmp.num[k] -= '\12';
                    carry = '\1';
                }
                else carry = '\0';
                ++j;
            }
        }
        if (carry){
            k = i + j - 1;
            tmp.num[k] = carry;
        }
        tmp.num[++k] = 0;
        tmp.dig = k;
        for (i = 0; i < tmp.dig; ++i)
            tmp.num[i] += '0';
        tmp.output();
        return;
    }
};

HugeInt a, b;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    a.input();
    b.input();
    a * b;
}

/*
样例输入
12345678900
98765432100
样例输出
1219326311126352690000
*/