#include<iostream>
#include<iomanip>
using namespace std;

constexpr int kMaxLen = 100, kMaxProblem = 6, kMaxBuck = 180;

struct Node {
    bool show = false;
    int uid = -1;
    int child = -1;
    int perf_num = 0;
    int tot_score = 0;
    int scores[kMaxProblem] = {-2, -2, -2, -2, -2, -2};
    //-2 : no submission ; -1 : compile error;
};

int userN, probK, submM;
int full_scores[kMaxProblem];
Node users[kMaxLen];
struct BuckHead {
    int first = -1, last = -1;
};
BuckHead buckets[kMaxBuck];

int convert_uid(char *str){
    int base = 1, res = 0;
    for (int i = 4; i >= 0 && str[i] != '0'; --i){
        res += base * (str[i] - '0');
        base = ((base << 1) + (base << 3));
    }
    return res;
}

// int bucket_sort_collect(int buck_num, bool ascend = false){
//     int head = -1, lastTail = -1;
//     int i = ascend ? 0 : buck_num;
//     int delta = ascend ? 1 : -1;
//     int stp = ascend ? buck_num : 0;
//     for (; i != stp ; i += delta){
//         /*...*/
//     }
//     return head;
// }

void output(int idx, int rank){
    Node &refN = users[idx];
    cout << rank << ' ';
    cout << setfill('0') << setw(5) << refN.uid;
    cout << ' ' << refN.tot_score << ' ';
    for (int j = 1; j <= probK; ++j){
        if (j != 1) cout << ' ';
        if (refN.scores[j] == -2)
            cout << "-";
        else if (refN.scores[j] <= 0)
            cout << "0";
        else cout << refN.scores[j];
    }
    cout << endl;
    return;
}

int main(){
    // ios::sync_with_stdio(false);
    freopen("E:\\in.txt", "r", stdin);
    cin >> userN >> probK >> submM;
    for (int i = 1; i <= probK; ++i)
        cin >> full_scores[i];
    cin >> ws;
    //input submission data;
    char uidin[10];
    int pidin, crtuid, scorein;
    for (int i = 0; i < submM; ++i){
        cin >> uidin >> pidin >> scorein >> ws;
        crtuid = convert_uid(uidin);
        if (users[crtuid].scores[pidin] < scorein){
            users[crtuid].scores[pidin] = scorein;
        }
    }
    //complete Node info;
    for (int i = 1; i <= userN; ++i){
        users[i].uid = i;
        for (int j = 1; j <= probK; ++j){
            if (users[i].scores[j] >= 0){
                users[i].tot_score += users[i].scores[j];
                users[i].show = true;
            }
            if (users[i].scores[j] == full_scores[j])
                ++users[i].perf_num;
        }
    }
    if (submM == 1){
        output(crtuid, 1);
        return 0;
    }
    //bucket sort by perfectly solved problem num;
    for (int i = 1; i <= userN; ++i){
        BuckHead &crtBH = buckets[users[i].perf_num];
        if (crtBH.first != -1){
            users[crtBH.last].child = i;
            crtBH.last = i;
        }
        else {
            crtBH.first = crtBH.last = i;
        }
    }
    //bucket sort collection;
    int head = -1;
    int lastTail = -1;
    for (int i = probK; i >= 0; --i){//non-increasing;
        if (buckets[i].first != -1){
            if (head == -1) {
                head = buckets[i].first;
            }
            else {//when lastTail != -1;
                users[lastTail].child = buckets[i].first;
            }
            lastTail = buckets[i].last;
            buckets[i].first = buckets[i].last = -1;
        }
    }
    users[lastTail].child = -1;//set NULL;

    //bucket sort by total score;
    int tot_full_score = 0;
    for (int i = 1; i <= probK; ++i)
        tot_full_score += full_scores[i];
    
    for (int i = head; i != -1; i = users[i].child){
        if (users[i].show){
            BuckHead &crtBH = buckets[users[i].tot_score];
            if (crtBH.first != -1){
                users[crtBH.last].child = i;
                crtBH.last = i;
            }
            else {
                crtBH.first = crtBH.last = i;
            }
        }
    }
    //bucket sort collection;
    head = lastTail = -1;
    for (int i = tot_full_score; i >= 0; --i){//total score non-increasing;
        if (buckets[i].first != -1){
            if (head == -1){
                head = buckets[i].first;
            }
            else {
                users[lastTail].child = buckets[i].first;
            }
            lastTail = buckets[i].last;
            buckets[i].first = buckets[i].last = -1;
        }
    }
    users[lastTail].child = -1;

    //output
    int cnt = 1, rank = 1, lastTotScor = -1;
    for (int i = head; i != -1; i = users[i].child){
        if (lastTotScor != users[i].tot_score) rank = cnt;
        lastTotScor = users[i].tot_score;
        output(i, rank);
        ++cnt;
    }
    return 0;
}