#include<cstdio>
#include<utility>
#include<vector>

int Row, Col;
enum PostPin : bool {
    uncharted = false,
    planned = true
} guidePost[30][30];
/*26 * 26 == 676; first : col(alphabet); second : row(number);*/
std::vector<std::pair<char, int> > route;
int goalDepth, currDepth;

bool explorePath(int r, int c){

    /*Successfully moved onto a new grid*/
    guidePost[r][c] = planned;
    ++currDepth;
    route.push_back(std::make_pair(static_cast<char>(c + 'A'), r));

    /*Try all eight directions to go (start from right-low and clockwisely)*/
    if (r - 1 >= 0 && c - 2 >= 0 && guidePost[r - 1][c - 2] == uncharted)
        explorePath(r - 1, c - 2);//left-upper;
    if (r + 1 < ::Row && c - 2 >= 0 && guidePost[r + 1][c - 2] == uncharted)
        explorePath(r + 1, c - 2);//left-lower;
    if (r - 2 >= 0 && c - 1 >= 0 && guidePost[r - 2][c - 1] == uncharted)
        explorePath(r - 2, c - 1);//up-left;
    if (r + 2 < ::Row && c - 1 >= 0 && guidePost[r + 2][c - 1] == uncharted)
        explorePath(r + 2, c - 1);//down-left;
    if (r - 2 >= 0 && c + 1 < ::Col && guidePost[r - 2][c + 1] == uncharted)
        explorePath(r - 2, c + 1);//up-right;
    if (r + 2 < ::Row && c + 1 < ::Col && guidePost[r + 2][c + 1] == uncharted)
        explorePath(r + 2, c + 1);//down-right;
    if (r - 1 >= 0 && c + 2 < ::Col && guidePost[r - 1][c + 2] == uncharted)
        explorePath(r - 1, c + 2);//right-upper; 
    if (r + 1 < ::Row && c + 2 < ::Col && guidePost[r + 1][c + 2] == uncharted)
        explorePath(r + 1, c + 2);//right-lower;

    /*If eight directions have all been tried,
    judge whether the depth is enough*/
    if (currDepth != goalDepth){
        guidePost[r][c] = uncharted;
        --currDepth;
        route.pop_back();
        return false;
    }
    return true;
    /*Finally return whether the route is good*/
}

void planJourneyForKnight(){
    goalDepth = ::Row * ::Col;
    /*Pick a starting grid*/
    int rStp = (::Row + 1) / 2, cStp = (::Col + 1) / 2;
    for (int i = 0; i < rStp; ++i){
        for (int j = 0; j < cStp; ++j){

            currDepth = 0;
            if (explorePath(i, j)){
                for (auto it = route.begin(); it != route.end(); ++it)
                    printf("%c%d", it->first, it->second + 1);
                printf("\n\n");

                /*If found, guidePost wont be cleaned;*/
                for (int k = 0; k < ::Row; ++k)
                    for (int m = 0; m < ::Col; ++m)
                        guidePost[k][m] = uncharted;

                return;
            }
        }
    }
    //If all starting points cannot exhaust whole world;
    printf("impossible\n\n");
}

int main(){
    freopen("E:\\Downloads\\in.txt", "r", stdin);
    freopen("E:\\Downloads\\myout.txt", "w", stdout);
    int caseN;
    scanf("%d", &caseN);
    for (int i = 1; i <= caseN; ++i){
        /*If more case, clear the route container*/
        route.clear();
        scanf("%d %d", &::Row, &::Col);
        printf("Scenario #%d:\n", i);
        planJourneyForKnight();
    }
}

/*
描述
Background
    The knight is getting bored of seeing the same black and white squares again and again 
    and has decided to make a journey
    around the world. Whenever a knight moves, it is two squares in one direction and one 
    square perpendicular to this. The world of a knight is the chessboard he is living on. 
    Our knight lives on a chessboard that has a smaller area than a regular 8 * 8 board, but 
    it is still rectangular. Can you help this adventurous knight to make travel plans?
Problem
    Find a path such that the knight visits every square once. The knight can start and end 
    on any square of the board.

输入
The input begins with a positive integer n in the first line. The following lines contain
n test cases. Each test case consists of a single line with two positive integers p and q, 
such that 1 <= p * q <= 26. This represents a p * q chessboard, where p describes how many 
different square numbers 1, . . . , p exist, q describes how many different square letters 
exist. These are the first q letters of the Latin alphabet: A, . . .

输出
The output for every scenario begins with a line containing "Scenario #i:", where i is the 
number of the scenario starting at 1. Then print a single line containing the 
lexicographically first path that visits all squares of the chessboard with knight moves 
followed by an empty line. The path should be given on a single line by concatenating the
names of the visited squares. Each square name consists of a capital letter followed by a 
number.
If no such path exist, you should output impossible on a single line.

样例输入
3
1 1
2 3
4 3

样例输出
Scenario #1:
A1

Scenario #2:
impossible

Scenario #3:
A1B3C1A2B4C2A3B1C3A4B2C4
*/