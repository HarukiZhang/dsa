#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int MAX = 110;

class CHugeInt {
// 在此处补充你的代码
	char dig;
	char pNum[210];
public:
	CHugeInt() : dig(0){*pNum = 0;}
	CHugeInt(const char* inchrs_){
		dig = strlen(inchrs_);
		if (dig) {
			char pNum_[210]{};
			char half = dig / 2;
			for (int i = 0; i <= half; ++i){
				*(pNum + i) = *(inchrs_ + (dig - 1 - i));
				*(pNum + (dig - 1 - i)) = *(inchrs_ + i);
			}
			*(pNum + dig) = 0;
		}
		else *pNum = 0;
	}
	CHugeInt(int num_){
		dig = 0;
		for (int quo = num_; quo > 0; quo /= 10){
			*(pNum + dig) = (char)(quo % 10 + 48);
			dig++;
		} // the digit of max int wont go beyond CHugeInt
		*(pNum + dig) = 0;
	}
	CHugeInt(const CHugeInt& cpyCHI_) : dig(cpyCHI_.dig){
		if (dig) strcpy(pNum, cpyCHI_.pNum);
	}
	~CHugeInt(){}
	CHugeInt operator+(const CHugeInt& cHINum_) const {
		char max_dig = dig >= cHINum_.dig ? dig : cHINum_.dig;
		const char* pLong = dig >= cHINum_.dig ? pNum : cHINum_.pNum;
		char min_dig = dig <= cHINum_.dig ? dig : cHINum_.dig;
		const char* pShort = dig <= cHINum_.dig ? pNum : cHINum_.pNum;
		CHugeInt resCHI;
		char carry = 0;
		int i = 0;
		for (; i < min_dig; ++i){
			char sum = *(pNum + i) + *(cHINum_.pNum + i) - 48 + carry;
			if (sum > 57){
				carry = 1;
				sum -= 10;
			}
			else carry = 0;
			*(resCHI.pNum + i) = sum;
		}
		for (; i < max_dig; ++i){
			char sum = *(pLong + i) + carry;
			if (sum > 57){
				carry = 1;
				sum -= 10;
			}
			else carry = 0;
			*(resCHI.pNum + i) = sum;
		}
		if (carry) {
			*(resCHI.pNum + i) = '1';
			++i;
		}
		*(resCHI.pNum + i) = 0;
		resCHI.dig = strlen(resCHI.pNum);
		return resCHI;
	}
	CHugeInt& operator++(){ //prefixed ++;
		*this = 1 + *this;
		return *this;
	}
	CHugeInt operator++(int nouse_){
		CHugeInt tmp{*this};
		*this = 1 + *this;
		return tmp;
	}
	void operator+=(int num_){
		CHugeInt cHINum_{num_};
		*this = this->operator+(cHINum_);
	}
	friend CHugeInt operator+(int num1_, const CHugeInt& cHINum2_){
		const CHugeInt cHINum1_(num1_);
		return cHINum1_ + cHINum2_;
	}
	friend ostream& operator<<(ostream& out, const CHugeInt& cHINum_){
		for (int i = cHINum_.dig - 1; i >= 0; i--){
			out << *(cHINum_.pNum + i);
		}
		return out;
	}
// 在此处补充你的代码
};

int  main() 
{
	char s[210];
	int n;
	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}
/*
输入
多组数据，每组数据是两个非负整数s和 n。s最多可能200位， n用int能表示
输出
对每组数据，输出6行，内容分别是：
样例输入
99999999999999999999999999888888888888888812345678901234567789 12
6 6
样例输出
99999999999999999999999999888888888888888812345678901234567801
99999999999999999999999999888888888888888812345678901234567801
99999999999999999999999999888888888888888812345678901234567801
25
25
26
12
12
12
13
13
14
*/