/*
The ranklist of PAT is generated from the status list, which shows the scores 
of the submissions. This time you are supposed to generate the ranklist for PAT.

Input Specification:
Each input file contains one test case. For each case, the first line contains 
3 positive integers, N (≤10^4), the total number of users, K (≤5), the total 
number of problems, and M (≤10^5), the total number of submissions. It is then 
assumed that the user id's are 5-digit numbers from 00001 to N, and the problem 
id's are from 1 to K. The next line contains K positive integers p[i] 
(i=1, ..., K), where p[i] corresponds to the full mark of the i-th problem. 
Then M lines follow, each gives the information of a submission in the following 
format:

    user_id problem_id partial_score_obtained

where partial_score_obtained is either −1 if the submission cannot even pass the 
compiler, or is an integer in the range [0, p[problem_id]]. All the numbers in a 
line are separated by a space.

Output Specification:
For each test case, you are supposed to output the ranklist in the following format:

    rank user_id total_score s[1] ... s[K]

where rank is calculated according to the total_score, and all the users with the 
same total_score obtain the same rank; and s[i] is the partial score obtained for 
the i-th problem. If a user has never submitted a solution for a problem, then "-" 
must be printed at the corresponding position. If a user has submitted several 
solutions to solve one problem, then the highest score will be counted.

The ranklist must be printed in non-decreasing order of the ranks. For those who 
have the same rank, users must be sorted in nonincreasing order according to the 
number of perfectly solved problems. And if there is still a tie, then they must 
be printed in increasing order of their id's. For those who has never submitted 
any solution that can pass the compiler, or has never submitted any solution, they 
must NOT be shown on the ranklist. It is guaranteed that at least one user can be 
shown on the ranklist.
*/
#include<cstdio>
#include<queue>
using namespace std;

constexpr int kMaxUser = 10010, kMaxProb = 5 + 1, kMaxSubms = 100010, kMaxDig = 5;

struct Record {
    int total_score = -1, perfect_num = 0;
    int scores[kMaxProb];
    //-2 : no submission;
    //-1 : submitted but compile error;
    //>=0: normal scores;
};

Record records[kMaxUser];
//   N       K      M
int userN, probN, submN;
int fullMarks[kMaxProb];

struct Elem {
    int idx;
    /*Priority of Key:
        rank (total_score) : non-decr;
        perfect_solved_num : non-incr;
        user_id            : incr;
    */
    bool operator<(const Elem &e) const {
        if (records[idx].total_score != records[e.idx].total_score){
            //high total_score => small rank : non-decresing;
            return records[idx].total_score < records[e.idx].total_score;
        }
        else if (records[idx].perfect_num != records[e.idx].perfect_num){
            //more perfect_num : non-increas;
            return records[idx].perfect_num < records[e.idx].perfect_num;
        }
        else {
            return idx > e.idx;//userid : ascending;
        }
    }
};
priority_queue<Elem> heap;

int convertUid(char *uid){
    int ret = 0, i, base = 10000;
    for (i = 0; i < kMaxDig && uid[i] == '0'; ++i)
        base /= 10;
    for (; i < kMaxDig; ++i){
        ret += base * (uid[i] - '0');
        base /= 10;
    }
    return ret;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);
    scanf("%d%d%d", &userN, &probN, &submN);
    //initialization;
    for (int i = 1; i <= probN; ++i)
        scanf("%d ", &fullMarks[i]);
    for (int i = 0; i <= userN; ++i)
        for (int j = 1; j <= probN; ++j)
            records[i].scores[j] = -2;//-2 : no submission;
    //read in;
    char uid[10];
    int prob_id, part_scr;
    for (int i = 0; i < submN; ++i){
        scanf("%s %d %d", uid, &prob_id, &part_scr);
        int uidi = convertUid(uid);
        Record &crtR = records[uidi];
        if (crtR.scores[prob_id] < part_scr)
            crtR.scores[prob_id] = part_scr;
    }
    //get statistics;
    for (int i = 1; i <= userN; ++i){
        bool flag = false;
        for (int j = 1; j <= probN; ++j){
            //For those who has never submitted any solution that can pass the compiler,
            //or has never submitted any solution, 
            //they must NOT be shown on the ranklist;
            //in other words, only has at-least one score >= 0;
            if (records[i].scores[j] >= 0){
                flag = true;
                records[i].total_score += records[i].scores[j];
                if (records[i].scores[j] == fullMarks[j])
                    ++records[i].perfect_num;
            }
            else if (records[i].scores[j] == -1)
                records[i].scores[j] = 0;
        }
        if (flag)
            ++records[i].total_score;
    }
    //heap sort on table;
    for (int i = 1; i <= userN; ++i)
        if (records[i].total_score >= 0)
            heap.push(Elem {i});
    //output;
    int rank_abs = 1, rank_prt = 1;
    int last_scr = records[heap.top().idx].total_score;
    while ( !heap.empty() ){
        const Elem &crt = heap.top();
        //only "un-submitted / compile error" do not output,
        //which should be differentiated from "score is 0";
        if (records[crt.idx].total_score >= 0){
            if (records[crt.idx].total_score != last_scr){
                rank_prt = rank_abs;
            }
            printf("%d %05d %d", rank_prt, crt.idx, records[crt.idx].total_score);

            for (int i = 1; i <= probN; ++i){
                if (records[crt.idx].scores[i] >= 0)
                    printf(" %d", records[crt.idx].scores[i]);
                else printf(" %c", '-');
            }
            printf("\n");
        }
        last_scr = records[crt.idx].total_score;
        heap.pop();
        ++rank_abs;
    }
    return 0;
}

/*
Sample Input:
7 4 20
20 25 25 30
00002 2 12
00007 4 17
00005 1 19
00007 2 25
00005 1 20
00002 2 2
00005 1 15
00001 1 18
00004 3 25
00002 2 25
00005 3 22
00006 4 -1
00001 2 18
00002 1 20
00004 1 15
00002 4 18
00001 3 4
00001 4 2
00005 2 -1
00004 2 0
Sample Output:
1 00002 63 20 25 - 18
2 00005 42 20 0 22 -
2 00007 42 - 25 - 17
2 00001 42 18 18 4 2
5 00004 40 15 0 25 -
*/