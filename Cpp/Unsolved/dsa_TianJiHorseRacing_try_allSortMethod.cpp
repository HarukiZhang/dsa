/*
The horse racing problem can be simply viewed as finding the maximum matching in a 
bipartite graph. Draw Tian's horses on one side, and the king's horses on the other. 
Whenever one of Tian's horses can beat one from the king, we draw an edge between them, 
meaning we wish to establish this pair. Then, the problem of winning as many rounds as 
possible is just to find the maximum matching in this graph. 
If there are ties, the problem becomes more complicated, he needs to assign weights 
0, 1, or -1 to all the possible edges, and find a maximum weighted perfect matching...

However, the horse racing problem is a very special case of bipartite matching. 
The graph is decided by the speed of the horses -- a vertex of higher speed always beat 
a vertex of lower speed. In this case, the weighted bipartite matching algorithm is a 
too advanced tool to deal with the problem.

In this problem, you are asked to write a program to solve this special case of 
matching problem.

输入
The input consists of up to 50 test cases. 
Each case starts with a positive integer n ( n<=1000) on the first line, 
which is the number of horses on each side. 
The next n integers on the second line are the speeds of Tian's horses. 
Then the next n integers on the third line are the speeds of the king's horses. 
The input ends with a line that has a single `0' after the last test case.

输出
For each input case, output a line containing a single number, 
which is the maximum money Tian Ji will get, in silver dollars.
*/

#include<iostream>
#include<map>
using namespace std;

int HorseN;
/*true : TianJi; false : King;*/
multimap<int, bool, greater<int> > myMap;

int main(){
    cin >> HorseN;
    int inp, bonus = 0;
    for (int i = 0; i < HorseN; ++i){
        cin >> inp;
        myMap.insert(make_pair(inp, true));
    }
    for (int i = 0; i < HorseN; ++i){
        cin >> inp;
        myMap.insert(make_pair(inp, false));
    }

    /*Match each Tian's horse to the first King's h;*/

    auto itT = myMap.begin();
    auto itK = itT;
    while (itK != myMap.end()){
        /*Tian's iterator jump over all King's horses;*/
        while (itT != myMap.end() && !itT->second) ++itT;
        if (itT == myMap.end()) break;
        itK = itT;
        /*King's iterator jump over all Tian's horses;*/
        while (itK != myMap.end() && itK->second) ++itK;
        if (itK == myMap.end()) break;

        if (itK->first == itT->first){
            auto it = itT;
            ++it;
            while (it != myMap.end() && !it->second) ++it;
            if (it == myMap.end()){
                /*Tie*/
                itK = myMap.erase(itK);
                itT = myMap.erase(itT);
            }
            else if (it->first == itT->first){
                /*Tie*/
                itK = myMap.erase(itK);
                itT = myMap.erase(itT);
            }
            else {
                /*Beat*/
            }
        }
        else {
            /*Beat*/
        }


        /*If Tian's current fastest horse ties with King's horse;*/
        if (itK->first == itT->first){
            /*Find next Tian's horse and next King's horse, compare them to dicide;*/
            auto itTn = itT, itKn = itK;
            while (itTn->first == itKn->first){
                ++itTn; ++itKn;
                while (itKn != myMap.end() && itKn->second) ++itKn;
                while (itTn != myMap.end() && !itTn->second) ++itTn;
                /*Till the end, were Tian's horses all as fast as King's horses;
                    Since we start from Tian's first fastest horse, and two sides have
                    the same number of horses, Tian's seq wont stop earlier than King's;*/
                if (itKn == myMap.end()){
                    /*Let all horses that are equal at speed to tie;*/
                    while (itK != myMap.end() && itK->first == itT->first){
                        itK = myMap.erase(itK);
                        itT = myMap.erase(itT);
                        while (itK != myMap.end() && itK->second) ++itK;
                        while (itT != myMap.end() && !itT->second) ++itT;
                    }
                    goto endloop;
                }
            }
            /*Branch other from being goto endloop, is that:
                itKn != .end() && Tian's speed!= King's;*/
            /*If Tian's is faster than King's, let the beginning equal two to tie;*/
            if (itTn->first > itKn->first){
                while (itK != myMap.end() && itK->first == itT->first){
                    itK = myMap.erase(itK);
                    itT = myMap.erase(itT);
                    while (itK != myMap.end() && itK->second) ++itK;
                    while (itT != myMap.end() && !itT->second) ++itT;
                }
            }
            /*If King's is faster, let beginning equal Tian's beat the next slower King's;
                After above while-loop, two sides wont be same at speed;*/
            else {
                ++itK;
                while (itK->second) ++itK;
                bonus += 200;
                itK = myMap.erase(itK);
                itT = myMap.erase(itT);
            }
        }
        else {
            bonus += 200;
            /*Erase itK firstly for itK is generally on the right of itT,
            so that it wont happen that after itT has been erased, itT
            pointed to the place where itK is pointing, and if then to
            erase itK, it will case itT invalid;*/
            itK = myMap.erase(itK);
            itT = myMap.erase(itT);
        }
    }
    endloop:
    /*While in above loop, it has all been enumerated that possibilities of tie,
        if after while-loop ending, there's still horses in myMap, Tian will lose them;*/
    int restPairs = myMap.size();
    bonus -= restPairs * 100;

    cout << bonus << "\n" << flush;
    
}

/*
样例输入
3
92 83 71
95 87 74
2
20 20
20 20
2
20 19
22 18
0
样例输出
200
0
0
*/