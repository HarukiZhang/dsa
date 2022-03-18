#include<cstdio>
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<algorithm>

using namespace std;
struct Pkm {
    short bCsp, attk;
};
struct Node {
    short rcvDmg, catchN;
    Node(){}
    Node(short r, short c)
        : rcvDmg(r), catchN(c){}
    Node(const Node& n){
        rcvDmg = n.rcvDmg;
        catchN = n.catchN;
    }
    void operator=(const Node& n){
        rcvDmg = n.rcvDmg;
        catchN = n.catchN;
    }
    bool operator>(const Node& n){
        if (catchN != n.catchN)
            return catchN > n.catchN;
        else
            return rcvDmg < n.rcvDmg;
    }
};

short BallN, HpM, PkmK;
Pkm pkms[110];
/*Rotating array:
    dpMtx[pkmTotN][rcvDmg][BalUsd]:
    value: maxCatchNum;*/
Node dpMtx[4][510][1010];

// struct comparePkm {
//     bool operator()(const Pkm& a, const Pkm& b){
//         if (a.attk != b.attk)
//             return a.attk < b.attk;
//         else
//             return a.bCsp < b.bCsp;
//     }
// };



void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1, const char* tag_name) {
    static double freq = -1;
    if (freq == -1) {
        LARGE_INTEGER fq;
        QueryPerformanceFrequency(&fq);
        freq = (double)fq.QuadPart;
        std::cout << "\n\n-----------------------------\n" << std::flush;
    }
    double ts = (double)(t1.QuadPart - t0.QuadPart) / freq;
    if (ts < 1) {
        ts *= 1000;
        std::cout << tag_name << ":" 
            << std::setprecision(3) << ts << " ms\n-----------------------------\n"
            << std::flush;
    }
    else std::cout << tag_name << ":" 
            << std::setprecision(3) << ts << " s\n-----------------------------\n"
            << std::flush;
    return;
}


int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);

    scanf("%hd %hd %hd", &BallN, &HpM, &PkmK);
    for (short i = 1; i <= PkmK; ++i){
        scanf("%hd %hd", &pkms[i].bCsp, &pkms[i].attk);
    }
    /*Testing result:
        Whether using sort do not interfere the result time:
            about 620 ms for both ways;*/
    sort(pkms + 1, pkms + (PkmK + 1), comparePkm());

    short icurr;
    for (short i = 1; i <= PkmK; ++i){
        short cPAtt = pkms[i].attk;
        short cPBcp = pkms[i].bCsp;

        short ilast;
        if (i & 1){
            icurr = 1;
            ilast = 0;
        }
        else {
            icurr = 0;
            ilast = 1;
        }

        for (short j = 1; j <= HpM; ++j){
            for (short k = 1; k <= BallN; ++k){
                short restHp = j - cPAtt;
                short restBN = k - cPBcp;
                if (restHp >= 0 && restBN >= 0){

                    Node tmpNode = dpMtx[ilast][restHp][restBN];
                    tmpNode.catchN += 1;
                    tmpNode.rcvDmg += cPAtt;
                    if (tmpNode > dpMtx[ilast][j][k])
                        dpMtx[icurr][j][k] = tmpNode;
                    else {
                        /*Catching the current is not better than not catching;*/
                        dpMtx[icurr][j][k] = dpMtx[ilast][j][k];
                    }
                }
                else {
                    /*Cannot catch current pkm;*/
                    dpMtx[icurr][j][k] = dpMtx[ilast][j][k];
                }
            }
        }
    }
    Node& res = dpMtx[icurr][HpM][BallN];
    // printf("%hd %hd\n", res.catchN, HpM - res.rcvDmg);


    cout << res.catchN << " " << HpM - res.rcvDmg << "\n" <<flush;
    QueryPerformanceCounter(&t1);
    printPerfCounter(t0, t1, "total");

}