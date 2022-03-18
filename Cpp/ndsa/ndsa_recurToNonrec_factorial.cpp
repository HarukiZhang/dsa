#include<iostream>
#include<stack>
using namespace std;

/*example function recursive*/
int factorial(int x){
    if (x <= 2)
        return x;
    else
        return x * factorial(x - 1);
}

void factorial(int x, int& f){
    int u;
    if (x <= 2)
        f = x;
    else {
        factorial(x - 1, u);
        f = u * x;
    }
    return;
}

struct Elem {
    /* return directory, param x, param f, local variable; */
    int rd, px, pf;
};

class Nonrec {
private:
    stack<Elem> nexus;
public:
    Nonrec() = default;
    ~Nonrec() = default;
    void replace(int x, int& f);
    void optim_rep(int x, int& f);
};

int main(){
    Nonrec nonrec;
    int res;
    nonrec.optim_rep(5, res);
    cout << res << endl;
}

void Nonrec::replace(int x, int& f){
    Elem tmp, prev;
    tmp.rd = 9;
    tmp.px = x;
    nexus.push(tmp);
label_0:
    tmp = nexus.top();
    if (tmp.px <= 2){//Terminating condition;
        nexus.pop();
        /*Pass the result to the previous layer of stack;*/
        tmp.pf = tmp.px;
        nexus.push(tmp);
        goto label_OA;
    }
    else {/*push in new layer of recursive elem to stack;*/
        tmp.rd = 1;
        --tmp.px;
        nexus.push(tmp);
        /*Loop to iterate the most lateral side of binary tree;*/
        goto label_0;
    }
label_1:
    /*Pass (pram f of top layer) to (local variable of previous layer);*/
    tmp = nexus.top(); nexus.pop();
    prev = nexus.top(); nexus.pop();
    /*Pass the result to the previous layer;
    prev.localVariable = tmp.pf;*/
    prev.pf = tmp.pf * prev.px;
    nexus.push(prev);
    /*Reach the bottom end of the function;
      go to OASchd;*/
/*OverAll Scheduling;*/
label_OA:
    tmp = nexus.top();
    if (tmp.rd == 1)
        goto label_1;
    else {// rd = 9;
        f = tmp.pf;
        nexus.pop();
        return;
    }
}

void Nonrec::optim_rep(int x, int& f){
    Elem tmp{9, x, 0};
    nexus.push(tmp);
    while (nexus.top().px > 2){
        tmp = nexus.top();
        tmp.rd = 1;
        --tmp.px;
        nexus.push(tmp);
    }
    nexus.top().pf = nexus.top().px;
    while (nexus.top().rd == 1){
        tmp = nexus.top();
        nexus.pop();
        nexus.top().pf = tmp.pf * nexus.top().px;
    }
    f = nexus.top().pf;
    nexus.pop();
    return;
}