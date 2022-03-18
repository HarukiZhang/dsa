#include<iostream>
using namespace std;
struct Elem { char info, lf, rt; } inTree[10], tree[2][26];
int main(){
    int N, iLf, iRt;
    for (int i = 0; i < 2; ++i){
        cin >> N >> ws;
        for (int j = 0; j < N; ++j){
            cin >> inTree[j].info >> ws >> inTree[j].lf >> ws >> inTree[j].rt >> ws;
            inTree[j].lf -= '0';
            inTree[j].rt -= '0';
        }
        for (int j = 0; j < N; ++j){
            Elem& elem = tree[i][(int)(inTree[j].info - 'A')];
            iLf = (int)(inTree[j].lf);
            iRt = (int)(inTree[j].rt);
            if (iLf >= 0) elem.lf = inTree[iLf].info - 'A';
            else elem.lf = -1;
            if (iRt >= 0) elem.rt = inTree[iRt].info - 'A';
            else elem.rt = -1;
            if (elem.lf < elem.rt){
                char tmp = elem.lf;
                elem.lf = elem.rt;
                elem.rt = tmp;
            }
        }
    }
    for (int i = 0; i < 26; ++i){
        if (tree[0][i].lf != tree[1][i].lf){
            cout << "No";
            return 0;
        }
        if (tree[0][i].rt != tree[1][i].rt){
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    return 0;
}