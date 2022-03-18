#include<cstdio>
#include<cmath>
using namespace std;

int main() {
	constexpr int SZ = 5;
	static char mtx[SZ][SZ+1];

	char c;
	scanf_s("%c", &c,1);
	
	int MID = SZ / 2;
	for (int row = 0; row < SZ; row++) {
		int col = 0;
		int sptime = abs(MID - row);
		for (; col < sptime; col++) {
			mtx[row][col] = ' ';
		}
		int tartime = SZ - sptime * 2 + col;
		for (; col < tartime; col++) {
			mtx[row][col] = c;
		}
	}
	for (int i = 0; i < SZ; i++) {
		printf(mtx[i]);
		printf("\n");
	}
	return 0;
}

/*
样例输入
*
样例输出
  *
 ***
*****
 ***
  *
*/