#include <iostream>
using namespace std;

int climbStep(int level){
	if (level == 1)
		return 1;
	else if (level == 2)
		return 2;
	else
		return climbStep(level - 1) + climbStep(level - 2);
}

int main() {
	int n;
	cin >> n;
	cout << climbStep(n);
}