#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
struct A {
	int nouse1;
	int nouse2;
	int n;
};

void myMemcpy(char* dest, char* src, int size) {
	for (int i = 0; i < size; i++) {
		*(dest + i) = *(src + i);
	}
}

void mysort(void* ptr, int nElem, size_t size, int (*pf)(const void*, const void*)) {
	char* pDm = new char[size] {};
	char* ptar = (char*)ptr;
	for (int i = 0; i < nElem - 1; i++){
		char* pMin = ptar + i * size;
		for (int j = i + 1; j < nElem; j++) {
			char* pOffset = ptar + j * size;
			if (pf(pMin, pOffset) > 0) pMin = pOffset;
		}
		char* pPre = ptar + i * size;
		myMemcpy(pDm, pPre, size);
		myMemcpy(pPre, pMin, size);
		myMemcpy(pMin, pDm, size);
	}
	delete[] pDm;
}

int MyCompare1(const void* e1, const void* e2)
{
	int* p1 = (int*)e1;
	int* p2 = (int*)e2;
	return *p1 - *p2;
}
int MyCompare2(const void* e1, const void* e2)
{
	int* p1 = (int*)e1;
	int* p2 = (int*)e2;
	if ((*p1 % 10) - (*p2 % 10))
		return (*p1 % 10) - (*p2 % 10);
	else
		return *p1 - *p2;
}
int MyCompare3(const void* e1, const void* e2)
{
	A* p1 = (A*)e1;
	A* p2 = (A*)e2;
	return p1->n - p2->n;
}

int a[20];
A b[20];

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			b[i].n = a[i];
		}
		mysort(a, n, sizeof(int), MyCompare1);
		for (int i = 0; i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
		mysort(a, n, sizeof(int), MyCompare2);
		for (int i = 0; i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
		mysort(b, n, sizeof(A), MyCompare3);
		for (int i = 0; i < n; ++i)
			cout << b[i].n << ",";
		cout << endl;
	}
	return 0;
}

/*

*/


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件