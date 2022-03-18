#include<iostream>
#include<cstdlib>
using namespace std;

double switchOpt(char opt, double opdLf, double opdRt) {
	switch (opt) {
	case '+': return opdLf + opdRt; break;
	case '-': return opdLf - opdRt; break;
	case '*': return opdLf * opdRt; break;
	case '/': return opdLf / opdRt; break;
	default:
		cerr << "switch operator error." << endl;
		return 0.0;
	}
}

/*Actually this function is wrong:
	only a number also constitute a polish notation,
	but this function cannot handle this situation;
	
This function pre-assumes that all expression initiates with
	an operator;
*/
double myEvalRevPolishNota() {
	char opt, test;
	double revPN[2]{};//store two revPoliNota;
	cin >> opt >> ws;
	/*input two revPoliNota*/
	for (int i = 0; i < 2; ++i) {
		test = cin.peek();
		if (test >= '0' && test <= '9')
			cin >> revPN[i] >> ws;
		else
			revPN[i] = myEvalRevPolishNota();
	}
	return switchOpt(opt, revPN[0], revPN[1]);
}

/*Corrected version*/
double evalRevPolNota(){
	cin >> ws;
	char test = cin.peek();
	double opd;
	if (test >= '0'){
		cin >> opd >> ws;
		return opd;	 
	}
	else {
		cin >> test >> ws;
		return switchOpt(test, evalRevPolNota(), evalRevPolNota());
	}
}

/*GuoWei's version*/
int evalRPN() {
	char input[20];
	// When cin a c-str, it stops when encounter a space;
	cin >> input;
	switch (input[0]) {
	case '+': return evalRPN() + evalRPN();
	case '-': return evalRPN() - evalRPN();
	case '*': return evalRPN() * evalRPN();
	case '/': return evalRPN() / evalRPN();
	// Other than above operators, a number is expected;
	default: return atoi(input);
	}
}

int main() {
	freopen("E:\\in.txt", "r", stdin);
	cout << evalRPN();
}

/*
The "Reversed Polish Notation" that GuoWei said refers to
"Polish Notation" of BaiLian version or so called prefix expression,
which is a notation that put operator in front of two operands, such as:
	"* + 11 12 + 24 35" == "(11 + 12) * (24 + 35)"
*/