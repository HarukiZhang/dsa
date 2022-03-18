#include<iostream>
#include<string>
#include<vector>
using namespace std;

/*Subproblem: 
    With i chars of str1 and j chars of str2, whether it is possible to form
        (i + j) chars of str3?
    Chars counting from left end;
*/

string str1, str2, str3;

bool zipper(){
    int l1 = str1.size(),
        l2 = str2.size();
    vector<vector<bool>> resMtx(l1 + 1, vector<bool>(l2 + 1, false));
    resMtx[0][0] = true;
    for (int i = 1; i <= l1; ++i)
        if (resMtx[i - 1][0] && str3[i - 1] == str1[i - 1])
            resMtx[i][0] = true;
    for (int i = 1; i <= l2; ++i)
        if (resMtx[0][i - 1] && str3[i - 1] == str2[i - 1])
            resMtx[0][i] = true;
    for (int a = 1; a <= l1; ++a){
        for (int b = 1; b <= l2; ++b){
            int idx = a + b - 1;
            if (resMtx[a - 1][b] && str3[idx] == str1[a - 1])
                resMtx[a][b] = true;
            if (resMtx[a][b - 1] && str3[idx] == str2[b - 1])
                resMtx[a][b] = true;
        }
    }
    return resMtx[l1][l2];
}

int main() {
    int n;
    cin >> n >> ws;
    for (int i = 1; i <= n; ++i){
        getline(cin, str1, ' ');
        getline(cin, str2, ' ');
        getline(cin, str3);
        cout << "Data set " << i << ": ";
        if (zipper())
            cout << "yes\n" << flush;
        else
            cout << "no\n" << flush;
    }
}