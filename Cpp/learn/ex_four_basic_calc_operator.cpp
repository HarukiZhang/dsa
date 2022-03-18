#include<iostream>

inline int add(int num1, int num2){
	int sum = num1 ^ num2;
	int carry = (num1 & num2) << 1;
	while (carry){
		int tmp = sum;
		sum = sum ^ carry;
		carry = (carry & tmp) << 1;
	}
	return sum;
}

inline int reciprocal(int num){
	return add(~num, 1);
}

inline int subtract(int minuend, int subtrahend){
	return add(minuend, reciprocal(subtrahend));
}

inline int prod(int num1, int num2){
	if (!(num1 && num2)) return 0;

	int sign1, sign2;
	if (sign1 = num1 >> 31 & 1) num1 = reciprocal(num1);
	if (sign2 = num2 >> 31 & 1) num2 = reciprocal(num2);

	int product = 0;
	while (num2){
		if (num2 & 1)
			product = add(product, num1);
		num2 = num2 >> 1;
		num1 = num1 << 1;
	}

	if (sign1 ^ sign2) product = reciprocal(product);
	return product;
}

inline int divide(int dividend, int divisor){
	if (!divisor) throw std::runtime_error("Divisor cannot be zero.");

	int sign1, sign2;
	if (sign1 = dividend >> 31 & 1) dividend = reciprocal(dividend);
	if (sign2 = divisor >> 31 & 1) divisor = reciprocal(divisor);

	int quotient = 0;
	if (dividend >= divisor){
		while (dividend >= divisor){
			dividend = subtract(dividend, divisor);
			quotient = add(quotient, 1);
		}
	}

	if (sign1 ^ sign2) quotient = reciprocal(quotient);
	return quotient;
}

int main () {
	std::cout << reciprocal(-5) << " " << reciprocal(5);
	
	// std::cout << 213 + -5432345 << std::endl
	// 	<< add(213, -5432345) << std::endl
	// 	<< 10 - 5 << std::endl
	// 	<< subtract(10, 5) << std::endl
	// 	<< 1234 * -5678 << std::endl
	// 	<< prod(1234, -5678) << std::endl
	// 	<< 0 / -2 << std::endl
	// 	<< divide(0 , -2);
}