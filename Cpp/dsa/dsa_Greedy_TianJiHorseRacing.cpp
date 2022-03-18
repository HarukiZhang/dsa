#include<cstdio>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
/*
贪心策略：
1，如果田忌的最快马快于齐王的最快马，则两者比。
（因为若是田忌的别的马很可能就赢不了了，所以两者比）
2，如果田忌的最快马慢于齐王的最快马，则用田忌的最慢马和齐王的最快马比。
（由于所有的马都赢不了齐王的最快马，所以用损失最小的，拿最慢的和他比）
3，若相等，则比较田忌的最慢马和齐王的最慢马
    3.1，若田忌最慢马快于齐王最慢马，两者比。
    （田忌的最慢马既然能赢一个就赢呗，而且齐王的最慢马肯定也得有个和他比，所以选最小的比他快得。）
    3.2，其他，则拿田忌的最慢马和齐王的最快马比。
    （反正所有的马都比田忌的最慢马快了，所以这匹马必输，选贡献最大的，干掉齐王的最快马）
*/
vector<int> tHorses, kHorses;
int cN;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    while (true){
        scanf("%d", &cN);
        if (cN == 0) return 0;
        int inp;
        for (int i = 0; i < cN; ++i){
            scanf("%d", &inp);
            tHorses.push_back(inp);
        }
        for (int i = 0; i < cN; ++i){
            scanf("%d", &inp);
            kHorses.push_back(inp);
        }
        sort(tHorses.begin(), tHorses.end(), greater<int>());
        sort(kHorses.begin(), kHorses.end(), greater<int>());
        int bonus = 0;
        auto itTlf = tHorses.begin();
        auto itTrt = tHorses.end() - 1;
        auto itKlf = kHorses.begin();
        auto itKrt = kHorses.end() - 1;
        while (itTlf <= itTrt){
            if (*itTlf > *itKlf){
                ++bonus;
                ++itTlf;
                ++itKlf;
            }
            else if (*itTlf < *itKlf){
                --bonus;
                ++itKlf;
                --itTrt;
            }
            else {
                if (*itTrt > *itKrt){
                    ++bonus;
                    --itTrt;
                    --itKrt;
                }
                else {
                    if (*itKlf > *itTrt)
                        --bonus;
                    ++itKlf;
                    --itTrt;
                }
            }
        }
        printf("%d\n", bonus * 200);
        tHorses.clear();
        kHorses.clear();
    }
}