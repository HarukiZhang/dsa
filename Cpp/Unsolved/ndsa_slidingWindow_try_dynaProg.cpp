#include<cstdio>

using namespace std;
constexpr int len = 1'000'000;
int arr[len], mtx[len], mtn[len], resX[len];
int n, k;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);

    int ipj = k - 1;
    for (int i = 0; i < n; ++i){
        for (int j = i; j < n; ++j){

            if (i == j){
                mtx[j] = arr[j];
                mtn[j] = arr[j];
            }
            else {
                if (arr[j] > mtx[j - 1])
                    mtx[j] = arr[j];
                else
                    mtx[j] = mtx[j - 1];
                
                if (arr[j] < mtn[j - 1])
                    mtn[j] = arr[j];
                else
                    mtn[j] = mtn[j - 1];
            }

            if (j == ipj){
                resX[j] = mtx[j];
                printf("%d ", mtn[j]);
            }
        }
        ++ipj;
    }
    printf("\n");
    for (ipj = k - 1; ipj < n; ++ipj){
        printf("%d ", resX[ipj]);
    }
    printf("\n");
}