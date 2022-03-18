#include <iostream>
#include <vector>
#include <utility>
using namespace std;

constexpr int kMax = 52;
/*N, K for storing the max within the input data;*/
int N, K;

/*mtxGr[the num being sep][the max num of group]*/
int mtxGr[kMax][kMax];
/*Separate N int into K groups*/
void sepaInt_Gr()
{
    for (int i = 0; i <= N; ++i)
    {
        for (int j = 1; j <= K; ++j)
        {
            if (i == 0 || i == 1 || j == 1)
                mtxGr[i][j] = 1;
            else if (i < j)
                mtxGr[i][j] = mtxGr[i][i];
            else
            {
                /*Logic: compute the matrix just as the simple version of this problem;
                this problem asks for the number of method to separate N into exactly K groups;
                The simple version's matrix compute separating i when the j is the max groups;
                So, if I want to compute "i into exactly j groups", I just need to subtruct
                "i when (j-1) is max" from "i when j is max";*/
                mtxGr[i][j] = mtxGr[i][j - 1] + mtxGr[i - j][j];
            }
        }
    }
}

/*mtxDiff[the number being separated][the max item separated]*/
int mtxDiff[kMax][kMax]{1};
/*Separate N int into sum of different items*/
void sepaInt_diff()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            if (i == j)
            {
                /*When the max item == itself, only one kind of method;
                When the max item == itself - 1, find previous results;*/
                mtxDiff[i][j] = 1 + mtxDiff[i][j - 1];
            }
            /*It's impossible to separate a num i with its first item bigger than itself;
                so there's actually only 0 kinds of method*/
            else if (i < j)
                mtxDiff[i][j] = mtxDiff[i][i];
            /*When the first item separated is lesser than itself; EX: 6 == 5 + 1;*/
            else
            {
                /*After spliting out the first item, the quantity left still need to be separated;
                But in case that no duplicate, when considering the next separation, the max limit
                    should be subtructed one from the limit of last time;
                And the result of previous steps should be summed;*/
                mtxDiff[i][j] = mtxDiff[i - j][j - 1] + mtxDiff[i][j - 1];
            }
        }
    }
}

/*mtxOdd[the number being separated][the max item that is odd]*/
int mtxOdd[kMax][kMax]{1};
/*Separate N int into sum of odd numbers*/
void sepaInt_odd()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; j += 2)
        {
            if (j == 1)
                mtxOdd[i][j] = 1;
            else if (i < j)
            {
                /*Logically, here below it should be : mtx[i][j] = mtx[i][i];
                But since my mtx only records odd j col, 
                not any row i has a correspondent col i that is filled with num;
                to avoid this absence access, change to following form;*/
                mtxOdd[i][j] = mtxOdd[i][j - 2];
            }
            else
            {
                /*Pre-set each odd col in the first row into 1, which although is
                    logically uncorrect, but it's more efficient when an odd num
                    comes to itself's col (ex: i = 3, j = 3), the (0,j) can be 
                    accessed and its value is 1 to fit the requirement;*/
                mtxOdd[i][j] = mtxOdd[i][j - 2] + mtxOdd[i - j][j];
            }
        }
    }
}

int main()
{
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    // freopen("E:\\Downloads\\myout.txt", "w", stdout);

    /*Firstly, store all input data, and pick out the max N, K;
        Maybe we can only run above three function only once for each;
        and we can seach the output results according to the index;*/
    vector<pair<int, int>> myvec;
    int nIn, kIn;
    N = -1, K = -1;
    while (cin >> nIn >> kIn)
    {
        myvec.push_back(make_pair(nIn, kIn));
        if (nIn > N)
            N = nIn;
        if (kIn > K)
            K = kIn;
    }

    sepaInt_Gr();
    sepaInt_diff();
    /*mtxOdd[][] need to be initialized to 
        all odd col in the first row is 1;*/
    for (int j = 1; j < kMax; j += 2)
        mtxOdd[0][j] = 1;
    sepaInt_odd();

    for (auto it = myvec.begin(); it != myvec.end(); ++it)
    {
        int n = it->first;
        int k = it->second;
        /*EX: (5,2) == (5,1) + (3,2);*/
        int res1 = mtxGr[n - k][k];
        int res2 = mtxDiff[n][n];
        int idx = n - 1;
        if (n & 1)
            idx = n;
        int res3 = mtxOdd[n][idx];
        cout << res1 << "\n"
             << res2 << "\n"
             << res3 << "\n"
             << flush;
    }
}