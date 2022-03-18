#include<cstdio>
using namespace std;
int buf[10010], arr[2][10010];
int main(){
    int K, start, last, maxSum, tmp, crt, prev;
    scanf("%d", &K);
    maxSum = 1 << 31;
    for (int i = 0; i < K; ++i){
        scanf("%d", &buf[i]);
        crt = i % 2;
        prev = (crt + 1) % 2;
        arr[crt][0] = buf[i];
        if (maxSum < buf[i]){
            maxSum = buf[i];
            start = i;
            last = i;
        }
        for (int j = 1; j <= i; ++j){
            arr[crt][j] = buf[i] + arr[prev][j - 1];
            if (maxSum < arr[crt][j]){
                maxSum = arr[crt][j];
                start = i - j;
                last = i;
            }
            else if (maxSum == arr[crt][j] && start > i - j) start = i - j;
        }
    }
    if (maxSum < 0){
        maxSum = 0;
        start = 0;
        last = K - 1;
    }
    printf("%d %d %d\n", maxSum, buf[start], buf[last]);
}