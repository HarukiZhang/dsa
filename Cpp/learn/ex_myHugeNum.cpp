#include <cstdlib>
#include <cstring>
#include <iostream>
#include <type_traits>

using std::ostream;
using std::cout;
using std::endl;

template<class T>
void print_bin(T num){
    int i = sizeof(T) * 8 - 1;
    if (std::is_signed<T>::value && num >> i & 1) {
        size_t reagent = INT_MAX;
        if (sizeof(T) == 8) reagent = LLONG_MAX;
        else if (sizeof(T) == 1) reagent = CHAR_MAX;
        num = ~(num & (T)reagent) + 1;
        --i;
        std::cout << 1;
    }
    for (; i >= 0; i--)
        std::cout << (num >> i & 1);
    // std::cout << std::endl;
}

constexpr int kMaxDig = 4;
constexpr int kUnitBitsCount = sizeof(size_t) * 8;
constexpr int kMaxBitsCount = kMaxDig * kUnitBitsCount * 8;

class myHugeNum
{
	unsigned long long buffer[kMaxDig];
public:
	myHugeNum() : buffer{0,0,0,0}{}
	~myHugeNum(){}
	myHugeNum(size_t a, size_t b, size_t c, size_t d)
		: buffer{a, b, c, d}{}
	// myHugeNum& operator=(myHugeNum& hn_){}	
	myHugeNum& operator<<(int offset){ //shift whole bits left
		size_t* transPtr = buffer + (kMaxDig - 1);
		size_t carry_in = 0, carry_out = 0;
		for (int i = 0; i < kMaxDig; ++i){
			carry_out = *(transPtr - i) >> (kUnitBitsCount - offset);
			*(transPtr - i) = *(transPtr - i) << offset | carry_in;
			carry_in = carry_out;
		}
		return *this;
	}
	myHugeNum& hnSHLB(){
		constexpr size_t reagent = 0x8000000000000000;
		size_t* transPtr = buffer + (kMaxDig - 1);
		size_t carry_in = 0, carry_out = 0;
		for (int i = 0; i < kMaxDig; ++i){
			carry_out = *(transPtr - i) & reagent ? 1 : 0;
			*(transPtr - i) = *(transPtr - i) << 1 | carry_in;
			carry_in = carry_out;
		}
		return *this;
	}
	myHugeNum operator^(const myHugeNum& hn_) const { // bitwise XOR
		myHugeNum res;
		for (int i = 0; i < kMaxDig; ++i)
			*(res.buffer + i) = *(buffer + i) ^ *(hn_.buffer + i);
		return res;
	}
	myHugeNum operator&(const myHugeNum& hn_) const { // bitwise AND
		myHugeNum res;
		for (int i = 0; i < kMaxDig; ++i)
			*(res.buffer + i) = *(buffer + i) & *(hn_.buffer + i);
		return res;
	}
	myHugeNum operator+(const myHugeNum& hn_) const{  // arithmetic Addition
		myHugeNum sum = *this ^ hn_;
		myHugeNum carry = (*this & hn_).hnSHLB();
		myHugeNum tmp;
		for (int i = 0; i < kMaxBitsCount; ++i){
			tmp = sum;
			sum = sum ^ carry;
			carry = (carry & tmp) << 1;
		}
		return sum;
	}
	friend ostream& operator<<(ostream& out, const myHugeNum& hn_){ //cout stream insertion
		for (int i = 2; i < kMaxDig; ++i)
			print_bin(*(hn_.buffer + i));
			// out << *(hn_.buffer + i);
		return out;
	}
};

int main(){
	int offset = 4;

	myHugeNum testhn {0, 0, 0xff, 0x1};
	myHugeNum btest  {0, 0, 0xa5, 0x2};

	cout << testhn << endl
		<< btest << endl
		<< (testhn + btest);

	// for (int i = kMaxDig - 1; i >= 0; --i)
	// 	std::cout << std::hex << *(transPtr - i) << " ";
}