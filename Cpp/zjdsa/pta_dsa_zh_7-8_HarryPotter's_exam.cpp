#include<iostream>
using namespace std;

constexpr int kMaxAnimalNum = 100, kMaxSpellLen = 100, INFTY = kMaxSpellLen * 10;

int minMtx[kMaxAnimalNum + 10][kMaxAnimalNum + 10];

void Floyd(int len){
    for (int k = 0; k < len; ++k){//iterate each vertex;
        for (int i = 0; i < len; ++i){//scan minMtx row;
            for (int j = 0; j < len; ++j){//scan minMtx col;
                int tmp = minMtx[i][k] + minMtx[k][j];
                if ( tmp < minMtx[i][j])
                    minMtx[i][j] = tmp;
            }
        }
    }
    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N, M, v1, v2, spellLen;
    cin >> N >> M;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (i == j) minMtx[i][j] = 0;
            else minMtx[i][j] = INFTY;
        }
    }
    for (int i = 0; i < M; ++i){
        cin >> v1 >> v2 >> spellLen;
        minMtx[v1 - 1][v2 - 1] = spellLen;
        minMtx[v2 - 1][v1 - 1] = spellLen;
    }
    Floyd(N);
    /*if after Floyd, minMtx still contains INFTY, 
        suggest impossible to only pick one animal;*/
    int optmLen = INFTY, optmAnimal;
    for (int i = 0; i < N; ++i){
        int difficulty = 0;
        for (int j = 0; j < N; ++j){
            if (minMtx[i][j] == INFTY){
                cout << 0 << endl;
                return 0;
            }
            if (minMtx[i][j] > difficulty) difficulty = minMtx[i][j];
        }
        if (difficulty < optmLen){
            optmLen = difficulty;
            optmAnimal = i;
        }
    }
    cout << optmAnimal + 1 << " " << optmLen << endl;

    // /*debug*/
    // cout << endl;
    // for (int i = 0; i < N; ++i){
    //     for (int j = 0; j < N; ++j){
    //         cout << minMtx[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    return 0;
}