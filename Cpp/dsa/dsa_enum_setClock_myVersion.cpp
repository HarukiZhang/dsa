#include <iostream>
#include <bitset>
using namespace std;

/*container for store 9 clock : one int*/
/*
Use 3 bits as one unit to denote one clock;
	9 clocks consist of a plate, so that it'll use 27 bits, 
	which is containable within one int;
Use binary 000, 001, 010, 011 to denote four direction;
	For periodically rotating, use binary 100 as an operator
		to bit-wise-and each clock unit to comsume the carry-in when addition;
Use big-end storage : the clock in block A is stored in the left end;
*/
int clockPlate = 0;

/*input the clock needle direction and store their complementary*/
void inputCompl(int& clckPlt){
	int input;
	for (int i = 8; i >= 0; --i){
		cin >> input;
		input = 4 - input & 0b011;
		clckPlt |= input << (i * 3);
	}
}

/*set all clocks in plate according to instruction No.*/
// return the whole plate after setting;
int setClock(int clckPlt, int instrN, int times){
	/*	移动    影响的时钟
		1         ABDE
		2         ABC
		3         BCEF
		4         ADG
		5         BDEFH
		6         CFI
		7         DEGH
		8         GHI
		9         EFHI	*/
	int setPatt;// setting pattern;
	switch (instrN) {
		case 1: setPatt = 0330'330'000; break;
		case 2: setPatt = 0333'000'000; break;
		case 3: setPatt = 0033'033'000; break;
		case 4: setPatt = 0300'300'300; break;
		case 5: setPatt = 0030'333'030; break;
		case 6: setPatt = 0003'003'003; break;
		case 7: setPatt = 0000'330'330; break;
		case 8: setPatt = 0000'000'333; break;
		case 9: setPatt = 0000'033'033; break;
		default : 
			setPatt = -100;
			cout << " instrSet select error " << endl;
	}
	for (int i = 0; i < times; ++i)
        clckPlt = clckPlt + setPatt & 0333'333'333;// +3 == -1;
    return clckPlt;
}

/*get the needle direction of the given block*/
inline int checkBlock(int clckPlt, int whichB){
	return clckPlt >> ((8 - whichB) * 3) & 0b111;
}

/*adjust the rest determined clocks*/
/*Adjusting method:
	The clockPlate stores the complementary direction of the actually given direction;
	These C-direction numerated the steps it takes to adjust the clock to zero;
	These C-direction indices also suggested 
		the times that we need to use a specific Move method;*/
inline void adjustClock(int& clckPlt, int* counter, int whichB, int whichM){
	int setTimes;
	if (setTimes = clckPlt >> ((8 - whichB) * 3) & 0b11)
		clckPlt = setClock(clckPlt, whichM, setTimes);
	counter[whichM - 1] = setTimes;
}

/*print the clock plate for debugging*/
void output4chk(int clckPlt){
	int outN = 0;
	for (int i = 8; i >= 0; --i){
		outN = clckPlt >> (i * 3) & 0b111;
		cout << outN << " ";
	}
	cout << endl;
}

int main() {
	// input and record the complementary of the diretion;
	inputCompl(clockPlate);

	// debug:
	cout << "input : ";
	output4chk(clockPlate);
	cout << endl;

    int mTimes[9]{}, mTTmp[9]{}, clockTmp, moveSum = 30;
    for (mTTmp[0] = 0; mTTmp[0] < 4; ++mTTmp[0]){
        for (mTTmp[1] = 0; mTTmp[1] < 4; ++mTTmp[1]){
            for (mTTmp[2] = 0; mTTmp[2] < 4; ++mTTmp[2]){
				
				clockTmp = clockPlate;
				clockTmp = setClock(clockTmp, 1, mTTmp[0]);
				clockTmp = setClock(clockTmp, 2, mTTmp[1]);
                clockTmp = setClock(clockTmp, 3, mTTmp[2]);
                // After above operations, if block A, B, C still not zero,
                // these 3 blocks have to be set by M4,M5,M6;
				/* 	
					A B C
					D   F
							*/
				adjustClock(clockTmp, mTTmp, 0, 4);//block A, Move 4;
				adjustClock(clockTmp, mTTmp, 1, 5);//block B, Move 5;
				adjustClock(clockTmp, mTTmp, 2, 6);//block C, Move 6;
                // Then, only M7 can set block D, and M9 block F;
				adjustClock(clockTmp, mTTmp, 3, 7);//block D, Move 7;
				adjustClock(clockTmp, mTTmp, 5, 9);//block F, Move 9;
				
				// After block D, F, then no Move method can set block E;
				// if block E is not yet zero, then this enum is uncorrect;
				if (clockTmp & 0777'777'000)//check whether block A~F are all zero-directed;
					continue;

                // Come to here, block A to F are all checked zero;
                // Then, it should be checked whether block G to I is tri-equal;
				int chkG = checkBlock(clockTmp, 6);//block G;
				if (chkG != checkBlock(clockTmp, 7) //block H;
					|| chkG != checkBlock(clockTmp, 8)){//block I;
						// If any of G,H,I is unequal, this enum is uncorrect;
						mTTmp[7] = 0;
						continue;
					}
				else // all equal, then just record how many times it need to use Move 8;
					mTTmp[7] = clockTmp & 0b11;//block I, Move 8;
				
				// record the minimal times;
				int moveSumTmp = 0;
				for (int i = 0; i < 9; ++i)
					moveSumTmp += mTTmp[i];
				if (moveSumTmp < moveSum){
					moveSum = moveSumTmp;
					// one correct route found, record them all;
					for (int i = 0; i < 9; ++i)
						mTimes[i] = mTTmp[i];
				}
            }
        }
    }
	// output the move times;
	for (int i = 0; i < 9; ++i)
		while (mTimes[i]){
			cout << i + 1 << endl;
			--mTimes[i];
		}
	/*before-success algo*/
	// int stepMin = 10, idxMin = 0, clockTmp, tmp, stepC;
	// for (int i = 1; i <= 9; ++i){
	// 	clockTmp = clockPlate;
	// 	stepC = 0;
	// 	clockTmp = setClock(clockTmp, i);
	// 	for (int j = i + 1; j <= 9; ++j){
	// 		tmp = setClock(clockTmp, j);
	// 		if (tmp < clockTmp){
	// 			clockTmp = tmp;
	// 			++stepC;
	// 		}
	// 	}
	// 	if (clockTmp == 0){
	// 		if (stepMin > stepC){
	// 			stepMin = stepC;
	// 			idxMin = i;
	// 		}
	// 	}
	// }
	// if (idxMin != 0){
	// 	for (int i = idxMin; i <= 9; ++i){
	// 		tmp = setClock(clockPlate, i);
	// 		if (tmp < clockPlate){
	// 			clockPlate = tmp;
	// 			cout << i << " : ";
	// 			output4chk(clockPlate);
	// 		}
	// 	}
	// }
	// else cout << "error";
}
/*
#INPUT:
3 3 0
2 2 2
2 1 2

#OUTPUT:
input : 1 1 0 2 2 2 2 3 2

4 : 0 1 0 1 2 2 1 3 2
5 : 0 0 0 0 1 1 1 2 2
8 : 0 0 0 0 1 1 0 1 1
9 : 0 0 0 0 0 0 0 0 0

clckPlt = 0 0 0 0 0 0 0 0 0
*/