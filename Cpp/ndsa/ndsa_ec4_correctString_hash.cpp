#include<iostream>

using namespace std;


int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    bool hashTbl[128]{};
    int nLine;
    char homeworks[64][64];
    char tmplt[64];
    cin >> nLine >> ws;
    for (int i = 0; i < nLine; ++i){
        cin.getline(homeworks[i], 50);
    }
    cin.getline(tmplt, 50);

    int iLf, iRt;
    for (iLf = 0; tmplt[iLf]; ++iLf){
        if (tmplt[iLf] == '['){
            iRt = ++iLf;
            while (tmplt[iRt] != ']'){
                char tmp = tmplt[iRt];
                
                hashTbl[tmp] = true;
                if (tmp > 'Z')
                    hashTbl[tmp - 32] = true;
                else if (tmp > '9')
                    hashTbl[tmp + 32] = true;

                ++iRt;
            }
            break;
        }
        else if (tmplt[iLf] > 'Z'){
            tmplt[iLf] -= 32;
        }
    }
    for (++iRt; tmplt[iRt]; ++iRt, ++iLf){
        tmplt[iLf] = tmplt[iRt];
        if (tmplt[iLf] > 'Z')
            tmplt[iLf] -= 32;
    }
    tmplt[iLf] = '\0';

    for (int i = 0; i < nLine; ++i){
        int iT = 0, iH = 0;
        while (iT <= iLf){
            if (tmplt[iT] == '['){
                if (!hashTbl[homeworks[i][iH]])
                    break;
            }
            else {
                char test = homeworks[i][iH];
                if (test > 'Z')
                    test -= 32;
                if (test != tmplt[iT])
                    break;
            }
            ++iT;
            ++iH;
        }
        if (iT == iLf + 1){
            cout << i + 1 << ' ' << homeworks[i] << endl;
        }
    }
}