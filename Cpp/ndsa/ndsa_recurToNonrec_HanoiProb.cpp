#include<iostream>
#include<stack>
using namespace std;

/*Question:
    This recursive method is very clear and simple;
    but logically, how does it assure that 
        each movement obeys the rule that only smaller plate can put onto bigger one;*/

/*Original Hanoi function:*/
void Hanoi(int n, char src, char mid, char dest){
    if (n == 1){
        /*If there is only one plate on the src, 
            we can simply move this one to the dest;*/
        cout << src << "->" << dest << endl;
    }
    else {
        /*Firstly, using dest as a transfer station to move n-1 plates to mid,
            so that there will be no plate on the dest,
            and only the most bottom palte is left on the src;*/
        Hanoi(n - 1, src, dest, mid);
        /*Consequently, we can easily move the left one on the src to the dest;*/
        cout << src << "->" << dest << endl;
        /*Then, we just need to figure out how to 
            move n-1 paltes on the mid to dest through src as transfer station;*/
        Hanoi(n - 1, mid, src, dest);
    }
    return;
}

struct Elem {
    int rd, pn;
    char src, mid, dest;
};

class Nonrec {
    stack<Elem> nexus;
public:
    Nonrec(){}
    void replace(int, char, char, char);
    void replc_optm(int, char, char, char);
};

int main(){
    Nonrec nonrec;
    nonrec.replace(4, 'A', 'B', 'C');
    cout << "\n--------------------" << endl;
    nonrec.replc_optm(4, 'A', 'B', 'C');
    return 0;
}

void Nonrec::replc_optm(int n, char src, char mid, char dest){
    Elem tmp{3, n, src, mid, dest };
    nexus.push(tmp);
    do {
        while (nexus.top().pn > 1){
            /*Set params for the first recursive function calling;*/
            tmp.rd = 1;
            tmp.pn = nexus.top().pn - 1;
            tmp.src = nexus.top().src;
            tmp.mid = nexus.top().dest;// mid exchange with dest;
            tmp.dest = nexus.top().mid;
            nexus.push(tmp);
        }
        /*if nexus.top().pn == 1;*/
        cout << nexus.top().src << "->" << nexus.top().dest << endl;
        /*The 2nd return directory;*/
        while (nexus.top().rd == 2)
            nexus.pop();
        /*The 1st return directory;*/
        if (nexus.top().rd == 1){
            nexus.pop();
            cout << nexus.top().src << "->" << nexus.top().dest << endl;
            /*Set params for the second recursive function calling;*/
            tmp.rd = 2;
            tmp.pn = nexus.top().pn - 1;
            tmp.src = nexus.top().mid;// src exchange with mid;
            tmp.mid = nexus.top().src;
            tmp.dest = nexus.top().dest;
            nexus.push(tmp);
            /*Control reaches end of funtion;*/
        }
    } while (nexus.top().rd != 3);
    /*When rd == 3 (stop);*/
    nexus.pop();
    return;
}

void Nonrec::replace(int n, char src, char mid, char dest){
    char swp;
    Elem tmp{ 3, n, src, mid, dest };
    nexus.push(tmp);
initial:
    if (nexus.top().pn == 1){
        cout << nexus.top().src << "->" << nexus.top().dest << endl;
        goto OASchdl;
    }
    else {
        /*Set params for the first recursive function calling;*/
        tmp.rd = 1;
        tmp.pn = nexus.top().pn - 1;
        tmp.src = nexus.top().src;
        tmp.mid = nexus.top().dest;
        tmp.dest = nexus.top().mid;
        nexus.push(tmp);
        goto initial;
    }
OASchdl:
    switch (nexus.top().rd){
    case 1 :
        nexus.pop();
        cout << nexus.top().src << "->" << nexus.top().dest << endl;
        tmp.rd = 2;
        tmp.pn = nexus.top().pn - 1;
        tmp.src = nexus.top().mid;
        tmp.mid = nexus.top().src;
        tmp.dest = nexus.top().dest;
        nexus.push(tmp);
        goto initial;
        break;
    case 2 :
        nexus.pop();
        goto OASchdl;
        break;
    case 3 :
        nexus.pop();
        break;
    default:
        break;
    }
    return;
}