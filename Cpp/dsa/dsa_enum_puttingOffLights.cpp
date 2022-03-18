#include <iostream>
using namespace std;
/* Summury & explanation:
char l[] : original lights matrix;
char s[] : saving the "switch" operator which can be used when output;
bool vO(char) : 
	char r[] : saving the result of each row after switches being pressed;
	The operation: using bit-wise shift to analogue the effect of pressing of switches;
	Notify: pressing one button will cause at most 5 light to change status,
		which contains up, down, left, right, and self;
	The number 63: its binary form == 0b00111111, so that after the & operation,
		the first two digits of binary number will be set to 0; this's for dealing with
		the potential overflow (the matrix cols are 6);
	! Attention: char r[] is necessary, because the result of the "last" row operated by
		last "switch" operator should be used in the present operation;
Two basic rules for solving problem:
	1) Pressing one button twice is deprecated and useless,
		because the second press will concel the very effect of the first;
	2) The order of pressing button dosent matter;
The LOGIC of the final loop:
	When the operation combination of the first row is determined, the following row is also 
		determined because the only two chance to change the status of the first row of light 
		is when 1) the operation of the first row, 2) the pressing of the second row's button;
	Therefore, the range of enumeration is restricted in the 64 possibility of the combination
		of the first row switch operator;
		and the last row's status is the only row that should be checked;
*/
char l[5];
char s[5];

bool vO(char o){
	char r[5];
	r[0] = ::l[0];
	for (int i = 0; i < 4; ++i){
		::s[i] = o;
		r[i] = (o ^ (o << 1) ^ (o >> 1)) & 63 ^ r[i];
		r[i + 1] = ::l[i + 1] ^ o;
		o = r[i];
	}
	::s[4] = o;
	if ((o ^ (o << 1) ^ (o >> 1)) & 63 ^ r[4]) return false;
	return true;
}

int main() {
	int N;
	cin >> N;
	for (int n = 1; n <= N; ++n){
		cout << "PUZZLE #" << n << "\n" << flush;

		char p;
		for (int i = 0; i < 5; ++i){
			l[i] = 0;
			for (int j = 5; j >= 0; --j){
				cin >> p;
				l[i] |= p - 48 << j;
			}
		}
		// Final loop:
		for (char o = 0; o < 64; ++o){
			if (vO(o)){
				for (int i = 0; i < 5; ++i){
					for (int j = 5; j >=0; --j)
						cout << (s[i] >> j & 1) << " ";
					cout << "\n" << flush;
				}
				break;
			}
		}
	}
}

/*
INPUT:
2
0 1 1 0 1 0
1 0 0 1 1 1
0 0 1 0 0 1
1 0 0 1 0 1
0 1 1 1 0 0
0 0 1 0 1 0
1 0 1 0 1 1
0 0 1 0 1 1
1 0 1 1 0 0
0 1 0 1 0 0

PUZZLE #1
1 0 1 0 0 1
1 1 0 1 0 1
0 0 1 0 1 1
1 0 0 1 0 0
0 1 0 0 0 0
PUZZLE #2
1 0 0 1 1 1
1 1 0 0 0 0
0 0 0 1 0 0
1 1 0 1 0 1
1 0 1 1 0 1
*/