#include <iostream>
using namespace std;

int evalFact();
int evalTerm();
int evalExpr();

int main() {
	cout << evalExpr();
}

int evalExpr(){
	int expr_val = evalTerm();
	while (true) {
		cin >> ws;
		char opt = cin.peek();
		if (opt == '+' || opt == '-'){
			cin >> opt >> ws;
			if (opt == '+')
				expr_val += evalTerm();
			else
				expr_val -= evalTerm();
		}
		else break;
	}
	return expr_val;
}

int evalTerm(){
	int term_val = evalFact();
	while (true) {
		cin >> ws;
		char opt = cin.peek();
		if (opt == '*' || opt == '/'){
			cin >> opt >> ws;
			if (opt == '*')
				term_val *= evalFact();
			else
				term_val /= evalFact();
		}
		else break;
	}
	return term_val;
}

int evalFact(){
	int fact_val;
	cin >> ws;
	char input = cin.peek();
	if (input == '('){
		cin >> input >> ws;
		fact_val = evalExpr();
		cin >> ws >> input;
		if (input != ')')
			cout << "Right parenthesis is not found.\n" << flush;
	}
	else cin >> fact_val;
	return fact_val;
}