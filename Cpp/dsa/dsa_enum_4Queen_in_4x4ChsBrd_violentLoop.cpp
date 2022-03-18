#include <iostream>
#include <iomanip>
#include <bitset>
#include <Windows.h>
using namespace std;
/*Firstly, try to figure out a "4 Queen in 4*4 ChessBoard" Problem*/
/*
Use a 16 bits short int to denote a basic chessboard;
	Initiation : all grid are set to 1;
	If a single grid or a col or a row has been watched by a Queen,
		invert this grid to 0;
Use another short int to record Queen's position;
	Where, initiation : all 0;
	The loc where a Queen is moved to will be set to 1;
*/
constexpr short kChsBrdLen = 4;
// short chessBoard = 0xffff;
// short QPos = 0;

bool stakeQueen(short& chessB, short& Qrec, char col_char, short row){
	short col = col_char - 'A';
	row -= 1;
	if (chessB >> (15 - (row * kChsBrdLen + col)) & 1){
							// if the given loc is available;
		// set the Queen's loc on QPos;
		Qrec |= 1 << (15 - (row * kChsBrdLen + col));
		/*set all loc that are watched by this Q on chessBoard*/
		// set the same row all 0;
		chessB &= ~(0xf << (kChsBrdLen - row - 1) * kChsBrdLen);
		// set the same col all 0;
		chessB &= ~(0x1111 << kChsBrdLen - col - 1);

		int dirSign[2] = {-1, 1};
		for (int i : dirSign){
			for (int j : dirSign){
				for (int r = row, 
						c = col;
					r >= 0 && r < kChsBrdLen &&
					c >= 0 && c < kChsBrdLen; 
					r += i,
					c += j){
					chessB &= ~(1 << (15 - (r * kChsBrdLen + c)));
				}
			}
		}
		return true;//means this stake is success;
	}
	return false;//if Loc is not available, return false;
}

void printChsBrd(short chessB){
	for (int i = 0; i < kChsBrdLen; ++i){
		for (int j = 0; j < kChsBrdLen; ++j)
			cout << (chessB >> (15 - (i * kChsBrdLen + j)) & 1)
				<< " ";
		cout << endl;
	}
}

bool eightQueen(short& chessB){ return true; }

void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1, const char* tag_name) {
    static double freq = -1;
    if (freq == -1) {
        LARGE_INTEGER fq;
        QueryPerformanceFrequency(&fq);
        freq = (double)fq.QuadPart;
        std::cout << "\n\n-----------------------------\n" << std::flush;
    }
    double ts = (double)(t1.QuadPart - t0.QuadPart) / freq;
    if (ts < 1) {
        ts *= 1000;
        std::cout << tag_name << ":" 
            << std::setprecision(3) << ts << " ms\n-----------------------------\n"
            << std::flush;
    }
    else std::cout << tag_name << ":" 
            << std::setprecision(3) << ts << " s\n-----------------------------\n"
            << std::flush;
    return;
}

int main() {
	// stakeQueen(chessBoard, QPos, 'B', 2);
	LARGE_INTEGER t0, t1;
	QueryPerformanceCounter(&t0);
	for (char fr1 = 'A'; fr1 <= 'D'; ++fr1){
	for (char fr2 = 'A'; fr2 <= 'D'; ++fr2){
	for (char fr3 = 'A'; fr3 <= 'D'; ++fr3){
	for (char fr4 = 'A'; fr4 <= 'D'; ++fr4){
		short chessB = 0xffff, QPos = 0;
		stakeQueen(chessB, QPos, fr1, 1);
		if (!stakeQueen(chessB, QPos, fr2, 2))
			continue;
		if (!stakeQueen(chessB, QPos, fr3, 3))
			continue;
		if (!stakeQueen(chessB, QPos, fr4, 4))
			continue;
		printChsBrd(QPos);
		cout << endl;
	}
	}
	}
	}
	QueryPerformanceCounter(&t1);
	printPerfCounter(t0, t1, "Total ");



	
}
/*
描述
会下国际象棋的人都很清楚：皇后可以在横、竖、斜线上不限步数地吃掉其他棋子。
如何将8个皇后放在棋盘上（有8 * 8个方格），使它们谁也不能被吃掉！这就是著名的八皇后问题。

对于某个满足要求的8皇后的摆放方法，定义一个皇后串a与之对应，即a=b1b2...b8，
其中bi为相应摆法中第i行皇后所处的列数。
已经知道8皇后问题一共有92组解（即92个不同的皇后串）。
给出一个数b，要求输出第b个串。
串的比较是这样的：皇后串x置于皇后串y之前，当且仅当将x视为整数时比y小。

输入
第1行是测试数据的组数n，后面跟着n行输入。每组测试数据占1行，包括一个正整数b(1 <= b <= 92)

输出
输出有n行，每行输出对应一个输入。输出应是一个正整数，是对应于b的皇后串。

样例输入
2
1
92

样例输出
15863724
84136275
*/