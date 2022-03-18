#include<cstdio>
/*Logic: 
    This kind of Problem has its core that to select several "targets" 
    among a bunch of its kinds, and for each target, there're two "properties" of them;
    The problem will set one property as constrain and the other as the quantity that need
    to be counted;
    The core conflict is that you need to select correct handle of targets such that 
    the desired property to be max with constrain;
    
    The key is to regard both properties as bounded together as a whole target;
    In the matrix, dim-1 is the quantity of the target, and dim-2 would be the quantity of 
    the property as constrain, the elememt in the matrix is the quantity in demand;*/
short N, M, Wi, Di;
short mtx[2][12900];

int main(){
    scanf("%hd %hd", &N, &M);
    short cR = 0, rR = 1, t;
    for (int i = 0; i < N; ++i){
        scanf("%hd %hd", &Wi, &Di);
        t = cR; cR = rR; rR = t;
        short pD, cD;
        for (short j = 1; j <= M; ++j){
            pD = mtx[rR][j];
            if (j - Wi >= 0 && (cD = mtx[rR][j - Wi] + Di) > pD)
                mtx[cR][j] = cD;
            else
                mtx[cR][j] = pD;
        }
    }
    printf("%hd", mtx[cR][M]);
}

/*
N(1 ≤ N≤ 3,402) 
M(1 ≤ M≤ 12,880)

Wi(1 ≤ Wi≤ 400)
Di(1 ≤ Di≤ 100)
*/