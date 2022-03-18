#include<cstdio>
using namespace std;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    int dayN, maxFajoM, sumBudget = 0, money, maxM = 0;
    scanf("%d %d", &dayN, &maxFajoM);
    int* budgets = new int [dayN + 4];
    for (int i = 0; i < dayN; ++i){
        scanf("%d", &money);
        sumBudget += money;
        if (money > maxM) maxM = money;
        budgets[i] = money;
    }

    // int res = bSearch(maxM, sumBudget);
    int left = maxM, right = sumBudget,
        optim, mid, quota, curM;
    while (left <= right){
        mid = (left + right) / 2;

        quota = maxFajoM;
        curM = 0;
        bool isBdgGood;
        for (int i = 0; i < dayN; ++i){
            curM += budgets[i];
            if (curM > mid){
                curM = budgets[i];
                --quota;
            }
            else if (curM == mid){
                curM = 0;
                --quota;
            }
        }
        if (quota > 0) isBdgGood = true;
        else if (quota == 0 && curM == 0) isBdgGood = true;
        else isBdgGood = false;

        if (isBdgGood){
            optim = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    printf("%d", optim);
    delete[] budgets;
}

//OUTPUT: 59
/*INPUT:
100 10
5
9
9
9
4
2
3
2
6
8
6
5
6
5
1
2
1
9
9
7
8
3
10
8
4
3
9
5
1
10
4
3
8
5
3
7
6
4
2
8
5
4
6
1
6
10
2
3
7
2
6
3
2
8
6
5
3
8
2
1
10
7
5
2
6
1
9
9
7
3
5
2
6
6
10
8
7
9
10
5
7
6
5
5
6
10
5
4
1
9
1
8
9
3
8
10
8
4
8
6
*/