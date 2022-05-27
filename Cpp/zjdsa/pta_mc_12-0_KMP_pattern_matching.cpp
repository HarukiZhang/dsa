#include<iostream>
using namespace std;

constexpr int kMaxLen = 110;

char String[kMaxLen];
char Pattern[kMaxLen];
int nextArr[kMaxLen] = {-1};
int N;

void getNext(){
    for (int i = 1; Pattern[i]; ++i){       
        int j = i;
        while (nextArr[j] >= 0 && Pattern[nextArr[j]] != Pattern[i])
            j = nextArr[j];
        nextArr[i + 1] = nextArr[j] + 1;
    }
    return;
}

char *KMP(){
    int patLen = 0;
    int iStr = 0, iPat = 0;
    while (true){
        while (Pattern[iPat] && String[iStr] && Pattern[iPat] == String[iStr]){
            ++iStr;
            ++iPat;
        }
        if (!Pattern[iPat]){
            while (Pattern[patLen++]);
            --patLen;
            return String + (iStr - patLen);
        }
        else if (!String[iStr])
            return nullptr;
        else {
            iPat = nextArr[iPat];
            if (iPat == -1){
                iPat = 0;
                ++iStr;
            }
        }
    }
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> String >> N;
    for (int i = 0; i < N; ++i){
        cin >> Pattern;
        getNext();
        char *res = KMP();
        if (res) cout << res << endl;
        else cout << "Not Found" << endl;
    }
    return 0;
}

/*
 a b c  a a b a b c
-1 0 0  0 1 1 2 1 2
-1 0 0 -1 1 0 2 0 0

-1 0 0  0 -1 0 0 -1 0 0 

-1 0 0  0 1 1 2 1 2 3
*/