#include<cstdio>
/*
You can only put your feet on a Black tile;
1）‘.’：黑色的瓷砖；
2）‘#’：白色的瓷砖；
3）‘@’：黑色的瓷砖，并且你站在这块瓷砖上。
*/
using namespace std;

short W, H;
/*input content : innate or wall; '\r' : explored*/
char bwFloor[22][22];
// bool guidePost[22][22];
short depth = 0;

void rAndB(short w, short h){
    /*position already explored*/
    if (bwFloor[h][w] == '\r')
        return;
    //else : innate : set the post CARRIAGE RETURN;
    bwFloor[h][w] = '\r';
    /*For every step on a new innate post*/
    ++depth;

    /*Clockwise order*/
    /*When index decrement, there's possi that it's out of range;*/
    if (h - 1 >= 0 && bwFloor[h - 1][w] != '#')
        rAndB(w, h - 1);//up
    /*only four possi. when w + 1: '\0', '.', '#', '@';
        go further along this route only when '.';*/
    if (bwFloor[h][w + 1] == '.')
        rAndB(w + 1, h);//right
    if (bwFloor[h + 1][w] == '.')
        rAndB(w, h + 1);//down
    if (w - 1 >= 0 && bwFloor[h][w - 1] != '#')
        rAndB(w - 1, h);//left

    return;
}

int main() {
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    while (true){
        scanf("%hd %hd", &W, &H);
        if (W == 0 && H == 0)
            return 0;
        for (short k = 0; k < 22; ++k)
            bwFloor[H][k] = 0;
        char c;
        short mW, mH;
        for (short i = 0; i < H; ++i){
            scanf("%s", bwFloor[i]);
            for (short j = 0; j < W; ++j){
                if (bwFloor[i][j] == '@'){
                    mW = j;
                    mH = i;
                }
            }
        }
        depth = 0;
        rAndB(mW, mH);
        printf("%hd\n", depth);
    }
}