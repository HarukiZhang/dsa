#include<iostream>
using namespace std;

constexpr int kMaxLen = 110;

char String[kMaxLen];
char Pattern[kMaxLen];
int nextArr[kMaxLen] = {-1};
int N;

void getNext(){
    int len = 0;
    while (Pattern[len]) ++len;
    --len;
    int i = 0, j = -1;
    while (i < len){
        while (j >= 0 && Pattern[j] != Pattern[i])
            j = nextArr[j];
        ++i;//for each loop, index i only increases 1;
        ++j;//for each loop, do not update index j;
        //ie, index j always holds it position as if i and j is individual pointer;
        //IOW, j is independent of i, rather than computing by i - 1;
        //PS, if j goto -1, ++j statement will correct its validity;
        if (Pattern[j] == Pattern[i])//compare successor of j and successor of i;
            nextArr[i] = nextArr[j];
        else nextArr[i] = j;
    }
    return;
}

char *KMP(){
    int patLen = 0;
    int iStr = 0, iPat = 0;
    while (true){
        //comparison;
        while (Pattern[iPat] && String[iStr] && Pattern[iPat] == String[iStr]){
            ++iStr;
            ++iPat;
        }
        //jump to next position to be compared;
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
    freopen("E:\\in.txt", "r", stdin);
    // ios::sync_with_stdio(false);
    // cin >> String >> N;
    // for (int i = 0; i < N; ++i){
    //     cin >> Pattern;
    //     getNext();
    //     char *res = KMP();
    //     if (res) cout << res << endl;
    //     else cout << "Not Found" << endl;
    // }

    //debug:
    cin >> N;
    cin >> Pattern;
    getNext();
    for (int i = 0; i < N; ++i){
        if (nextArr[i] < 0) cout << ' ' << nextArr[i];
        else cout << "  " << nextArr[i];
    }
    return 0;
}

/*
 a  b  c  a  a  b  a  b  c
-1  0  0  0  1  1  2  1  2
-1  0  0 -1  1  0  2  0  0

-1  0  0 -1  1  0  2  0  0
*/