#include <iostream>
#include <iomanip>
#include <bitset>
#include <Windows.h>
using namespace std;
/*"8 Q in 8*8 CB" Problem*/
/*Container:
	Use a 64 bits long long int to denote a basic chessboard;
		Initiation : all one string;
		If a single square or a col or a row has been watched by a Queen,
		invert this square to 0;
	Use another long long int to record Queen's position;
		Where, initiation : all zero string;
		The loc where a Queen is moved to will be set to 1;
*/

constexpr int kChsBrdLen = 8;
constexpr int kMaxLen = 63;
constexpr long long kVerticOprd = 0xffLL;
constexpr long long kHorizaOprd = 0x101010101010101;
constexpr long long kSingltonOprd = 1LL;
constexpr long long kAllZeroStr = 0LL;
constexpr long long kAllOneStr = ~0LL;

bool moveQueen(long long& chessB, long long& Qrec, char col_char, int row){
	int col = col_char - 'A';
	row -= 1;
	bool isLocAvail = chessB >> (kMaxLen - (row * kChsBrdLen + col)) & 1;
	if (isLocAvail){// if the given loc is available;
		// Record the Queen's loc on QPos;
		Qrec |= kSingltonOprd << (kMaxLen - (row * kChsBrdLen + col));
		/*Set all loc that are watched by this Q on chessBoard*/
		// Set the same row all 0;
		chessB &= ~(kVerticOprd << (kChsBrdLen - row - 1) * kChsBrdLen);
		// Set the same col all 0;
		chessB &= ~(kHorizaOprd << kChsBrdLen - col - 1);
		// Set all the diagonal squares 0;
		int dirSign[2] = {-1, 1};
		for (int i : dirSign){
			for (int j : dirSign){
				for (int r = row + i, c = col + j;
					r >= 0 && r < kChsBrdLen && c >= 0 && c < kChsBrdLen; 
					r += i, c += j){
					chessB &= ~(kSingltonOprd << (kMaxLen - (r * kChsBrdLen + c)));
				}
			}
		}
		return true;//means this stake is success;
	}
	return false;//if Loc is not available, return false;
}

void printChsBrd(long long chessB){
	for (int i = 0; i < kChsBrdLen; ++i){
		for (int j = 0; j < kChsBrdLen; ++j)
			// Problem requires to print transposed matrix;
			cout << (chessB >> (kMaxLen - (j * kChsBrdLen + i)) & 1) << " ";
		cout << "\n" << flush;
	}
}

void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1, const char* tag_name) {
    static double freq = -1;
    if (freq == -1) {
        LARGE_INTEGER fq;
        QueryPerformanceFrequency(&fq);
        freq = (double)fq.QuadPart;
        std::clog << "\n\n-----------------------------\n" << std::flush;
    }
    double ts = (double)(t1.QuadPart - t0.QuadPart) / freq;
    if (ts < 1) {
        ts *= 1000;
        std::clog << tag_name << ":" 
            << std::setprecision(3) << ts << " ms\n-----------------------------\n"
            << std::flush;
    }
    else std::clog << tag_name << ":" 
            << std::setprecision(3) << ts << " s\n-----------------------------\n"
            << std::flush;
    return;
}

