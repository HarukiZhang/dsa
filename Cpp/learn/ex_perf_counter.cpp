#include <Windows.h>
#include <cstdio>
int main() {
	LARGE_INTEGER fq, t0, t1;
	QueryPerformanceFrequency(&fq);
	double freq = (double)t0.QuadPart; // freq = 1e8
	QueryPerformanceCounter(&t0);
	// module starts ...
	Sleep(10UL);
	// module ends
	QueryPerformanceCounter(&t1);
	double tspan = (double)(t1.QuadPart - t0.QuadPart) / freq; // second
	printf("%lf s", tspan);
}