#include<iostream>

using namespace std;

int arr[] = {1, -2, 3, 10, -4, 7, 2, -5};

void printArr(int* bg, int* ed){
	for (; bg != ed; ++bg)
		cout << *bg << " ";
	cout << endl;
}

int calcSubSum(int* bg, int* ed){
	int sum = 0;
	for (;bg != ed; ++bg)
		sum += *bg;
	return sum;
}

void basicLoopAlg(){
	int maxSum = arr[0];
	pair<int, int> bged;
	for (int i = 1; i <= 8; ++i){
		for (int j = 0; j <= i; ++j){
			int sum = calcSubSum(arr + j, arr + i);
			if (maxSum < sum) {
				maxSum = sum;
				bged.first = j;
				bged.second = i;
			}
		}
	}
	cout << maxSum << "\n" << flush;
	printArr(arr + bged.first, arr + bged.second);
}

void dynamicProgram(){
	/*Wrong logic;*/
	int tmpSum = arr[0], tmpMax = arr[0], tmp;
	for (int i = 1; i < 8; ++i){
		tmp = tmpSum + arr[i];
		tmpSum = tmp > arr[i] ? tmp : arr[i];

		tmpMax = tmpSum > tmpMax ? tmpSum : tmpMax;
	}
	cout << tmpMax;
}

int main (){
	dynamicProgram();
}

/*
求数组最大子数组之和

      1, -2, 3, 10, -4, 7, 2, -5

 和最大的子数组为【3, 10, -4, 7, 2】

 输出为该子数组的和18

 请分别思考分治法、动态规划法及其效率
*/