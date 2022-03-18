#include<cstdio>
int chBL, piecN;
char chesBrd[10][10];
/*false : unavailable for putting a piece; true : available*/
bool ctrlTbl[10][10];
int depth, methods;

/*WHEN the piece number == the chessboard length*/
void setPieces(int r){
    for (int i = 0; i < chBL; ++i){
        /*IF (current place is a grid) AND (the place is available)*/
        if (chesBrd[r][i] != '.' && ctrlTbl[r][i]){
            ++depth;
            /*Mark the grid that is watched by current piece*/
            for (int j = r + 1; j < chBL; ++j)
                ctrlTbl[j][i] = false;
            /*No need to set whole row of ctrlTbl to be true*/
            /*go to next row*/
            if (r + 1 < chBL)
                setPieces(r + 1);
            
            if (depth == piecN)
                ++methods;
            
            /*Unmark the grid*/
            --depth;
            for (int j = r + 1; j < chBL; ++j)
                ctrlTbl[j][i] = true;
        }
    }
    /*Under the condition that piecN == chBL, which means every row has to contain one piece;
    IF there is a row where there's no place for putting a piece,
    it is impossible to put all pieces into this chessboard;*/
}

/*WHEN the piece number < the chessboard length*/
void setPieces_UB(int startRow, int restPieceN){
    for (int i = startRow; i < chBL; ++i){//for row index;
        /*Here, the current row has not been put any piece;
        So, only when restPieceN <= chBL - i, the chessboard can
            contain all remaining pieces;*/
        if (restPieceN > chBL - i)
            return;
        
        for (int j = 0; j < chBL; ++j){//col index;

            if (chesBrd[i][j] != '.' && ctrlTbl[i][j]){
                ++depth;
                for (int k = i + 1; k < chBL; ++k)
                    ctrlTbl[k][j] = false;

                if (restPieceN > 0 && restPieceN - 1 <= chBL - i - 1)
                    setPieces_UB(i + 1, restPieceN - 1);
                
                if (depth == piecN)
                    ++methods;

                --depth;
                for (int k = i + 1; k < chBL; ++k)
                    ctrlTbl[k][j] = true;
            }
        }
    }
}

int main(){
    
    while (true){
        scanf("%d %d", &chBL, &piecN);
        if (chBL == -1)
            return 0;
        
        for (int i = 0; i < chBL; ++i)
            scanf("%s", chesBrd[i]);
        
        depth = 0;
        methods = 0;
        for (int i = 0; i < chBL; ++i)
            for (int j = 0; j < chBL; ++j)
                ctrlTbl[i][j] = true;
        
        setPieces_UB(0, piecN);

        printf("%d\n", methods);
    }
}
/*
描述
在一个给定形状的棋盘（形状可能是不规则的）上面摆放棋子，棋子没有区别。
要求摆放时任意的两个棋子不能放在棋盘中的同一行或者同一列，请编程求解对于给定形状和大小的棋盘，
摆放k个棋子的所有可行的摆放方案C。

输入
输入含有多组测试数据。
每组数据的第一行是两个正整数，n k，用一个空格隔开，表示了将在一个n*n的矩阵内描述棋盘，
以及摆放棋子的数目。 n <= 8 , k <= n
当为-1 -1时表示输入结束。
随后的n行描述了棋盘的形状：每行有n个字符，其中
    # 表示棋盘区域，
    . 表示空白区域（数据保证不出现多余的空白行或者空白列）。

输出
对于每一组数据，给出一行输出，输出摆放的方案数目C （数据保证C<2^31）。
样例输入
2 1
#.
.#
4 4
...#
..#.
.#..
#...
-1 -1
样例输出
2
1
*/