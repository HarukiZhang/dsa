#include<iostream>
#include<stack>
#include<string>

using namespace std;

void input(string& buf, string& s){
    char ch;
    for (int i = 0; i < buf.length(); ++i){
        ch = buf[i];
        if (ch != '\011' && ch != '\040')
            s.push_back(ch);
    }
}

int extract(string& s, int& idx);

int evalFactor(string& s, int& idx);
int evalTerm(string& s, int& idx);

int evalExpr(string& s, int& idx){
    int val_expr = evalTerm(s, idx);
    while (1) {
        char ch = s[idx];
        if (ch == '+' || ch == '-'){
            if (ch == '+')
                val_expr += evalTerm(s, ++idx);
            else
                val_expr -= evalTerm(s, ++idx);
        }
        else break;
    }
    return val_expr;
}

int evalTerm(string& s, int& idx){
    int val_term = evalFactor(s, idx);
    while (1){
        if (s[idx] == '*')
            val_term *= evalFactor(s, ++idx);
        else break;
    }
    return val_term;
}

int evalFactor(string& s, int& idx){
    char ch = s[idx++];
    int val_factor;
    if (ch == '('){
        val_factor = evalExpr(s, idx);
        ++idx;//for ')';
    }
    else if (ch >= '0' && ch <= '9')
        val_factor = extract(s, --idx);
    else// when ch == 'a'...'Z';
        val_factor = static_cast<int>(ch - 64);//'A' == 65;
    return val_factor;
}

int extract(string& s, int& idx){
    int val_extr = 0, i_tmp = idx + 1, base = 1;
    for (; s[i_tmp] >= '0' && s[i_tmp] <= '9'; ++i_tmp)
        base *= 10;
    for (; idx < i_tmp; ++idx){
        val_extr += static_cast<int>(s[idx] - '0') * base;
        base /= 10;
    }
    return val_extr;
}

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    string buf, sta;
    int n;
    cin >> n >> ws;
    for (int i = 0; i < n; ++i){
        int val[2];
        for (int j = 0; j < 2; ++j){
            int idx = 0;
            getline(cin, buf);
            input(buf, sta);
            val[j] = evalExpr(sta, idx);
            sta.clear();
        }
        if (val[0] == val[1])
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}

/*
描述
判断两个表达式在数学上是否是等价的。
输入
第一行：N（1<=N<=20），表示测试数据组数。
接下来每组测试数据包括两行，每行包括一个数学表达式，每个表达式的长度不超过80个字符。输入数据没有空行。

一个表达式可能包括：
单个英文字母表示的变量（区分大小写）
数字（只有一位数）
配对的括号
运算符加+、减-、乘*
任意数量的空格或tab（可能出现在表达式中间的任何位置）

注意：表达式保证是语法正确的，且所有运算符的优先级相同，运算次序从左至右。变量的系数和指数保证不超过16位整数。
输出
对每个测试数据，输出一行：等价则输出“YES”，不等价则输出“NO”。
样例输入
3
(a+b-c)*2
(a+a)+(b*2)-(3*c)+c
a*2-(a+c)+((a+c+e)*2)
3*a+c+(2*e)
(a-b)*(a-b)
(a*a)-(2*a*b)-(b*b)
样例输出
YES
YES
NO
*/