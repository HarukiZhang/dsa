#include <iostream>
#include <bitset>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

int oriClocks[9];
int clocks[9];
const char * moves[9] = { "ABDE","ABC","BCEF","ADG","BDEFH","CFI","DEGH","GHI","EFHI" };
int moveTimes[9] = {0};
int result[9];
int minTimes = 1 << 30;
void Enum(int n) 
{
	if( n >= 9 ) {
		// copy original clock array to temp clock arr;
		memcpy(clocks,oriClocks,sizeof(clocks));
		int totalTimes = 0;
		for( int i = 0;i < 9 ; ++ i ) {
			if( moveTimes[i] ) {
				for( int k = 0; moves[i][k]; ++k) {
					// moves[i][k] : a specific move method;
					// above - 'A' : convert a char to an index;
					// use a move method according to moveTimes;
					clocks[moves[i][k] -'A'] = (clocks[moves[i][k] -'A'] + moveTimes[i]) % 4;
					totalTimes += moveTimes[i];
				}
			}
		}
		// loop to the first non-zero block;
		int i;
		for( i = 0;i < 9; ++i )
			if( clocks[i])
				break;
		if( i == 9) {// if all blocks are zero;
			// record if minimal;
			if( minTimes > totalTimes) {
				minTimes = totalTimes;
				// copy movetimes to the result array;
				memcpy(result,moveTimes,sizeof(result));
			} 
		}
		return ;// so that when n = 9 it will be the last time of recursion;
	}
	// if n < 9;
	for( int i = 0;i < 4; ++ i ) {// 4 possibilities for each Move method;
								// which are : being used for 0, 1, 2, 3 times;
		moveTimes[n] = i; // first time, n == 0;
		Enum(n+1);// recursively call;
		// And for any i == 0, 1, 2, 3, this func will recursively call from 0 to 9;
		// When n == 0, it's not a substantial disposal, it's more like a 
		// initiation process; and when n == 1 to 9 it's the actually disposal;
		// Therefore, this algo is a fully 9^4 loop enumeration;
	}
	return ;
} 
int main()
{
	for( int i = 0;i < 9 ; ++i )
		cin >> oriClocks[i];
	Enum(0);
	for( int i = 0; i < 9; ++i )
		for( int k = 0; k < result[i] ; ++ k ) 
			cout << i+1 << " ";
	return 0;
}