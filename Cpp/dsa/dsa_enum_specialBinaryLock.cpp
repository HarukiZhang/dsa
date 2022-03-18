#include <iostream>
#include <bitset>

using namespace std;
/* Problem description
有一种特殊的二进制密码锁，由n个相连的按钮组成（n<30），
按钮有凹/凸两种状态，用手按按钮会改变其状态。

然而让人头疼的是，当你按一个按钮时，跟它相邻的两个按钮状态也会反转。
当然，如果你按的是最左或者最右边的按钮，该按钮只会影响到跟它相邻的一个按钮。

当前密码锁状态已知，需要解决的问题是，你至少需要按多少次按钮，才能将密码锁转变为所期望的目标状态。

输入
两行，给出两个由0、1组成的等长字符串，表示当前/目标密码锁状态，其中0代表凹，1代表凸。
输出
至少需要进行的按按钮操作次数，如果无法实现转变，则输出impossible。
样例输入
011
000
样例输出
1
*/

/* Present Problem
How to reduce the potential trials ?
	Actually this is a light-putting-off problem, only to rotate the lock to vertical direction;
	In the LPO problem, we need to enumerate only the first row's pattern;
	While in this problem, we just need to enum the first ONE button (whether press or not);
	And then, for the rest buttons, whether pressing them depends on the last batton status;
	If the last button is same as the goal, you dont need to press the present one;
	If the last button is not same as the goal, you need to press the present so that
		this press will set the last the same as the goal;
	Till the end, if finally the after-pressing is becoming the same as the goal status,
		count the times of pressing, if not, it means it's impossible to resolve;
*/ 

// one int has 32 bits for storing 0/1;
// using small-end-storage method : high digit stores in the left end;
// using digit to control output;
constexpr int kEraser = 0x3fffffff;
constexpr int slider = 1;


int readin(int& buff){// return the digit;
	char inputc[32];
	cin >> inputc;
	int digit = 0;
	char input;
	for (int i = 0; inputc[i]; ++i){
		buff |= inputc[i] - '0' << i;
		++digit;
	}
	return digit;
}

void putout(int lockB, int dig){
	for (int i = 0; i < dig; ++i)
		cout << (lockB >> i & slider) << " ";
	cout << "\n" << flush;
}

int genButton(int locPatt){
	// return the effect after pressing the button pattern;
	// in effect pattern, 1 for inversion 0 for not;
	// param is a pattern of where to press;
	// in param pattern, 1 for pressing 0 for not;
	return (locPatt ^ locPatt << 1 ^ locPatt >> 1) & kEraser;
}

int getBit(int buff, int offset){
	return buff >> offset & 1;
}

int pressButton(int lockBase, int offset){//return the result after pressing
	int buttB = 1 << offset;
	int button = (buttB ^ buttB << 1 ^ buttB >> 1) & kEraser;
	return lockBase ^ button;
}

int main() {
	int lockStart = 0, lockGoal = 0;
	int digit = readin(lockStart);
	readin(lockGoal);

	int num0 = 0, num1 = 0;
	for (int j = 0; j < 2; ++j){// loop twice: one for pressing the first, one for not;
		int lockTmp = lockStart;
		if (j){// when j = 0, try not to press the first button;
			lockTmp = pressButton(lockTmp, 0);
			++num1;
		}
		for (int i = 1; i < digit; ++i){
			// compare the last button status, if it's not same as the goal;
			if (getBit(lockTmp, i - 1) != getBit(lockGoal, i - 1)){
				lockTmp = pressButton(lockTmp, i);
				if (j)
					++num1;
				else
					++num0;
			}
		}
		// check the whole lock status;
		if (lockTmp != lockGoal){
			// if it's not the solution, use num0/1 as flag set to 100 denoting "no solution";
			if (j)
				num1 = 100;
			else
				num0 = 100;
		}
	}

	int min = num0 < num1 ? num0 : num1;

	if (min < 100)
		cout << min;
	else
		cout << "impossible";
}