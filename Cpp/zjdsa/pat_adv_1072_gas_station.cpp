#include<stdint.h>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

/*
not all correct;
probably: array overflew;
consider following situation:
    zero location;
    only one house, gas location, road;
    max houseN, gasLocM, roadsK;
    service Range max and min;
*/

constexpr int kMaxHouse = 1010, kMaxGasLoc = 16, kMaxRoad = 10010,
    kHSta = 16, kInt_Infty = ~(1 << 31);
int64_t __Infinity = 0x7FF0000000000000;
const double kDBL_Infty = *((double *)&__Infinity);

int houseN, gasLocM, roadsK, servRgDs;
int dist[kMaxGasLoc][kMaxGasLoc + kMaxHouse];
int mtxMap[kMaxGasLoc + kMaxHouse][kMaxGasLoc + kMaxHouse];

void Dijkstra(int ptr);
void record();
void read();

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    scanf("%d %d %d %d ", &houseN, &gasLocM, &roadsK, &servRgDs);
    read();
    record();
    return 0;
}

struct Elem {
    int id, dist;
    bool operator<(const Elem& e) const {//for minheap;
        return dist > e.dist;
    }
};

void Dijkstra(int ptr){
    /*initialization*/
    priority_queue<Elem> mypque;
    bool collected[kMaxGasLoc + kMaxHouse]{};//all false;
    int stp = kHSta + houseN;

    for (int i = 1; i <=stp; ++i){
        dist[ptr][i] = mtxMap[ptr][i];
    }

    /*algorithm*/
    mypque.push( Elem {ptr, 0} );
    collected[ptr] = true;
    dist[ptr][ptr] = 0;
    while ( !mypque.empty() ){
        Elem crtE = mypque.top(); mypque.pop();

        for (int i = 1; i <= stp; ++i){
            if (crtE.id != i && mtxMap[crtE.id][i] < kInt_Infty){//for each direct edge;
                if (collected[i] == false){
                    int tmpDist = crtE.dist + mtxMap[crtE.id][i];
                    if (tmpDist < dist[ptr][i]){
                        dist[ptr][i] = tmpDist;
                    }
                    mypque.push(Elem {i, dist[ptr][i]});
                    collected[i] = true;
                }
            }
        }
    }
    return;
}

void read(){

    int stp = kHSta + houseN;
    for (int i = 0; i <= stp; ++i)
        for (int j = 0; j <= stp; ++j){
            if (i == j) mtxMap[i][i] = 0;
            else mtxMap[i][j] = kInt_Infty;        
        }

    char inchar;
    int idcs[2], rLen;
    // Road road;
    for (int i = 0; i < roadsK; ++i){
        for (int k = 0; k < 2; ++k){
            inchar = getchar();
            if (inchar != 'G'){//house loc;
                ungetc(inchar, stdin);
                scanf("%d ", &idcs[k]);
                idcs[k] += kHSta;
            }
            else {//gas loc;
                scanf("%d ", &idcs[k]);
            }
        }
        scanf("%d ", &rLen);
        
        if (mtxMap[idcs[0]][idcs[1]] > rLen){
            mtxMap[idcs[0]][idcs[1]] = mtxMap[idcs[1]][idcs[0]] = rLen;
        }
    }
    return;
}

double roundnear(double x){
    int b = (int)(x * 10);
    int d = (int)(100 * x - b * 10.0);
    if (d > 4){
        return ((double)b + 1.0) / 10.0;
    }
    else {
        return (double)b / 10.0;
    }
}

void record(){
    for (int i = 1; i <= gasLocM; ++i)
        Dijkstra(i);
    
    int stp = kHSta + houseN;
    double resMax = -1.0, resAver = kDBL_Infty;
    int iD;
    for (int i = 1; i <= gasLocM; ++i){

        double min = kDBL_Infty, sum = 0.0;
        for (int j = kHSta + 1; j <= stp; ++j){
            if (dist[i][j] > servRgDs){
                min = -2.0;
                break;
            }
            sum += dist[i][j];
            if (dist[i][j] < min)
                min = dist[i][j];
        }

        if (min > resMax){
            resMax = min;
            resAver = sum / houseN;
            iD = i;
        }
        else if (min == resMax && resAver > sum / houseN){
            resAver = sum / houseN;
            iD = i;
        }
    }
    
    if (resMax > 0 && resAver > 0){
        // printf("G%d\n%.1f %.1f", iD, roundnear(resMax), roundnear(resAver));
        printf("G%d\n%.1f %.1f", iD, resMax, resAver);
    }
    else {
        printf("No Solution");
    }
    return;
}


/*Input Specification:
N (≤10^3): the total number of houses; 
M (≤10): the total number of the candidate locations for the gas stations; 
K (≤10^4): the number of roads connecting the houses and the gas stations; and 
DS: the maximum service range of the gas station.

all the houses : 1 ~ N, 
all the candidate locations : G1 ~ GM.

Then K lines follow, each describes a road in the format
    P1 P2 Dist
where P1 and P2 are the two ends of a road which can be either house numbers or 
gas station numbers, and Dist is the integer length of the road.
*/
/*Output Specification:
the first line : the index number of the best location.
the next line  : 
    between the solution and all the houses. (accurate up to 1 decimal place)
        the minimum distances
        the average distances
If the solution does not exist, simply output : No Solution.
*/
/*
Sample Input 1:
4 3 11 5
1 2 2
1 4 2
1 G1 4
1 G2 3
2 3 2
2 G2 1
3 4 2
3 G3 2
4 G1 3
G2 G1 1
G3 G2 2

Sample Output 1:
G1
2.0 3.3
*/