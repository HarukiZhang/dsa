#include<cstdio>
#include<cmath>
using namespace std;
constexpr double EPS = 1e-8;
int main() {
	double a, b, c, bsq, ac4;
	scanf_s("%lf %lf %lf", &a, &b, &c);
	bsq = b * b;
	ac4 = 4 * a * c;
	if (b == 0.0) b = -b;
	if (fabs(bsq - ac4) < EPS) { // i.e. bsq == ac4
		printf("x1=x2=%.5f", -b / 2 / a);
	}
	else {
		double delta = sqrt(fabs(bsq - ac4));
		if (bsq - ac4 > EPS) {
			double nmrt1 = -b + delta, nmrt2 = -b - delta;
			if (nmrt1 < EPS && nmrt1 > -EPS) nmrt1 = 0.0;
			if (nmrt2 < EPS && nmrt2 > -EPS) nmrt2 = 0.0;
			printf("x1=%.5f;x2=%.5f", nmrt1 / 2 / a, nmrt2 / 2 / a);
		}
		else {
			double real = -b / 2 / a, imag = delta / 2 / a;
			printf("x1=%.5f+%.5fi;x2=%.5f-%.5fi", real, imag, real, imag);
		}
	}
}

/*
利用公式x1 = (-b + sqrt(b*b-4*a*c))/(2*a), x2 = (-b - sqrt(b*b-4*a*c))/(2*a)求一元二次方程ax2+ bx + c =0的根，其中a不等于0。

输入
输入一行，包含三个浮点数a, b, c（它们之间以一个空格分开），分别表示方程ax2 + bx + c =0的系数。
输出
输出一行，表示方程的解。
若b2 = 4 * a * c,则两个实根相等，则输出形式为：x1=x2=...。
若b2 > 4 * a * c,则两个实根不等，则输出形式为：x1=...;x2 = ...，其中x1>x2。
若b2 < 4 * a * c，则有两个虚根，则输出：x1=实部+虚部i; x2=实部-虚部i，即x1的虚部系数大于等于x2的虚部系数，实部为0时不可省略。实部 = -b / (2*a), 虚部 = sqrt(4*a*c-b*b) / (2*a)

所有实数部分要求精确到小数点后5位，数字、符号之间没有空格。
样例输入
样例输入1
1.0 2.0 8.0

样例输入2
1 0 1
样例输出
样例输出1
x1=-1.00000+2.64575i;x2=-1.00000-2.64575i

样例输出2
x1=0.00000+1.00000i;x2=0.00000-1.00000i
*/