#include <map>
#include <cstdlib>

int main() {
    std::multimap<int, int> memsht; //first:attack; second:memID;
    memsht.insert(std::make_pair(1000000000, 1));
    int nMem;
    scanf("%d", &nMem);
    for (int i = 0; i < nMem; i++) {
        int memId, memAtt;
        scanf("%d %d", &memId, &memAtt);
        //firstly search for appropriate member ID in the map;
        int idApprop;
        auto iterPair = memsht.equal_range(memAtt);
        if (iterPair.first == iterPair.second) { // key not found; need to reset the iterator pair;
            int refind1, refind2;
            if (iterPair.first == memsht.begin()) {
                refind1 = (refind2 = (iterPair.first)->first);
            }
            else if (iterPair.first == memsht.end()) {
                refind1 = (refind2 = (--(iterPair.first))->first);
            }
            else {
                auto itAft = iterPair.first;
                auto itBef = --(iterPair.first);
                int distA = abs(itAft->first - memAtt);
                int distB = abs(itBef->first - memAtt);
                if (distA != distB) {
                    refind1 = (distA < distB) ? itAft->first : itBef->first;
                    refind2 = refind1;
                }
                else {
                    refind1 = itBef->first;
                    refind2 = itAft->first;
                }
            }
            // starting refind:
            if (refind1 != refind2) {
                auto it_ref1 = memsht.lower_bound(refind1);
                auto it_ref2 = memsht.upper_bound(refind2);
                iterPair = std::make_pair(it_ref1, it_ref2);
            }
            else iterPair = memsht.equal_range(refind2);
        }
        // then iterate in the range(equal or nonequal) to find the appropriate ID;
        idApprop = (iterPair.first)->second;
        for (auto it = ++(iterPair.first); it != iterPair.second; it++) {
            int preId = it->second;
            if (preId < idApprop) idApprop = preId;
        }
        // output the found
        printf("%d %d\n", memId, idApprop);
        //then consider insert the present member;
        memsht.insert(std::make_pair(memAtt, memId));
    }
    return 0;
}

/*
两人的实力值可以相同。
另外，每个人都有一个唯一的id，也是一个正整数。
为了使得比赛更好看，每一个新队员都会选择与他实力最为接近的人比赛，
即比赛双方的实力值之差的绝对值越小越好，如果有多个人的实力值与他差别相同，则他会选择id最小的那个。

不幸的是，Facer一不小心把比赛记录弄丢了，但是他还保留着会员的注册记录。
现在请你帮facer恢复比赛纪录，按照时间顺序依次输出每场比赛双方的id。

输入
第一行一个数n(0 < n <=100000)，表示格斗场新来的会员数（不包括facer）。
以后n行每一行两个数，按照入会的时间给出会员的id和实力值。
一开始，facer就算是会员，id为1，实力值1000000000。输入保证两人的实力值不同。

输出
N行，每行两个数，为每场比赛双方的id，新手的id写在前面。

样例输入
3
2 1
3 3
4 2
样例输出
2 1
3 2
4 2
*/