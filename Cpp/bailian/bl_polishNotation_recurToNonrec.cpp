#include<iostream>
#include<stack>

using namespace std;

double evalPolNota(){
/*label_0:*/
    char oprt, test;
    double opd_lf, opd_rt, res;
    cin >> ws;
    test = cin.peek();
    if (test >= '0'){
        cin >> res >> ws;
    }
    else {
        cin >> oprt >> ws;
        opd_lf = evalPolNota();
        /*label_1:*/
        opd_rt = evalPolNota();
        /*label_2:*/
        switch (oprt){
        case '+' :
            res = opd_lf + opd_rt;
            break;
        case '-' :
            res = opd_lf - opd_rt;
            break;
        case '*' :
            res = opd_lf * opd_rt;
            break;
        case '/' :
            res = opd_lf / opd_rt;
            break;
        default :
            break;
        }
    }
    return res;
}

struct Elem {
    int rd;
    char ch;
    double retVal;
};

class Nonrec {
    stack<Elem> nexus;
public:
    Nonrec() = default;
    double loopReplace();
};

int main(){
    freopen("E:\\Downloads\\in.txt", "r", stdin);
    Nonrec nc;
    // cout << evalPolNota() << endl;
    cout << nc.loopReplace() << endl;
}

double Nonrec::loopReplace(){
    Elem tmp { 3, '\0', 0.0 };
    double dbt;
    nexus.push(tmp);
    do {
        cin >> ws;
        while (cin.peek() < '0'){
            cin >> nexus.top().ch >> ws;
            Elem tmp { 1, '\0', 0.0 };
            nexus.push(tmp);
        }
        cin >> nexus.top().retVal >> ws;
        while (nexus.top().rd == 2){
            dbt = nexus.top().retVal;
            nexus.pop();

            switch (nexus.top().ch){
            case '+':
                nexus.top().retVal += dbt;
                break;
            case '-':
                nexus.top().retVal -= dbt;
                break;
            case '*':
                nexus.top().retVal *= dbt;
                break;
            case '/':
                nexus.top().retVal /= dbt;
                break;
            default :
                break;
            }
        }
        if (nexus.top().rd == 1){
            dbt = nexus.top().retVal;
            nexus.pop();
            nexus.top().retVal = dbt;

            Elem tmp { 2, '\0', 0.0 };
            nexus.push(tmp);
        }
    } while (nexus.top().rd != 3);
    dbt = nexus.top().retVal;
    nexus.pop();
    return dbt;
}