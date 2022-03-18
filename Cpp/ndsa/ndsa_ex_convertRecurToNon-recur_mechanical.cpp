#include<iostream>
#include<stack>
using namespace std;

/*Example of the recursive version;*/
void exmp(int n, int& f){
    int u1, u2;
    if (n < 2)
        f = n + 1;
    else {
        exmp((int)(n / 2), u1);
        exmp((int)(n / 4), u2);
        f = u1 * u2;
    }
    return;
}

typedef struct elem {
    /*rd : return directory;*/
    /*pn : parameter n;*/
    /*pf : parameter reference f;*/
    /*q1 : local variable u1;*/
    /*q2 : local variable u2;*/
	int rd, pn, pf, q1, q2;
} ELEM;

class nonrec {
private:
	stack<ELEM> S;
public:
	nonrec(void){} //constructor;
	void replace1(int n, int& f);
	/*optimized conversion*/
	void replace2(int n, int& f);
};

int main(){
	int res = 0;
	exmp(5, res);
	cout << res << "\n" << flush;
	int res1 = 0;
	nonrec nr;
	nr.replace1(5, res1);
	cout << res1 << "\n" << flush;
}

void nonrec::replace1(int n, int& f){
	ELEM x, tmp;
	/*Push a "lookout" (rd = 3, ie the stop of computing) to the bottom*/
	x.rd = 3;
	x.pn = n;
	S.push(x);
/*label0 is the main entry of non-recursion;*/
label0:
    /*The terminating condition (when parameter n < 2);*/
	if ((x = S.top()).pn < 2){
		S.pop();
		x.pf = x.pn + 1;
		/*The result of evalution should be again push into the stack,
			for stack is the only nexus for passing all parameters and local variables;*/
		S.push(x);
		/*Here is the only way out (from initiation) to labelOA, which is an overall scheduling;*/
		goto labelOA;
	}
    /*else : the 2nd branch (when parameter n >= 2);*/
    /*The first recursive calling: fun(n / 2);*/
	x.rd = 1;//adjust rd but do not pop;
	x.pn = (int)(x.pn / 2);
	S.push(x);
	/*Every time when a recursive statement is done, go to label0 (overall scheduling);*/
	goto label0;
/*label1 is a mark for that : stack.top().rd == 1;*/
label1:
	/*Pass (param f of top layer) to (local variable of previous layer);*/
	tmp = S.top();
	S.pop();
	x = S.top();
	S.pop();
	x.q1 = tmp.pf; //modify u1 = pf;
	S.push(x);
    /*The second recursive calling: fun(n / 4);*/
	x.pn = (int)(x.pn / 4);
	x.rd = 2;
	S.push(x);
	goto label0;
/*label2 is a mark for completion of the 2nd recursive statement;*/
label2:
	tmp = S.top();
	S.pop();
	x = S.top();
	S.pop();
	x.q2 = tmp.pf;
    /*Integrate results;*/
	x.pf = x.q1 * x.q2;
	S.push(x);
	/*Control to the end of function and return;
		Here it can also go to labelOA;*/
/*labelOA is an entry into the nexus;*/
labelOA:
	x = S.top();//only peek the top but not pop;
	switch(x.rd){
	/*Let control go back to where it came from;*/
	case 1 :
		goto label1;
		break;
	case 2 :
		goto label2;
		break;
	/*If stack is at the bottom, the computing is over;*/
	case 3 :
		tmp = S.top();
		S.pop();
		f = tmp.pf;
		break;
	default : cerr << "error label number in stack\n";
		break;
	}
}

void nonrec::replace2(int n, int&f){
	ELEM x, tmp;
	//entry info;
	x.rd = 3;
	x.pn = n;
	S.push(x);
	do {
		//push along the left route of the recursive structure graph;
		while ((x = S.top()).pn >= 2){
			x.rd = 1;
			x.pn = (int)(x.pn / 2);
			S.push(x);
		}
		x = S.top(); //original exit, n <= 2;
		S.pop();
		x.pf = x.pn + 1;
		S.push(x);
		//If return from the second recursion, go uphead the route;
		while ((x = S.top()).rd == 2){
			tmp = S.top();
			S.pop();
			x = S.top();
			S.pop();
			x.pf = x.q1 * tmp.pf;
			S.push(x);
		}
		if ((x = S.top()).rd == 1){
			tmp = S.top();
			S.pop();
			x = S.top();
			S.pop();
			x.q1 = tmp.pf;
			S.push(x);
			/* enter into the second recursion;*/
			tmp.rd = 2;
			tmp.pn = (int)(x.pn / 4);
			S.push(tmp);
		}
	} while ((x = S.top()).rd != 3);
	x = S.top();
	S.pop();
	f = x.pf;
}