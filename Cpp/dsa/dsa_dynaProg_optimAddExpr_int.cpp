#include<iostream>
#include<iomanip>
using namespace std;

char cstrIn[16];
//int numIn;
int numMtx[9][9];
/*minSumMtx[curLen][optN]*/
int minSumMtx[9][9]{ -1 };

void optimAddExpr(int& oprd, int strL, int optN) {
	for (int curL = 1; curL <= strL; ++curL) {
		for (int iOptN = 0; iOptN <= optN && iOptN <= curL; ++iOptN) {
			/*curL : the strlen from right end*/
			int& curOprd = ::minSumMtx[curL][iOptN];

			if (iOptN == 0) {
				curOprd = ::numMtx[strL - curL][strL - 1];
			}
			else if (curL <= iOptN) {
				curOprd = 0x6fffffff;
			}
			else {
				int minRes = 0x6fffffff;
				for (int i = strL - curL; i < strL; ++i) {
					int tmp1 = ::numMtx[strL - curL][i];
					int tmp2 = ::minSumMtx[strL - i - 1][iOptN - 1];
					int tmp = tmp1 + tmp2;
					if (tmp < minRes) minRes = tmp;
				}
				curOprd = minRes;
			}
		}
	}
	cout << ::minSumMtx[strL][optN];
}

void cstrToNumMtx(int strL) {
	int tmpNum;
	char tmpStr[16]{};
	for (int i = 0; i < strL; ++i) {
		for (int j = i; j < strL; ++j) {
			int k = i, t = 0;
			for (; k <= j; ++k, ++t) {
				tmpStr[t] = cstrIn[k];
			}
			tmpStr[t] = 0;
			tmpNum = atoi(tmpStr);
			::numMtx[i][j] = tmpNum;
		}
	}
}

int main() {
	int optNum;
	cin >> optNum >> cstrIn;
	int cstrLen = strlen(cstrIn);
	cstrToNumMtx(cstrLen);

	optimAddExpr(::minSumMtx[cstrLen][optNum], cstrLen, optNum);
	//for (int i = 0; i < cstrLen; ++i) {
	//	for (int j = 0; j < cstrLen; ++j) {
	//		cout << setw(10) << ::numMtx[i][j];
	//	}
	//	cout << "\n" << flush;
	//}
}