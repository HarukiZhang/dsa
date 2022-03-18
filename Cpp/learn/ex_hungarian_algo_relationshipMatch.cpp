#include<iostream>
#include<cstring>
using namespace std;

/*girls[] store the boy matched;*/
int boyN, girlN, girls[10];
/*line[][] : for each boy, which girl he is able to match;*/
/*asked[]  : for each boy, which girl he has already asked whether she has boyfriend;*/
bool line[10][10], asked[10];

bool find(int boy){
    for (int j = 1; j <= girlN; j++){
        /*IF current boy is fond of the girl j,
            AND current boy has not yet asked this girl j whether she has a boyfriend;*/
        if (line[boy][j] == true && asked[j] == false){
            asked[j] = true;
            /*IF the girl j now has no boyfriend,
                OR the boyfriend of the girl j could change his girlfriend;*/
            if (girls[j] == 0 || find(girls[j])){
                girls[j] = boy;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cin >> boyN >> girlN;
    int ni;
    char ci;
    for (int i = 1; i <= boyN; ){
        cin >> ni;
        cin >> noskipws >> ci;
        line[i][ni] = true;
        if (ci == '\n')
            ++i;
    }
    int all = 0;
    for (int i = 1; i <= boyN; i++)
    {
        /*Reset 0 for asked[], 
        denoting that each boy has not yet asked anyone in the beginning;*/
        memset(asked, 0, sizeof(asked)); //这个在每一步中清空
        if (find(i))
            all += 1;
    }
    cout << all;
}