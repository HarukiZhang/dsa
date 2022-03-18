/*10:Best Cow Line, Gold
总时间限制: 10000ms 单个测试点时间限制: 1000ms 内存限制: 65536kB
描述
  FJ is about to take his N (1 <= N <= 30,000) cows to the annual "Farmer of the Year" 
  competition. In this contest every farmer arranges his cows in a line and herds them 
  past the judges.

  The contest organizers adopted a new registration scheme this year: simply register 
  the initial letter of every cow in the order they will appear (e.g., If FJ takes Bessie, 
  Sylvia, and Dora in that order, he just registers BSD). After the registration phase ends, 
  every group is judged in increasing lexicographic order (i.e., alphabetical order) according 
  to the string of the initials of the cows' names.

  FJ is very busy this year and has to hurry back to his farm, so he wants to be judged as 
  early as possible. He decides to rearrange his cows, who have already lined up, before 
  registering them.

  FJ marks a location for a new line of the competing cows. He then proceeds to marshal the 
  cows from the old line to the new one by repeatedly sending either the first or last cow 
  in the (remainder of the) original line to the end of the new line. When he's finished, 
  FJ takes his cows for registration in this new order.

  Given the initial order of his cows, determine the least lexicographic string of initials 
  he can make this way.

输入
  * Line 1: A single integer: N
  * Lines 2..N+1: Line i+1 contains a single initial ('A'..'Z') of the cow in the ith position 
  in the original line

输出
  The least lexicographic string he can make. Every line (except perhaps the last one) contains 
  the initials of 80 cows ('A'..'Z') in the newline.

提示
INPUT DETAILS:
  FJ has 6 cows in this order: ACDBCB

OUTPUT DETAILS:
    Step   Original     New
    #1     ACDBCB
    #2      CDBCB     A
    #3      CDBC      AB
    #4      CDB       ABC
    #5      CD        ABCB
    #6       D        ABCBC
    #7                ABCBCD
*/
#include<cstdio>
#include<deque>
#include<vector>
using namespace std;

deque<char> myDeq;
vector<char> myVec;
int N;
char inp;

int main(){
	// freopen("E:\\Downloads\\in.txt", "r", stdin);
	scanf("%d\n", &N);
	for (int i = 0; i < N; ++i){
		scanf("%c\n", &inp);
		myDeq.push_back(inp);
	}
	while (!myDeq.empty()){
		char a = myDeq.front(),
			b = myDeq.back();
		/*Push the side that is lexicographically former;*/
		if (a < b){
			myVec.push_back(a);
			myDeq.pop_front();
		}
		else if (a > b){
			myVec.push_back(b);
			myDeq.pop_back();
		}
		else {
			auto itlf = myDeq.begin();
			auto itrt = myDeq.end() - 1;

			int curlen = myDeq.size();
			int half = curlen / 2;
			int i;
			/*No matter odd or even, as long as i < len / 2, i wont overflow or be conflict
			with each other (segmentation fault);
			Until each side is lexicographically former, we dont know we should take which
			side, because the rule is to pick one cow one time, rather than two cows concurrently;*/
			for (i = 0; i < half; ++i){
				/*Loop till different cows;*/
				if (*itlf != *itrt)
					break;
				/*Both sides shrink inward concurrently;*/
				++itlf;
				--itrt;
			}
			/*Using deque's size to control looping, two ptrs would not become the same one
			in the middle of whole sequence;*/
			if (*itlf < *itrt){
				myVec.push_back(a);
				myDeq.pop_front();
			}
			/*If all elems are same till the very middle pos, it's no difference we take
			elem on which side, So just push the back elem and use the same branch of 
			(left ptr > right);*/
			else {
				myVec.push_back(b);
				myDeq.pop_back();
			}
		}
	}
	int cnt = 0;
	for (auto it = myVec.begin(); it != myVec.end(); ++it){
		if (cnt != 0 && cnt % 80 == 0)
			printf("\n");
		printf("%c", *it);
		++cnt;
	}
}

/*
样例输入
6
A
C
D
B
C
B
样例输出
ABCBCD
*/