#include<iostream>
#include<stack>
using namespace std;

void infix_to_postfix(char* infix, char* postfix){
    stack<char> optrStk;
    int iInfx = 0, iPost = 0;
    char tmp;
    while (infix[iInfx]){
        switch(infix[iInfx]){
        case '+' :
        case '-' :
            while (!optrStk.empty() && optrStk.top() != '('){
                postfix[iPost++] = optrStk.top();
                optrStk.pop();
            }
            optrStk.push(infix[iInfx]);
            break;
        case '*' :
        case '/' :
            /*left id prior to right;*/
            while (!optrStk.empty() && ((tmp = optrStk.top()) == '*' || tmp == '/')){
                postfix[iPost++] = tmp;
                optrStk.pop();
            }
            //no need break;
        case '(' :
            optrStk.push(infix[iInfx]);
            break;
        case ')' :
            while (optrStk.top() != '(' ){
                postfix[iPost++] = optrStk.top();
                optrStk.pop();
            }
            optrStk.pop();
            break;
        case ' ' :
        default  :
            postfix[iPost++] = infix[iInfx];
            break;
        }
        ++iInfx;
    }
    while (!optrStk.empty()){
        postfix[iPost++] = optrStk.top();
        optrStk.pop();
    }
    postfix[iPost] = 0;
    return;
}

int eval_num(char* buf, int& idx){
    int unit = 1, res = 0, stp = idx;
    for (; buf[idx] >= '0' && buf[idx] <= '9'; ++idx);
    for (int i = idx - 1; i >= stp; --i){
        res += unit * (int)(buf[i] - '0');
        unit *= 10;
    }
    return res;
}

void skipws(char* buf, int& i){
    while(buf[i]==' ')++i;
    return;
}

int eval_postfix_expr(char* expr){
    stack<int> numStk;
    int tmp, res, i = 0;
    while (expr[i]){
        switch(expr[i++]){
        case '+' :
            tmp = numStk.top();
            numStk.pop();
            numStk.top() += tmp;
            break;
        case '-' :
            tmp = numStk.top();
            numStk.pop();
            numStk.top() -= tmp;
            break;
        case '*' :
            tmp = numStk.top();
            numStk.pop();
            numStk.top() *= tmp;
            break;
        case '/' :
            tmp = numStk.top();
            numStk.pop();
            numStk.top() /= tmp;
            break;
        case ' ' :break;
        default  :
            --i;
            tmp = eval_num(expr, i);
            numStk.push(tmp);
            break;
        }
    }
    res = numStk.top();
    numStk.pop();
    return res;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);

    char buf0[64], buf1[64];
    cin.getline(buf0, 63);
    infix_to_postfix(buf0, buf1);
    cout << buf1 << endl;
    cout << eval_postfix_expr(buf1);
    return 0;
}

/*
2 * (9 + 6 / 3 - 5) + 4
postfix:
2  9  6  3 /+ 5- * 4+
resutlt:
16
*/