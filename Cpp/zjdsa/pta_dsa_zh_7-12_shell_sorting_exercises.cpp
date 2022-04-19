#include<iostream>
using namespace std;

constexpr int kMaxSize = 100010;

int N;
int origin[kMaxSize];

void shell_sort(int arr[], int size);//original shell sort;
void shell_sort_sedgewick(int arr[], int size);//shell sort with Sedgewick increment;

int get_sedgewick_given(int size, bool reboot = false);//given by ChenYue Grandma;
int get_sedgewick_1(int size, bool reboot = false);//formula 1;
int get_sedgewick_2(int size, bool reboot = false);//formula 2;

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> origin[i];
    //sorting method;
    // shell_sort(origin, N);
    shell_sort_sedgewick(origin, N);
    //....
    for (int i = 0; i < N; ++i){
        if (i) cout << ' ';
        cout << origin[i];
    }
    return 0;
}

/*test results:
测试点                   original  Sw_given  Sw_1  Sw_2
数据1：只有1个元素；	  6 	3	3	3
数据2：11个不相同的整数	  4 	5	4	3
数据3：10^3个随机整数；	  4 	4	4	3
数据4：10^4个随机整数；	  6 	5	5	6
数据5：10^5个随机整数；	  33	32	26	26
数据6：10^5个顺序整数；	  24	20	18	18
数据7：10^5个逆序整数；	  25	23	18	19
数据8：10^5基本有序整数； 22	19	17	18
数据9：10^5个随机正整数	  28	23	26	23
mean	               16.89 	14.89 	13.44 	13.22 
stdev	               11.70 	10.74 	9.54 	9.38 
*/

void shell_sort(int arr[], int size){
    for (int inc = size / 2; inc >= 1; inc >>= 1){
        for (int i = inc; i < size; ++i){
            int tmp = arr[i],
                j = i;
            for (; j >= inc && arr[j - inc] > tmp; j -= inc)
                arr[j] = arr[j - inc];
            arr[j] = tmp;
        }
    }
    return;
}

void shell_sort_sedgewick(int arr[], int size){
    int inc = get_sedgewick_1(size, true);
    while (inc >= -1){
        if (inc == -1) inc = -inc;
        for (int i = inc; i < size; ++i){
            int tmp = arr[i],
                j = i;
            for (; j >= inc && arr[j - inc] > tmp; j -= inc)
                arr[j] = arr[j - inc];
            arr[j] = tmp;
        }
        inc = get_sedgewick_1(size);
    }
    return;
}

int get_sedgewick_given(int size, bool reboot = false){
    static int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, -1, -10};
    static int i;
    if (reboot){
        i = 0;
        while (size <= Sedgewick[i]) ++i;
    }
    return Sedgewick[i++];
}

int get_sedgewick_1(int size, bool reboot = false){
    static int i;
    if (reboot){
        i = 0;
        while ( (9 * (1 << (2 * i)) - 9 * (1 << i) + 1) < size )
            ++i;
    }
    --i;
    return       9 * (1 << (2 * i)) - 9 * (1 << i) + 1;
}

int get_sedgewick_2(int size, bool reboot = false){
    static int i;
    if (reboot){
        i = 0;
        while ( ((1 << (2 * i)) - 3 * (1 << i) + 1) < size )
            ++i;
    }
    --i;
    return       (1 << (2 * i)) - 3 * (1 << i) + 1;
}