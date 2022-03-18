#include<cstdio>
#include<stack>
using namespace std;

constexpr int kStrLen = 128;

/*Dynamic Programming*/
void maxSubSum_dP(){
    static int buf[kStrLen], scrollArr[2][kStrLen];

    int K, maxSum = -1, crt, last, tmp;
    scanf("%d", &K);
    for (int i = 0; i < K; ++i){
        crt = i % 2;
        last = (crt + 1) % 2;
        scanf("%d", &buf[i]);
        scrollArr[crt][0] = buf[i];
        for (int j = 1; j <= i; ++j){
            tmp = buf[i] + scrollArr[last][j - 1];
            if (tmp > scrollArr[crt][j - 1])
                scrollArr[crt][j] = tmp;
            else scrollArr[crt][j] = scrollArr[crt][j - 1];
            if (maxSum < scrollArr[crt][j]) maxSum = scrollArr[crt][j];
        }
    }
    if (maxSum < 0) maxSum = 0;
    printf("%d", maxSum);
    return;
}

/*Divide-and-Conquer*/
int maxSubSum_dac(int arr[], int left, int right){
    int leftMaxSum, rightMaxSum,
        midLeftMaxSum, midRightMaxSum,
        midLeftSum, midRightSum, midSum,
        iMid, ret;
    /*Terminal condition*/
    if (left == right){
        if (arr[left] > 0) return arr[left];
        else return 0;
    }
    /*recursion for left and right individually*/
    iMid = (left + right) / 2;
    leftMaxSum = maxSubSum_dac(arr, left, iMid);
    rightMaxSum = maxSubSum_dac(arr, iMid + 1, right);
    /*scan for cross-border max sum*/
    midLeftMaxSum = midRightMaxSum = -1;
    midLeftSum = midRightSum = 0;
    for (int i = iMid; i >= left; --i){
        midLeftSum += arr[i];
        if (midLeftSum > midLeftMaxSum) midLeftMaxSum = midLeftSum;
    }
    for (int i = iMid + 1; i <= right; ++i){
        midRightSum += arr[i];
        if (midRightSum > midRightMaxSum) midRightMaxSum = midRightSum;
    }
    midSum = midLeftMaxSum + midRightMaxSum;
    ret = leftMaxSum > rightMaxSum ?
        leftMaxSum > midSum ? leftMaxSum : midSum :
        rightMaxSum > midSum ? rightMaxSum : midSum;
    return ret;
}
/*Divide-and-Conquer nonrec*/
class MaxSubSum_DaC_NonRec {
public:
    struct Elem {
        int rd, lf, rt, maxLf, ret;
    };
private:
    stack<MaxSubSum_DaC_NonRec::Elem> nexus;
public:
    MaxSubSum_DaC_NonRec() = default;
    
    int initiate(int* arr, int lf, int rt){
        int maxMdT, maxLfT, maxRtT, mid, left, right, retVal;
        nexus.push(Elem {3, lf, rt, 0, 0});
        do {
            while ((left = nexus.top().lf) != (right = nexus.top().rt)){
                mid = (left + right) / 2;
                nexus.push(Elem {1, left, mid, 0, 0});
            }
            //if (left == right) {
            if (arr[left] > 0) nexus.top().ret = arr[left];
            else nexus.top().ret = 0;
            //} if end;
            /*Enter overall scheduling*/
            while (nexus.top().rd == 2){
                maxRtT = nexus.top().ret;
                nexus.pop();

                left = nexus.top().lf;
                right = nexus.top().rt;
                mid = (left + right) / 2;
                maxMdT = scanSum(arr, mid, left, -1)
                    + scanSum(arr, mid + 1, right, 1);
                nexus.top().ret = max3(nexus.top().maxLf, maxRtT, maxMdT);
            }
            if (nexus.top().rd == 1){
                maxLfT = nexus.top().ret;
                nexus.pop();

                right = nexus.top().rt;
                mid = (nexus.top().lf + right) / 2;
                nexus.push(Elem {2, mid + 1, right, maxLfT, 0});
            }
        } while (nexus.top().rd != 3);
        retVal = nexus.top().ret;
        nexus.pop();
        return retVal;
    }
private:
    int scanSum(int* arr, int start, int end, int dir){
        int crtSum, maxSum;
        bool (*comp)(int, int);
        if (dir != -1) comp = less_equal;
        else comp = greater_equal;
        crtSum = maxSum = 0;
        for (int i = start; comp(i, end); i = i + dir){
            crtSum += arr[i];
            if (crtSum > maxSum) maxSum = crtSum;
        }
        return maxSum;
    }
    
    int max3(int a, int b, int c){
        return a > b ? a > c ? a : c : b > c ? b : c;
    }
    
    static bool less_equal(int a, int b){ return a <= b; }
    
    static bool greater_equal(int a, int b){ return a >= b; }
};

/*Online Processing*/
void maxSubSum_ol(){
    int K, maxSum, crtSum, tmp;
    scanf("%d", &K);
    for (int i = 0; i < K; ++i){
        scanf("%d", &tmp);
        crtSum += tmp;
        if (crtSum > maxSum) maxSum = crtSum;
        else if (crtSum < 0) crtSum = 0;
    }
    if (maxSum < 0) maxSum = 0;
    printf("%d", maxSum);
    return;
}

int arr[kStrLen];

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &arr[i]);
    
    MaxSubSum_DaC_NonRec maxSubSum;
    int res = maxSubSum.initiate(::arr, 0, N - 1);
    printf("%d", res);
    return 0;
}