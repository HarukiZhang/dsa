#include<cstdio>
#include<algorithm>
#include<functional>
using namespace std;

int numN, stdLK;

inline void swap(int* l, int* r){
    int t = *l;
    *l = *r;
    *r = t;
}

void arrangeLeft(int* pSta, int* pEnd, int base){
    int* pLf = pSta, * pRt = pEnd;
    int* lastLf, * lastRt;
    int resN;
    do {
        lastLf = pLf;
        lastRt = pRt;
        while (pLf < pRt){
            
            while (pLf < pRt && *pRt <= base) --pRt;
            swap(pLf, pRt);
            while (pLf < pRt && *pLf >= base) ++pLf;
            swap(pLf, pRt);

        }
        
        resN = 0;
        while (pSta[resN] >= base) ++resN;

        if (resN != ::stdLK){
            if (resN < ::stdLK){
                pLf = pRt + 1;
                pRt = lastRt;
                base = *pLf;
            }
            else {
                pRt = pLf - 1;
                pLf = lastLf;
                base = *pLf;
            }
        }
        
    } while (resN != ::stdLK);
}

int main() {
    int input;
    scanf("%d", &::numN);

    int* arr = new int[numN + 4];

    for (int i = 0; i < numN; ++i){
        scanf("%d", &input);
        arr[i] = input;
    }
    scanf("%d", &stdLK);
    arrangeLeft(arr, arr + (numN - 1), arr[0]);

    sort(arr, arr + stdLK, greater<int>());
    for (int i = 0; i < stdLK; ++i)
        printf("%d\n", arr[i]);
    
    delete[] arr;
}