int main() {
	freopen("D:\\haruk\\Documents\\VSCode\\Cpp\\out.txt", "w", stdout);
	LARGE_INTEGER t0, t1;
	QueryPerformanceCounter(&t0);

	int counter = 1;
	for (char fr1 = 'A'; fr1 <= 'H'; ++fr1){
		long long chessB = kAllOneStr, QPos = kAllZeroStr;
		moveQueen(chessB, QPos, fr1, 1);
	for (char fr2 = 'A'; fr2 <= 'H'; ++fr2){
		long long chessBTmp = chessB, QPosTmp = QPos;
		if (!moveQueen(chessBTmp, QPosTmp, fr2, 2))
			continue;
	for (char fr3 = 'A'; fr3 <= 'H'; ++fr3){
		long long chessBTmp3 = chessBTmp, QPosTmp3 = QPosTmp;
		if (!moveQueen(chessBTmp3, QPosTmp3, fr3, 3))
			continue;
	for (char fr4 = 'A'; fr4 <= 'H'; ++fr4){
		long long chessBTmp4 = chessBTmp3, QPosTmp4 = QPosTmp3;
		if (!moveQueen(chessBTmp4, QPosTmp4, fr4, 4))
			continue;
	for (char fr5 = 'A'; fr5 <= 'H'; ++fr5){
		long long chessBTmp5 = chessBTmp4, QPosTmp5 = QPosTmp4;
		if (!moveQueen(chessBTmp5, QPosTmp5, fr5, 5))
			continue;
	for (char fr6 = 'A'; fr6 <= 'H'; ++fr6){
		long long chessBTmp6 = chessBTmp5, QPosTmp6 = QPosTmp5;
		if (!moveQueen(chessBTmp6, QPosTmp6, fr6, 6))
			continue;	
	for (char fr7 = 'A'; fr7 <= 'H'; ++fr7){
		long long chessBTmp7 = chessBTmp6, QPosTmp7 = QPosTmp6;
		if (!moveQueen(chessBTmp7, QPosTmp7, fr7, 7))
			continue;
	for (char fr8 = 'A'; fr8 <= 'H'; ++fr8){
		long long chessBTmp8 = chessBTmp7, QPosTmp8 = QPosTmp7;
		if (!moveQueen(chessBTmp8, QPosTmp8, fr8, 8))
			continue;
		cout << "No. " << counter++ << "\n" << flush;						
		printChsBrd(QPosTmp8);
	}	}	}	}	}	}	}	}
	
	QueryPerformanceCounter(&t1);
	printPerfCounter(t0, t1, "Total ");
}
/*
描述
在国际象棋棋盘上放置八个皇后，要求每两个皇后之间不能直接吃掉对方。
皇后可以在横、竖、斜线上不限步数地吃掉其他棋子。

无输入。

输出
按给定顺序和格式输出所有八皇后问题的解（见Sample Output）。

提示
此题可使用函数递归调用的方法求解。

样例输出
No. 1
1 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 1 
0 1 0 0 0 0 0 0 
0 0 0 1 0 0 0 0 
0 0 0 0 0 1 0 0 
0 0 1 0 0 0 0 0 
No. 2
1 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 0 1 0 0 0 0 
0 0 0 0 0 1 0 0 
0 0 0 0 0 0 0 1 
0 1 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 
0 0 1 0 0 0 0 0 
No. 3
1 0 0 0 0 0 0 0 
0 0 0 0 0 1 0 0 
0 0 0 0 0 0 0 1 
0 0 1 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 0 1 0 0 0 0 
0 1 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 
No. 4
1 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 1 
0 0 0 0 0 1 0 0 
0 0 1 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 1 0 0 0 0 0 0 
0 0 0 1 0 0 0 0 
No. 5
0 0 0 0 0 1 0 0 
1 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 
0 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 1 
0 0 1 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 0 1 0 0 0 0 
No. 6
0 0 0 1 0 0 0 0 
1 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 1 
0 1 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 1 0 0 0 0 0 
0 0 0 0 0 1 0 0 
No. 7
0 0 0 0 1 0 0 0 
1 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 1 
0 0 0 1 0 0 0 0 
0 1 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 1 0 0 0 0 0 
0 0 0 0 0 1 0 0 
No. 8
0 0 1 0 0 0 0 0 
1 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 1 
0 1 0 0 0 0 0 0 
0 0 0 1 0 0 0 0 
0 0 0 0 0 1 0 0 
No. 9
0 0 0 0 1 0 0 0 
1 0 0 0 0 0 0 0 
0 0 0 1 0 0 0 0 
0 0 0 0 0 1 0 0 
0 0 0 0 0 0 0 1 
0 1 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 
0 0 1 0 0 0 0 0 
...以下省略
*/