#include<iostream>
#include<cmath>
using namespace std;

double ori[4];
constexpr double eps = 1e-6;

double selectOpt(double opdlf, double opdrt, int idx){
	switch (idx) {
	case 0:
		return opdlf + opdrt;
		break;
	case 1:
		return opdlf - opdrt;
		break;
	case 2:
		return opdrt - opdlf;
		break;
	case 3:
		return opdlf * opdrt;
		break;
	case 4:
		if (opdrt == 0.0)
			return 0.0;
		else return opdlf / opdrt;
		break;
	case 5:
		if (opdlf == 0.0)
			return 0.0;
		else return opdrt / opdlf;
		break;
	default:
		cout << "operator selection error" << endl;
		return 0.0;
	}
}

bool calc24(double arr[], int n){
	if (n == 1){
		if (fabs(arr[0] - 24) < eps)
			return true;
		return false;
	}
	else {
		double temp[4];
		for (int fir = 0; fir < n - 1; ++fir){
			for (int sec = fir + 1; sec < n; ++sec){
				int restN = 0;
				for (int i = 0; i < n; ++i)
					if (i != fir && i != sec)
						temp[restN++] = arr[i];
				for (int optIdx = 0; optIdx < 6; ++optIdx){
					temp[restN] = selectOpt(arr[fir], arr[sec], optIdx);
					if (calc24(temp, restN + 1))
						return true;
				}
			}
		}
		return false;
	}
}

int main() {
	while (true) {
		int counter = 0;
		for (int i = 0; i < 4; ++i){
			cin >> ori[i];
			if (ori[i] == 0)
				++counter;
		}
		
		if (counter == 4)
			return 0;
		
		if (calc24(ori, 4))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}