#include <iostream>
#include <algorithm>
#include <vector>
/*描述
给出4个小于10个正整数，你可以使用加减乘除4种运算以及括号把这4个数连接起来得到一个表达式。
现在的问题是，是否存在一种方式使得得到的表达式的结果等于24。

这里加减乘除以及括号的运算结果和运算的优先级跟我们平常的定义一致（这里的除法定义是实数除法）。

比如，对于5，5，5，1，我们知道5 * (5 – 1 / 5) = 24，因此可以得到24。
又比如，对于1，1，4，2，我们怎么都不能得到24。

输入
输入数据包括多行，每行给出一组测试数据，包括4个小于10个正整数。
最后一组测试数据中包括4个0，表示输入的结束，这组数据不用处理。

输出
对于每一组测试数据，输出一行，如果可以得到24，输出“YES”；否则，输出“NO”。

样例输入
5 5 5 1
1 1 4 2
0 0 0 0

样例输出
YES
NO
*/
/*This is a violant-loop Enumeration solution*/
using namespace std;
vector<int> operands;

/*This class is used to record and calc fraction precisely*/
class FRACTION {
public:
	int numer, denom;

	FRACTION(int n, int d)
		:numer(n), denom(d) {}
	FRACTION(const FRACTION& frac)
		//const lvalue param. receives both rvalue and lvalue;
		:numer(frac.numer),
		 denom(frac.denom) {}
	FRACTION(int num) : numer(num), denom(1) {}
	FRACTION& operator=(const FRACTION& opd){
		this->numer = opd.numer;
		this->denom = opd.denom;
		return *this;
	}
	FRACTION operator+(const FRACTION& opd) const {
		//return type is a non-reference : pure rvalue;
		// const lvalue reference param. receives both rvalue and lvalue;
		FRACTION tmp {numer, denom};
		tmp.numer = opd.numer * denom + numer * opd.denom;
		tmp.denom *= opd.denom;
		// tmp.reduction();
		return tmp;
	}
	FRACTION operator-(const FRACTION& opd) const {
		FRACTION tmp {numer, denom};
		tmp.numer = numer * opd.denom - opd.numer * denom;
		tmp.denom *= opd.denom;
		// tmp.reduction();
		return tmp;
	}
	FRACTION operator*(const FRACTION& opd) const {
		FRACTION tmp {numer, denom};
		tmp.numer *= opd.numer;
		tmp.denom *= opd.denom;
		// tmp.reduction();
		return tmp;
	}
	FRACTION operator/(const FRACTION& opd) const {
		FRACTION tmp {numer, denom};
		tmp.numer *= opd.denom;
		tmp.denom *= opd.numer;
		// tmp.reduction();
		return tmp;
	}
	bool isZero() const {
		if (numer == 0)
			return true;
		return false;
	}
	int gcd(int a, int b){
		while (int t = a % b){
			a = b;
			b = t;
		}
		return b;
	}
	void reduction(){
		int b = gcd(numer, denom);
		numer /= b;
		denom /= b;
	}
	operator int (){
		reduction();
		if (denom == 1)
			return numer;
		else
			return 0;
	}
};

FRACTION fracZero {0};

FRACTION selectOpt(const FRACTION& opdlf, const FRACTION& opdrt, int idx){
	switch (idx) {
	case 0:
		return opdlf + opdrt;
		break;
	case 1:
		return opdlf - opdrt;
		break;
	case 2:
		return opdrt - opdlf;
		break;
	case 3:
		return opdlf * opdrt;
		break;
	case 4:
		if (opdrt.isZero())
			return fracZero;
		return opdlf / opdrt;
		break;
	case 5:
		if (opdlf.isZero())
			return fracZero;
		return opdrt / opdlf;
		break;
	default:
		cout << "operator selection error" << endl;
		return ::fracZero;
	}
}

void calc24(){
	do {
		for (int op1 = 0; op1 < 6; ++op1){
			for (int op2 = 0; op2 < 6; ++op2){
				for (int op3 = 0; op3 < 6; ++op3){
					/*pick three operation and get answer*/
					FRACTION opd0 {::operands[0]};
					FRACTION opd1 {::operands[1]};
					FRACTION opd2 {::operands[2]};
					FRACTION opd3 {::operands[3]};

					FRACTION res1 = selectOpt(opd0, opd1, op1);
					res1 = selectOpt(res1, opd2, op2);
					res1 = selectOpt(res1, opd3, op3);
					if (static_cast<int>(res1) == 24){
						cout << "YES\n" << flush;
						// cout << ::operands[0] << " " << ::operands[1] << " "
						// 	<< ::operands[2] << " " << ::operands[3]
						// 	<< " can be calculated to 24.\n" << flush;
						return;
					}

					res1 = selectOpt(opd0, opd1, op1);
					FRACTION res2 = selectOpt(opd2, opd3, op3);
					res2 = selectOpt(res1, res2, op2);
					if (static_cast<int>(res2) == 24){
						cout << "YES\n" << flush;
						return;
					}
				}
			}
		}
	} while (next_permutation(::operands.begin(), ::operands.end()));
	cout << "NO\n" << flush;
	// cout << ::operands[0] << " " << ::operands[1] << " "
	// 	<< ::operands[2] << " " << ::operands[3]
	// 	<< " can NOT be calculated to 24.\n" << flush;
	return;
}

ostream& operator<<(ostream& os, const FRACTION& frac){
	os << "(" << frac.numer << "/" << frac.denom << ")";
	return os;
}

int main() {
	// FRACTION a{8, 3}, b{6, 3}, c{2, 3}, d{1, 3};
	// FRACTION res1{0};
	// // res1 = c + d;
	// // cout << res1 << endl;
	// // res1 = res1 * a;
	// // cout << res1 << endl;
	// // res1 = res1 / b;
	// // cout << res1 << endl
	// // 	<< static_cast<int>(res1);
	// res1 = a + b + (c + d);
	// cout << res1 << endl;

	int input;
	while (true){
		int zeroCtr = 0;
		for (int i = 0; i < 4; ++i){
			cin >> input;
			if (input == 0)
				++zeroCtr;
			::operands.push_back(input);
		}
		if (zeroCtr == 4)
			return 0;
		sort(::operands.begin(), ::operands.end());
		calc24();
		::operands.clear();
	}
}
