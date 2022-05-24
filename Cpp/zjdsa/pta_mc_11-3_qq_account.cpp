#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

constexpr int kMaxLen = 1 << 4, kMask = kMaxLen - 1;

struct Account {
    long long qqno;
    string pswd;
};

int N;
int indices[kMaxLen];
vector<Account> entries;

int find(int &idx, long long qqno){
    //return: 0 empty loc found; 1 : qqno exists; -1 : else;
    //hash method : key mod kMaxLen;
    //collis resolv: +\- quadratic probe;
    int hash = static_cast<int>(qqno & kMask);
    idx = hash;
    if (indices[idx] == -1) return 0;
    else if (entries[indices[idx]].qqno == qqno) return 1;
    int base = 1, ofs = base, stp = ceil(sqrt(N));
    while (base <= stp){
        for (int i = 0; i < 2; ++i){
            idx = (hash + ofs) & kMask;
            if (indices[idx] == -1) return 0;
            else if (entries[indices[idx]].qqno == qqno) return 1;
            ofs = -ofs;
        }
        ++base;
        ofs = base * base;
    }
    return -1;
}

bool insert(const Account &accn){
    //using find() to substitute probe();
    int idx = 0;
    int flag = find(idx, accn.qqno);
    if (flag == 0){
        entries.push_back( accn );
        indices[idx] = entries.size() - 1;
        return true;
    }
    return false;
}

int main(){
    for (int i = 0; i < kMaxLen; ++i)
        indices[i] = -1;

    ios::sync_with_stdio(false);
    // freopen("E:\\in.txt", "r", stdin);
    cin >> N;

    char cmd[4];
    Account tmpAccn;
    for (int i = 0; i < N; ++i){
        cin >> cmd >> tmpAccn.qqno >> tmpAccn.pswd;
        if (cmd[0] == 'L'){
            int idx = 0;
            int flag = find(idx, tmpAccn.qqno);
            if (flag == 1){
                if (entries[indices[idx]].pswd == tmpAccn.pswd)
                    cout << "Login: OK" << endl;
                else cout << "ERROR: Wrong PW" << endl;
            }
            else if (flag == 0) cout << "ERROR: Not Exist" << endl;
        }
        else {
            if (insert(tmpAccn))
                cout << "New: OK" << endl;
            else cout << "ERROR: Exist" << endl;
        }
    }
    return 0;
}