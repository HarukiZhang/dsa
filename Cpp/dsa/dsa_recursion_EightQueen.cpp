#include <iostream>
using namespace std;
/*"8 Q in 8*8 CB" Problem : Recursive enumeration*/
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
		// Set the whole row all 0;
		chessB &= ~(kVerticOprd << (kChsBrdLen - row - 1) * kChsBrdLen);
		// Set the whole col all 0;
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
		return true;//The move is success;
	}
	return false;//The square is unavailable;
}

void printChsBrd(long long chessB){
	for (int i = 0; i < kChsBrdLen; ++i){
		for (int j = 0; j < kChsBrdLen; ++j)
			// Problem requires to print transposed matrix;
			//                             v -- swapped --  v
			cout << (chessB >> (kMaxLen - (j * kChsBrdLen + i)) & 1) << " ";
		cout << "\n" << flush;
	}
}

void eightQueenRecur(long long& chessB, long long& Qrec, char col_in, int row){
	// Count the number of resolution;
	static int counter = 1;
	/*Boundary Condition : when come to the 8th row*/
	if (row >= 8){
		// Enum 8 cols of the 8th row;
		for (char col = 'A'; col <= 'H'; ++col){
			long long chessBTmp = chessB, QrecTmp = Qrec;
			if (!moveQueen(chessBTmp, QrecTmp, col, row))
				continue;
			// When the Queen was actually checked on the 8th row;
			cout << "No. " << counter++ << "\n" << flush;						
			printChsBrd(QrecTmp);
			// Return to set boundary;
			return;				
		}
	}
	// For first to 7th row, the operation is the same;
	for (char col = 'A'; col <= 'H'; ++col){
		// Record and use the temp to go forward to the next row;
		// So that when the loop came back to the previous row,
		// the chessboard and the Q's position record could restore to last status;
		long long chessBTmp = chessB, QrecTmp = Qrec;
		if (!moveQueen(chessBTmp, QrecTmp, col, row))
			continue;
		else
			eightQueenRecur(chessBTmp, QrecTmp, col, row + 1);
			// If the present row was successfully set, recursively call
			// with increment of the row;
	}
}

int main() {
	long long chessBoard = kAllOneStr, QPos = kAllZeroStr;
	eightQueenRecur(chessBoard, QPos, 'A', 1);
}