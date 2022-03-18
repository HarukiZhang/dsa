#include<iostream>
#include<stack>

using namespace std;

/*Original recursive function*/
void fibonacci(int n, int& f){
/*label_0:*/
    int lv;
    if (n < 2)// when n == 0 or n == 1;
        f = n;
    else {
        fibonacci(n - 1, lv);
        /*label_1:*/
        f = lv;
        fibonacci(n - 2, lv);
        /*label_2:*/
        f += lv;
    }
    return;
}

enum class RetDir : int { stop = 0, one, two = 2 };

struct Elem {
    RetDir rd;
    int pn, pf, lv;
};

class Nonrec {
private:
    stack<Elem> nexus;
public:
    Nonrec() = default;
    void replace(int n, int& f);
    void rplc_optm(int n, int& f);
};

int main(){
    Nonrec nonrec;
    int res;
    nonrec.rplc_optm(5, res);
    cout << res << endl;
}

void Nonrec::rplc_optm(int n, int& f){
    int retVal;
    Elem tmp{ RetDir::stop, n, 0, 0 };
    nexus.push(tmp);
    do {
    /*Process according to value of param n;*/
        
        /*First recursive calling;*/
        while (nexus.top().pn > 1){
            tmp.rd = RetDir::one;
            --tmp.pn;
            nexus.push(tmp);
            /*goto label_0;*/
        }
        /*if (nexus.top().pn < 2)*/
        nexus.top().pf = nexus.top().pn;
        /*goto label_OA;*/
    
    /*Start to process according to return directory;*/
        
        /*label_2:*/
        while (nexus.top().rd == RetDir::two){
            retVal = nexus.top().pf;
            nexus.pop();
            nexus.top().pf = retVal + nexus.top().lv;
            /*goto label_OA and
              then come back to label_2 if rd of prev layer == 2;*/
        }
        
        /*label_1:*/
        if (nexus.top().rd == RetDir::one){
            /*Pass result to previous layer;*/
            retVal = nexus.top().pf;
            nexus.pop();
            nexus.top().lv = retVal;
            /*Push the layer of the second recursion;*/
            tmp.rd = RetDir::two;
            tmp.pn = nexus.top().pn - 2;
            nexus.push(tmp);
            /*goto label_0;*/
        }

    } while (nexus.top().rd != RetDir::stop);
    f = nexus.top().pf;
    nexus.pop();
    return;
}

void Nonrec::replace(int n, int& f){
    int retVal;
    Elem tmp{ RetDir::stop, n, 0, 0 };
    nexus.push(tmp);
label_0:
    if (nexus.top().pn < 2){
        nexus.top().pf = nexus.top().pn;
        goto label_OA;
    }
    else {
        tmp.rd = RetDir::one;
        --tmp.pn;
        nexus.push(tmp);
        goto label_0;
    }
label_1:
    retVal = nexus.top().pf;
    nexus.pop();
    nexus.top().lv = retVal;
    /*The second recur func;*/
    tmp.rd = RetDir::two;
    tmp.pn = nexus.top().pn - 2;
    nexus.push(tmp);
    /*Why go to lebel_0?
      For in second rec func, param n still need to be separated;*/
    goto label_0;
label_2:
    retVal = nexus.top().pf;
    nexus.pop();
    nexus.top().pf = retVal + nexus.top().lv;
    /*The control reaches bottom end;
      goto label_OA and come back to babel_2 
      if rd of prev is still two;*/
label_OA:
    switch (nexus.top().rd){
    case RetDir::one :
        goto label_1;
        break;
    case RetDir::two :
        goto label_2;
        break;
    case RetDir::stop :
        f = nexus.top().pf;
        nexus.pop();
        break;
    default :
        break;
    }
    return;
}