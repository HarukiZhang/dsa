#include<iostream>
#include<string>
#include<vector>
using namespace std;

constexpr int kMaxLen = 1 << 18, kMask = kMaxLen - 1;

typedef unsigned int hash_t;

struct ENode {
    hash_t hash;
    string phoneNo;
    int times = 0;
};

int indices[kMaxLen]{};
vector<ENode> entries;

inline hash_t hash_func(const string &str){
    //use last 5 digits as hash value;
    int base = 1;
    hash_t ret = 0;
    for (int i = 10; i > 5; --i){
        ret += (str[i] - '0') * base;
        base = (base << 1) + (base << 3);
    }
    return ret;
}

inline int probe(hash_t &idx, const string &phoneN){
    //return : true : old entry found; false: new valid index;
    idx &= kMask;
    hash_t initial = idx;
    do {
        if (indices[idx] == -1) return 0;
        else if (entries[indices[idx]].phoneNo == phoneN) return 1;
        //else: hash value equal but true value not;
        idx = (idx * 5 + 1) & kMask;
    } while (idx != initial);
    return -1;//hash table full;
}

void insert(const string &phoneN){
    hash_t hashV = hash_func(phoneN);
    hash_t idx = hashV;
    int flagi = probe(idx, phoneN);
    if (flagi != -1){
        if (flagi == 1)
            entries[indices[idx]].times++;
        else {
            entries.push_back(ENode {hashV, phoneN, 1} );
            indices[idx] = entries.size() - 1;
        }
    }
    return;
}

int main(){
    for (int i = 0; i < kMaxLen; ++i)
        indices[i] = -1;
    
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int N;
    string p1, p2;
    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> p1 >> p2;
        insert(p1);
        insert(p2);
    }

    int maxTimes = -1, crazyN = -1;
    for (auto entry : entries){
        if (entry.times > maxTimes){
            maxTimes = entry.times;
            p1 = entry.phoneNo;
            crazyN = 1;
        }
        else if (entry.times == maxTimes){
            ++crazyN;
            if (entry.phoneNo < p1)
                p1 = entry.phoneNo;
        }
    }
    cout << p1 << ' ' << maxTimes;
    if (crazyN > 1) cout << ' ' << crazyN;
    return 0;
}