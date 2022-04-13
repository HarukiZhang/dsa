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

typedef int hash_t;//differentiate indices and hash value;
constexpr int kMaxSize = 1 << 19;//use a 2**i number;
constexpr int kMask = kMaxSize - 1;//which is an all-one-string;
int recordsN;

struct Elem {
    string phoneNum;
    int callT = -1;//record calling times of the phone number;
};
int indices[kMaxSize];//the sparce table storing indices to entries;
                      //the index of arr indices is hash value;
vector<Elem> entries; //specific entry of phone number and calling times;

hash_t hashFunc(string &ph){
    int i = 6, base = 10000;//max == 99999;
    hash_t res = 0;
    //convert char str into int number;
    //count last 5 digits of phone number into play;
    for (; i < ph.length(); ++i){
        res += (ph[i] - '0') * base;
        base /= 10;
    }
    res &= kMask;//modulo using masking;
    return res;
}

/*probe and increase callT;*/
inline hash_t probe(hash_t hashC, string &ph){
    hash_t nHash = hashC;
    do {
        if (indices[nHash] != -1){//if occupied;
            //if phoneNum eq, just increase callT;
            if (entries[indices[nHash]].phoneNum == ph){
                ++entries[indices[nHash]].callT;
            }
            //else; if phoneNum neq, probe another place;
        }
        else return nHash;
        nHash = (nHash * 5 + 1) & kMask;//collision resolution;
    } while (nHash != hashC);
    return -1;//entries is full;
}

void insert(string &ph){//return idx;
    hash_t hashCode = probe(hashFunc(ph), ph);//obtain a valid hash value;
    //if ph has been inserted, callT increased within probe();
    if (hashCode != -1){//if ph has yet been inserted;
        entries.push_back(Elem{ph, 1});
        indices[hashCode] = entries.size() - 1;
    }
    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    //initialization;
    for (int i = 0; i < kMaxSize; ++i)
        indices[i] = -1;

    cin >> recordsN;
    string ph1, ph2;
    for (int i = 0; i < recordsN; ++i){
        cin >> ph1 >> ph2;
        insert(ph1);
        insert(ph2);
    }

    //search for max calling time;
    int maxCT = 0;
    string maxPH;
    int resNum = -1;

    for (Elem elem : entries){
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