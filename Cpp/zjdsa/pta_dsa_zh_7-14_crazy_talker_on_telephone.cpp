/*
给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。

输入格式:
输入首先给出正整数N（≤10 
5
 ），为通话记录条数。随后N行，每行给出一条通话记录。简单起见，
 这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。

输出格式:
在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。
如果这样的人不唯一，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;

constexpr int kMaxSize = 200003;//prime num;
int recordsN;

struct Elem {
    string phoneNum;
    int callT = -1;
};
// Elem hashTbl[kMaxSize];
vector<Elem> hashTbl[kMaxSize];

int hashFunc(string &ph){
    int i = 6, base = 10000;
    size_t res = 0ULL;
    for (; i < ph.length(); ++i){
        res += (ph[i] - '0') * base;
        base /= 10;
    }
    res %= (size_t)kMaxSize;
    return (int)res;
}

/*didn't use; for probing may not find new place for some cases;*/
inline int probe(int idx){
    int m1 = -1, ofsBase = 1, cnt = 0, ofs, nidx;
    while (ofsBase <= kMaxSize / 2){
        if (cnt & 1){//odd;
            ofs = ofsBase * ofsBase * m1;
            ++ofsBase;
        }
        else {//even;
            ofs = ofsBase * ofsBase;
        }
        nidx = (idx + kMaxSize + ofs) % kMaxSize;
        if (hashTbl[nidx].empty())
            return nidx;
        ++cnt;
    }
    return -1;
}

int insert(string &ph){//return idx;
    int idx = hashFunc(ph);
    if (!hashTbl[idx].empty()){//crt idx is occupied;
        bool isIn = false;
        for (Elem &elem : hashTbl[idx]){
            if (elem.phoneNum == ph){
                ++elem.callT;
                isIn = true;
                break;
            }
        }
        if (!isIn)
            hashTbl[idx].push_back(Elem {ph, 1});
    }
    else {//crt idx is valid;
        hashTbl[idx].push_back(Elem {ph, 1});
    }
    return idx;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);

    cin >> recordsN;
    string ph1, ph2;
    for (int i = 0; i < recordsN; ++i){
        cin >> ph1 >> ph2;
        insert(ph1);
        insert(ph2);
    }

    int maxCT = 0;
    string maxPH;
    int resNum = -1;

    for (int i = 0; i < kMaxSize; ++i){
        if (!hashTbl[i].empty()){
            for (Elem elem : hashTbl[i]){
                if (elem.callT > maxCT){
                    maxCT = elem.callT;
                    maxPH = elem.phoneNum;
                    resNum = 1;
                }
                else if (elem.callT == maxCT){
                    ++resNum;
                    if (elem.phoneNum < maxPH)
                        maxPH = elem.phoneNum;
                }
            }
        }
    }

    cout << maxPH << " " << maxCT;
    if (resNum > 1) cout << " " << resNum;

    return 0;
}

/*
输入样例:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
输出样例:
13588625832 3
*/