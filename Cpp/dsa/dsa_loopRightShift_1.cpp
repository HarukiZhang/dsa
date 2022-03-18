#include <iostream>
using namespace std;
int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int gcd(int a, int b)
{
	while (int t = a % b)
	{
		a = b;
		b = t;
	}
	return b;
}

void printA(){
	for (int i = 0; i < 10; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void loopRightShift(int* start, int len, int offset){
	int d = gcd(len, offset);
	for (int i = 0; i < d; i++)
	{
		for (int j = 1; j <= len / d; j++)
		{
			int idx = (i + offset * j) % len;
			int temp = a[i];
			a[i] = a[idx];
			a[idx] = temp;
		}
	}
}

int main()
{
	int n = 10, k = 2;
	loopRightShift(a, n, k);
	// cout << "i=" << i << " j=" << j << " s=" << sel << "  ";
	printA();
}
/*
每个元素到它要去的位置连有向边，这就形成gcd(n,k)个环;
	GCD, Greatest Common Divisor（最大公因数）;
对于每个环，暂存其中一个值并移动其他值;
先整体反转，然后局部反转，这样只需一个附加空间用于交换，时间复杂度O(n);
*/