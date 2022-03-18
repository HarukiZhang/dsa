#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

struct Factor {
    int coef;
    int expo;
    char vari;

    bool operator<(Factor& v){
        return vari < v.vari;
    }
    bool operator==(Factor& v){
        return (vari == v.vari && expo == v.expo && coef == v.coef);
    }
};

struct Term {
    int coef;
    int nVari;
    Factor factors[4];

    bool operator==(Term& t){
        if (nVari != t.nVari)
            return false;
        for (int i = 0; i < nVari; ++i){
            if (factors[i] != t.factors[i])
                return false;
        }
        return true;
    }
};

void evalFactor(string& s, Factor& f, int& idx);
void evalTerm(string& s, Term& t, int& idx);
void evalExpr(string& s, int& idx);

string buff;
string expr;

vector<Term> termVec;
stack<string> buffStk;

void evalExpr(string& s, int& idx){
    Term t1;
    evalTerm(s, t1, idx);
    termVec.push_back(t1);
    while (true){
        char ch = s[idx];
        if (ch == '+' || ch == '-'){
            Term t2;
            evalTerm(s, t2, idx);
            termVec.push_back(t2);
        }
        else break;
    }
}

void evalTerm(string& s, Term& t, int& idx){
    Factor f1;
    evalFactor(s, f1, idx);
    
}


int main(){
    sizeof(Factor);
    sizeof(Term);

    freopen("E:\\Downloads\\in.txt", "r", stdin);
    int n;
    cin >> n >> ws;
    for (int i = 0; i < n; ++i){
        getline(cin, buff);
        char ch;
        for (int j = 0; j < buff.length(); ++j){
            ch = buff[j];
            if (ch != '\011' && ch != '\040')
                expr.push_back(ch);
        }
        cout << expr << endl;
    }
    return 0;
}