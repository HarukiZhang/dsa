#include<iostream>
#include<vector>
#include<string>
using namespace std;

constexpr int kMaxNum = 70, kMaxLen = kMaxNum * 2, kAsciiLen = 128;
constexpr int kInfty = ~(1<<31);

struct Node {
    int weight, lchild = -1, rchild = -1;
    char data = '\0';
};

int charNum;
int freqs[kAsciiLen];
char charHash[kMaxNum];
string codes_buffer[kMaxNum];
Node tree[kMaxLen];
int treeSize = 0;
int weights[kMaxLen];

void getMinTwo(int* hp, int sz){
    hp[0] = hp[1] = kMaxLen - 1;//the last value in weights[], which is kInfty;
    for (int i = 0; i < sz; ++i){
        if (weights[i] < weights[hp[0]]){
            if (weights[i] < weights[hp[1]]){
                hp[0] = hp[1];
                hp[1] = i;
            }
            else hp[0] = i;
        }
    }
    return;
}

int getMinWPL(){
    int resWpl = 0;
    int minT[2];//the idx of minimal two;
    while(true) {
        getMinTwo(minT, treeSize);
        if (weights[minT[0]] != kInfty){//minT[0] should be greater than minT[1];
            int tmpSum = weights[minT[0]] + weights[minT[1]];
            resWpl += tmpSum;
            tree[treeSize] = Node {tmpSum, minT[0], minT[1] };
            weights[treeSize] = tmpSum;
            ++treeSize;
            weights[minT[0]] = kInfty;
            weights[minT[1]] = kInfty;
        }
        else break;
    }
    return resWpl;
}

bool compareCodes(const string &s1, const string &s2){
    decltype(s1.length()) l1 = 0, l2 = 0;
    while (l1 < s1.length() && l2 < s2.length()){
        if (s1[l1] != s2[l2])
            return true;//prefix code valid;
        ++l1;
        ++l2;
    }
    return false;//prefix code invalid;
}

bool checkPrefixCode(int ptr){
    for (int i = ptr + 1; i < charNum; ++i){
        if ( !compareCodes(codes_buffer[ptr], codes_buffer[i]) )
            return false;//crt invalid;
    }
    return true;//all valid;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);

    cin >> charNum >> ws;
    for (int i = 0; i < charNum; ++i){
        cin >> tree[i].data >> ws >> tree[i].weight >> ws;
        freqs[(size_t)tree[i].data] = tree[i].weight;
        weights[i] = tree[i].weight;
        ++treeSize;
    }
    weights[kMaxLen - 1] = kInfty;//usd for getMinTwo() initializaton;
    int minWpl = getMinWPL();
    int studentNum;
    cin >> studentNum >> ws;
    for (int i = 0; i < studentNum; ++i){
        bool flag = true;
        
        int crtWpl = 0;
        for (int j = 0; j < charNum; ++j){
            cin >> charHash[j] >> ws >> codes_buffer[j] >> ws;
            crtWpl += codes_buffer[j].length() * freqs[(size_t)charHash[j]];
        }

        if (crtWpl != minWpl) flag = false;

        for (int j = 0; j < charNum; ++j){
            if ( !flag ) break;
            flag = checkPrefixCode(j);
        }
        if (flag)
            cout << "Yes";
        else cout << "No";
        cout << endl;

        for (int j = 0; j < charNum; ++j)
            codes_buffer[j].clear();
    }
    return 0;
}


/*
*/