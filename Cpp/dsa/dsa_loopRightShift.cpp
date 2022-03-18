#include <iostream>
#include <iomanip> 
#include <cstring>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <type_traits>

using namespace std;

// template <class Type>
// class Item {
// private:
// 	Type key; //关键码域
// 	           // 其他域
// public:
// 	Item(Type value) : key(value) {}
// 	Type getKey() { //取关键码值
// 		return key;
// 	}
// 	void setKey(Type k) { //置关键码
// 		key = k;
// 	}
// };
// template <class Type>
// int SeqSearch(vector<Item<Type>*>& dataList, int length, Type k) {
// 	int i = length;
// 	dataList[0]->setKey(k); //将第0元素设为带检索值，设监视哨
// 	while (dataListp[i]->getKey() != k)
// 		--i;
// 	return i; //返回元素位置
// }
// vector<Item<int>*> dataList;

// template <class Type>
// int BinSearch(vector<Item<Type>*>& dataList, int length, Type k) {
// 	int low = 1, high = length, mid;
// 	while (low <= high) {
// 		mid = (low + high) / 2;
// 		if (k < dataList[mid]->getKey())
// 			high = mid - 1; //右缩检索区间
// 		else if (k > dataList[mid]->getKey())
// 			low = mid + 1; //左缩检索区间
// 		else return mid; // 成功则返回当前位置
// 	}
// 	return 0; //检索失败
// }

// void BracketMatch(char* str){
// 	SeqStack S;
// 	int i;
// 	char ch;
// 	InitStack(&S);
// 	for (i = 0; str[i] != '\0'; ++i) {
// 		switch(str[i]) {
// 		case '(': case '[': case '{':
// 			Push(&S, str[i]);
// 			break;
// 		case ')': case ']': case '}':
// 			if (IsEmpty(&S)) {
// 				printf("\n右括号多余！");
// 				return;
// 			} else {
// 				GetTop(&S, &ch);
// 				if (Match(ch, str[i]))
// 					Pop(&S, &ch);
// 				else {
// 					printf("\n括号不匹配！");
// 					return;
// 				}
// 			} // else end
// 		} //switch end
// 	} //for end
// 	if (IsEmpty(&S))
// 		printf("\n括号匹配！");
// 	else printf("\n左括号多余");
// }

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
            << std::setprecision(5) << ts << " ms\n-----------------------------\n"
            << std::flush;
    }
    else std::cout << tag_name << ":" 
            << std::setprecision(5) << ts << " s\n-----------------------------\n"
            << std::flush;
    return;
}

void myswap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void popSort(int* start, int* tail, int times){
	for (int i = 0; i < times; ++i){
		for (int* ptr = start; ptr != tail; ++ptr){
			if (*ptr > *(ptr + 1)) myswap(ptr, ptr + 1);
		}
	}
}

void loopRightShift(int* start, int length, int dig){
	dig %= length;
	if (dig == 0) return;
	int popTimes, swapGoal, tailOffset;
	bool flag = (dig >= (length + 1) / 2);
	if (flag) {
		popTimes = length - dig;
		swapGoal = length - dig;
		tailOffset = dig;
	} else {
		popTimes = length % dig;
		swapGoal = length;
		if (popTimes) swapGoal = length - dig * 2;
		tailOffset = length - dig;
	}
	int offset = 0;
	while (offset < swapGoal){
		
		for (
			int* tailStart = start + tailOffset;
			tailStart != start + length;
			++tailStart, ++offset
		){
			myswap(start + offset, tailStart);
		}
	}
	if (flag)
		popSort(start, start + dig - 1, popTimes);
	else
		popSort(start + offset, start + length - 1, popTimes);
	return;
}

constexpr int kLength = 4000;
int arr[kLength];

int main() {
	// int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	LARGE_INTEGER t0, t1;
	for (int i = 0; i < kLength; ++i){
		arr[i] = i;
	}

	QueryPerformanceCounter(&t0);

	// for (int j = 1; j < kLength; ++j){
		// cout << "right Shift " << setw(2) << j << " : ";


		loopRightShift(arr, kLength, 1998);


		// for (int i = 0; i < length; ++i)
		// 	cout << arr[i] << " ";
		// cout << endl;	
		// sort(arr, arr + length);
	// }

	QueryPerformanceCounter(&t1);

	printPerfCounter(t0, t1, "Total ");
}