/*Probelm Name: Milking Grid; global No. 7736;
整个挤奶网格可以从模式 'AB'重复得来。
第一行和最后一行的A用模式‘AB’的前缀部分A得到。
即求最小覆盖矩阵。*/
#include<cstdio>

constexpr int kMR = 10'010;
constexpr int kMC = 85;

int lcm(int a, int b){
    int t, m = a * b;
    /*gcd*/
    while ((t = a % b) != 0){
        a = b;
        b = t;
    }
    /*lcm = a * b / gcd;*/
    return m / b;
}

char mtx[kMR][kMC];
int next[kMR];

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int R, C;
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; ++i)
        scanf("%s", mtx[i]);

    int ln = 1, wd = 1;
    int idx, last;
    for (int i = 0; i < R; ++i){
        /*biuld next arr for matrix;*/
        last = next[idx = 0] = -1;
        while (idx < C){
            while (last >= 0 && mtx[i][idx] != mtx[i][last])
                last = next[last];
            next[++idx] = ++last;
        }
        /*least repetitive pattern = len - next[len];
        find the least common multiple for len of pattern of each row
        to find the least len of pattern fitting whole matrix;*/
        if (ln != C - next[C])
            ln = lcm(ln, C - next[C]);
        /*if lcm is larger than len of row, trim;*/
        if (ln > C){
            ln = C;
            break;
        }
    }

    for (int j = 0; j < C; ++j){
        /*biuld next arr for transposed matrix;*/
        last = next[idx = 0] = -1;
        while (idx < R){
            while (last >= 0 && mtx[idx][j] != mtx[last][j])
                last = next[last];
            next[++idx] = ++last;
        }
        if (wd != R - next[R]) wd = lcm(wd, R - next[R]);
        if (wd > R){ wd = R; break; }
    }

    printf("%d\n", ln * wd);
    return 0;
}