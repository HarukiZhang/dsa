/*
实现QQ新帐户申请和老帐户登陆的简化版功能。最大挑战是：据说现在的QQ号码已经有10位数了。

输入格式:
输入首先给出一个正整数N（≤10^5），随后给出N行指令。
每行指令的格式为：“命令符（空格）QQ号码（空格）密码”。
其中命令符为“N”（代表New）时表示要新申请一个QQ号，后面是新帐户的号码和密码；
命令符为“L”（代表Login）时表示是老帐户登陆，后面是登陆信息。
QQ号码为一个不超过10位、但大于1000（据说QQ老总的号码是1001）的整数。
密码为不小于6位、不超过16位、且不包含空格的字符串。

输出格式:
针对每条指令，给出相应的信息：

1）若新申请帐户成功，则输出“New: OK”；

2）若新申请的号码已经存在，则输出“ERROR: Exist”；

3）若老帐户登陆成功，则输出“Login: OK”；

4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；

5）若老帐户密码错误，则输出“ERROR: Wrong PW”。

输入样例:
5
L 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
L 1234567890 myQQ@qq
L 1234567890 myQQ@qq.com
输出样例:
ERROR: Not Exist
New: OK
ERROR: Exist
ERROR: Wrong PW
Login: OK
*/
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

constexpr size_t _FNV_offset_basis = 14695981039346656037ULL;
constexpr size_t _FNV_prime        = 1099511628211ULL;
constexpr int kMaxSize = 1 << 18, kMask = kMaxSize - 1;
typedef unsigned long long hash_t;
typedef int indx_t;
struct Entry {
    hash_t accn_hash, pswd_hash;
};

indx_t indices[kMaxSize];
vector<Entry> entries;
int lineN;

hash_t bitwise_hash(const unsigned char * const _First, const size_t _Count){
    hash_t _Val = _FNV_offset_basis;
    for (size_t _Idx = 0; _Idx < _Count; ++_Idx) {
        _Val ^= static_cast<size_t>(_First[_Idx]);
        _Val *= _FNV_prime;
    }
    return _Val;
}

hash_t str_hash(const string &str){
    return bitwise_hash(
        reinterpret_cast<const unsigned char *>(str.c_str()), str.length()
    );
}

hash_t int_hash(unsigned long long ull){
    return bitwise_hash(
        &reinterpret_cast<const unsigned char &>(ull), sizeof(unsigned long long)
    );
}

indx_t probe(const Entry &ent){
    indx_t idx = ent.accn_hash & kMask;
    indx_t nidx = idx;
    do {
        if (indices[nidx] == -1) return nidx;
        nidx = (nidx * 5 + 1) & kMask;
    } while (nidx != idx);
    return -1;
}

void insert(const Entry &ent){
    indx_t idx = probe(ent);
    if (idx != -1){
        entries.push_back(ent);
        indices[idx] = entries.size() - 1;
    }
    return;
}

indx_t find(hash_t accn){
    indx_t idx = accn & kMask;
    while (indices[idx] != -1){//judge whether has entry;
        if (entries[indices[idx]].accn_hash == accn)
            return idx;
        idx = (idx * 5 + 1) & kMask;
    }
    return -1;
}

void apply(hash_t accn, const string &pswd){
    Entry tmp_ent {int_hash(accn), str_hash(pswd)};
    indx_t idx = find(tmp_ent.accn_hash);
    if (idx != -1)
        cout << "ERROR: Exist" << endl;
    else {
        insert(tmp_ent);
        cout << "New: OK" << endl;
    }
    return;
}

void login(hash_t accn, const string &pswd){
    Entry tmp_ent {int_hash(accn), str_hash(pswd)};
    indx_t idx = find(tmp_ent.accn_hash);
    if (idx != -1){
        if (entries[indices[idx]].pswd_hash != tmp_ent.pswd_hash)
            cout << "ERROR: Wrong PW" << endl;
        else cout << "Login: OK" << endl;
    }
    else cout << "ERROR: Not Exist" << endl;
    return;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);
    // ios::sync_with_stdio(false);

    char cmd;
    hash_t accnin;
    string pswdin;
    cin >> lineN >> ws;

    memset(indices, -1, kMaxSize * sizeof(indx_t));
    
    for (int i = 0; i < lineN; ++i){
        cin >> cmd >> accnin >> ws >> pswdin >> ws;
        if (cmd == 'L'){//cmd is Login;
            login(accnin, pswdin);
        }
        else {//cmd is New;
            apply(accnin, pswdin);
        }
    }
    return 0;
}