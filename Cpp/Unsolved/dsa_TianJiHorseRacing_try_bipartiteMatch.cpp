#include<cstdio>
#include<algorithm>
#include<functional>
using namespace std;

int horseN, HK[1010], HT[1010];
/*favorMtx[][] :
    [][0] : the first slower K-horse;
    [][1] : the first equal K-h;*/
int favorMtx[1010][2];
/*recordK[i] = -1 : the i-th King's horse has not been matched;*/
int recordK[1010];
bool checked[1010];

bool matchTtoK(int iTJ){
    int iKg, stp = horseN;
    for (int i = 0; i < 2; ++i){
        /*The first loop access slower horses, the second, equal ones;*/
        iKg = favorMtx[iTJ][i];
        if (iKg != -1){
            for ( ; iKg < stp; ++iKg){
                if (checked[iKg] == false){
                    checked[iKg] = true;
                    if (recordK[iKg] == -1 || matchTtoK(recordK[iKg])){
                        recordK[iKg] = iTJ;
                        return true;
                    }
                }
            }
            /*If it not returned, go to access equal ones;*/
            stp = favorMtx[iTJ][0];
        }
    }
    return false;
}

void initiate(){
    sort(HT, HT + horseN, greater<int>());
    sort(HK, HK + horseN, greater<int>());

    /*i : TJ; k : King;*/
    for (int i = 0, k = 0; i < horseN; ++i){
        while (k < horseN){
            if (HK[k] <= HT[i]){
                /*(<= && !=) means <;*/
                if (HK[k] != HT[i]){
                    favorMtx[i][0] = k;
                    favorMtx[i][1] = -1;
                }
                else {
                    favorMtx[i][1] = k;
                    static int kt = k;
                    if (HT[i] != HT[i - 1]){
                        kt = k;
                        while (kt < horseN && HK[kt] == HT[i]) ++kt;
                    }
                    if (kt == horseN)
                        favorMtx[i][0] = -1;
                    else
                        favorMtx[i][0] = kt;
                }
                break;
            }
            ++k;
        }
        /*IF not a single King's horse is slower than current TJ's horse;*/
        /*k will stop at where HK[k] == HT[horse - 1];*/
        if (k == horseN){
            for (; i < horseN; ++i){
                favorMtx[i][0] = -1;
                favorMtx[i][1] = -1;
            }
        }
    }

    for (int i = 0; i < horseN; ++i)
        recordK[i] = -1;
}

int main(){
    scanf("%d", &horseN);
    for (int i = 0; i < horseN; ++i)
        scanf("%d", &HT[i]);
    for (int i = 0; i < horseN; ++i)
        scanf("%d", &HK[i]);

    //Test:
    HK[1009] = -1;

    initiate();

    for (int hTJ = 0; hTJ < horseN; ++hTJ){
        matchTtoK(hTJ);
        for (int z = 0; z < horseN; ++z)
            checked[z] = 0;
    }

    int bonus = 0;
    for (int i = 0; i < horseN; ++i){
        if (recordK[i] != -1){
            /*Subscript i of recordK denotes i-th horse of King;
              Value in recordK donotes the subscript of TJ's horse that
                matched to current King's;*/
            if (HK[i] != HT[recordK[i]])
                ++bonus;
        }
        else
            --bonus;
    }

    printf("%d\n", bonus * 200);
}