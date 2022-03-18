#include<cstdio>
using namespace std;

long long rONu = 0LL;

/*The whole frame is the same as a mergeSort*/
void myMerge(int* arr, int st, int md, int ed, int* tmp){
    int iT = 0, iUp = st, iDw = md + 1;
    while (iUp <= md && iDw <= ed){
        if (arr[iUp] > arr[iDw]){
            /*Because that the both sides of array are oredered, for each time when 
            a value A of left array is bigger than a value B of right,
            we know that all values after the current value A in the left array
            will also be bigger than value B in the right,
            which means we need to count the number of values rest in the left array
            and add this number on to the total rONu counter*/
            ::rONu += md - iUp + 1;
            tmp[iT++] = arr[iDw++];
        }
        else 
            tmp[iT++] = arr[iUp++];
    }
    while (iUp <= md)
        tmp[iT++] = arr[iUp++];
    while (iDw <= ed)
        tmp[iT++] = arr[iDw++];
    for (int i = 0; i < iT; ++i)
        arr[st + i] = tmp[i];
}

void cntRON(int* arr, int st, int ed, int* tmp){
    if (st < ed){
        int md = (st + ed) / 2;
        cntRON(arr, st, md, tmp);
        cntRON(arr, md + 1, ed, tmp);
        myMerge(arr, st, md, ed, tmp);
    }
}

int main() {
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    int n, c;
    scanf("%d", &n);
    int* arr = new int[n + 4];
    int* tmp = new int[n + 4];
    for (int i = 0; i < n; ++i){
        scanf("%d ", &c);
        arr[i] = c;
    }
    cntRON(arr, 0, n - 1, tmp);
    //Attention: printf should use ll specifier;
    printf("%lld", ::rONu);
    
    delete[] arr;
    delete[] tmp;
}

//2638945351