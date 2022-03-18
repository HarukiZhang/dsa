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

struct Elem {
    int rd, retVal, locVal_lf, locVal_rt;
    char oprt;
    Elem(int rd_) : rd{rd_} {}
};

stack<Elem> nexus;
string str;
int ptr;

int nonrec_optm(){
    char ch;
    int retV;
    nexus.push(Elem(8));
    do {
        nexus.push(Elem(1));
        do {//label_3;
            nexus.push(Elem(4));
            do {//label_6;
                ch = str[ptr];
                
    /*Uncomplete!!
    Dont know how to do;*/
                
                
                if (ch == '('){
                    ++ptr;
                    nexus.push(Elem(7));
                }
                if (str[ptr] == '*'){
                    ++ptr;
                    nexus.push(Elem(5));
                }
            } while(true);

        } while (true);

    } while (nexus.top().rd != 8);
}

/*Non-recursive function*/
int nonrec_rplc_1(){
    char chT;
    int rvT;
    Elem elemT{8, 0, 0, 0};// rd == 8, for stop;
    nexus.push(elemT);//evalExpr() body, which should be operated after label_1;
label_0://evalExpr() initial;
    elemT.rd = 1;//evalTerm() body;
    nexus.push(elemT);
label_3://evalTerm() initial;
    elemT.rd = 4;//evalFactor() body;
    nexus.push(elemT);
label_6://evalFactor() initial;
    chT = str[ptr];
    if (chT == '('){
        elemT.rd = 7;
        ++ptr;
        nexus.push(elemT);
        goto label_0;
label_7:
        rvT = nexus.top().retVal;
        nexus.pop();
        nexus.top().locVal_lf = rvT;
        ++ptr;
    }
    else if (chT <= '9'){
        nexus.top().locVal_lf = extract(str, ptr);
    }
    else {
        nexus.top().locVal_lf = static_cast<int>(chT - 64);//'A' == 65;
        ++ptr;
    }
    nexus.top().retVal = nexus.top().locVal_lf;//prepare for value return;
    goto label_OA;

label_1:
    rvT = nexus.top().retVal;
    nexus.pop();
    nexus.top().locVal_lf = rvT;
    nexus.top().oprt = str[ptr];
    while (nexus.top().oprt == '+' || nexus.top().oprt == '-'){
        elemT.rd = 2;
        ++ptr;
        nexus.push(elemT);
        goto label_3;
label_2:
        rvT = nexus.top().retVal;
        nexus.pop();
        nexus.top().locVal_rt = rvT;//must return to rt value;
        if (nexus.top().oprt == '+'){
            nexus.top().locVal_lf += nexus.top().locVal_rt;
        }
        else {
            nexus.top().locVal_lf -= nexus.top().locVal_rt;
        }
        nexus.top().oprt = str[ptr];
    }
    nexus.top().retVal = nexus.top().locVal_lf;
    goto label_OA;

label_4://within evalTerm();
    rvT = nexus.top().retVal;
    nexus.pop();
    nexus.top().locVal_lf = rvT;
    while (str[ptr] == '*'){
        elemT.rd = 5;//evalFactor() body;
        ++ptr;
        nexus.push(elemT);
        goto label_6;
label_5:
        rvT = nexus.top().retVal;
        nexus.pop();
        nexus.top().locVal_rt = rvT;//must return to rt value;
        nexus.top().locVal_lf *= nexus.top().locVal_rt;
    }
    nexus.top().retVal = nexus.top().locVal_lf;//prepare for value return;
    // goto label_OA;

label_OA:
    switch (nexus.top().rd){
    case 1 :
        goto label_1;
        break;
    case 2 :
        goto label_2;
        break;
    case 3 :
        break;
    case 4 :
        goto label_4;
        break;
    case 5 :
        goto label_5;
        break;
    case 6 :
        break;
    case 7 :
        goto label_7;
        break;
    case 8 :
        rvT = nexus.top().retVal;
        nexus.pop();
        return rvT;
    default :
        break;  
    }
    return -1;
}

/*Recursive function family*/
int evalFactor(string& s, int& idx);
int evalTerm(string& s, int& idx);
int evalExpr(string& s, int& idx){
/*label_0*/
    int val_expr = evalTerm(s, idx);
    /*label_1*/
    char ch = s[idx];
    while (ch == '+' || ch == '-') {
        /*label_2*/
        if (ch == '+')
            val_expr += evalTerm(s, ++idx);
        else
            val_expr -= evalTerm(s, ++idx);
        ch = s[idx];
    }
    return val_expr;
}
int evalTerm(string& s, int& idx){
/*label_3*/
    int val_term = evalFactor(s, idx);
    /*label_4*/
    while (s[idx] == '*'){
        /*label_5*/
        val_term *= evalFactor(s, ++idx);
    }
    return val_term;
}
int evalFactor(string& s, int& idx){
/*label_6*/
    char ch = s[idx];
    int val_factor;
    if (ch == '('){
        val_factor = evalExpr(s, ++idx);
        /*label_7*/
        ++idx;//for ')';
    }
    else if (ch >= '0' && ch <= '9')
        val_factor = extract(s, idx);
    else {// when ch == 'a'...'Z';
        val_factor = static_cast<int>(ch - 64);//'A' == 65;
        ++idx;
    }
    return val_factor;
}


int main(){
    freopen("E:\\Downloads\\in.txt", "r", stdin);

    string buf;
    int n;
    cin >> n >> ws;
    for (int i = 0; i < n; ++i){
        int val[2];
        for (int j = 0; j < 2; ++j){
            int idx = 0;
            getline(cin, buf);
            input(buf, str);
            val[j] = nonrec_rplc_1();
            str.clear();
            ptr = 0;
        }
        if (val[0] == val[1])
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}