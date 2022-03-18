#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

void infix_to_prefix(char* infixExpr, char* resBuff){
    stack<char> myStk;
    stack<char> print;
    char tmp, crtChar;
    for (int i = strlen(infixExpr) - 1; i >= 0; --i){
        crtChar = infixExpr[i];
        switch (crtChar){
        case '+' :
        case '-' :
            print.push(' ');
            while (!myStk.empty() && ( ( tmp = myStk.top() ) == '*' || tmp == '/') ){
                myStk.pop();
                print.push(tmp);
            }
            myStk.push(crtChar);
            break;
        case '*' :
        case '/' :
            print.push(' ');
        case ')' :
            myStk.push(crtChar);
            break;
        case '(' :
            tmp = myStk.top();//there must be at least a ')' in the stack;
            while (tmp != ')'){
                print.push(tmp);
                myStk.pop();
                tmp = myStk.top();
            }
            myStk.pop();
            break;
        default  :// 0 ~ 9;
            if (crtChar >= '0' && crtChar <= '9')
                print.push(crtChar);
            else {
                cerr << "invalid character input;" << endl;
                return;
            }
            break;
        }
    }
    while (!myStk.empty()){
        print.push(myStk.top());
        myStk.pop();
    }
    int i;
    for (i = 0; !print.empty(); ++i){
        resBuff[i] = print.top();
        print.pop();
    }
    resBuff[i] = 0;
    return;
}

int eval_num(char* buff, int& idx){
    int res = 0, stp = idx;
    while (buff[idx] >= '0' && buff[idx] <= '9') ++idx;
    int unit = 1;
    for (int i = idx - 1; i >= stp; --i){
        res += unit * (int)(buff[i] - '0');
        unit *= 10;
    }
    return res;
}

int eval_prefix_expr(char* prefixExpr){
    static int i = 0;
    int res = 0;
    while (prefixExpr[i] && prefixExpr[i] == ' ') ++i;
    switch (prefixExpr[i++]){
    case '+' :
        res = eval_prefix_expr(prefixExpr);
        res += eval_prefix_expr(prefixExpr);
        break;
    case '-' :
        res = eval_prefix_expr(prefixExpr);
        res -= eval_prefix_expr(prefixExpr);
        break;
    case '*' :
        res = eval_prefix_expr(prefixExpr);
        res *= eval_prefix_expr(prefixExpr);
        break;
    case '/' :
        res = eval_prefix_expr(prefixExpr);
        res /= eval_prefix_expr(prefixExpr);
        break;
    default  :
        --i;
        res = eval_num(prefixExpr, i);
        break;
    }
    return res;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);

    char buf[64], buf1[64];
    for (int i = 0; cin >> ws >> buf[i] >> ws; ++i);
    infix_to_prefix(buf, buf1);
    cout << buf1 << endl;
    cout << eval_prefix_expr(buf1);
    return 0;
}

/*
5 * (1 + 3) / 7 - 6 / 2 
*/