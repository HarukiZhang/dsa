#include<iostream>
#include<string>

using namespace std;

constexpr int kTblLen = 32;
int cnt = 0;

/*According to len of prefix, one-loc-shifted setting;*/
void biuldNextArr_BF(string& patt, int* nArr);

void biuldNextArr(string& patt, int* nArr);

/*optimized findNext()*/
void findNext(string& patt, int* nArr);

int matchPatt_KMP(string& targ, int sta, string& patt, int* nArr);

/*This version is slim, but seems to consume more time (?):
    227  cnt = 265  */
int matchPatt_KMP_slim(string& targ, int sta, 
    string& patt, int* nArr);


void biuldNextArr_exmp(string& patt){
    int nArr[kTblLen]{};
    const int kLen = patt.length();
    int ptr, shift_to;
    ptr = 0;
    nArr[ptr] = -1;
    shift_to = nArr[ptr];
    while (ptr < kLen - 1){
        if (shift_to == -1 || patt[ptr] == patt[shift_to]){
            nArr[++ptr] = ++shift_to;
        }
        else {
            do {
                shift_to = nArr[shift_to];
            } while (shift_to != -1 && patt[ptr] != patt[shift_to]);
            shift_to = nArr[ptr + 1] = shift_to + 1;
            ++ptr;
        }
    }
    return;
}


int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    // string tar;
    string pat{"aabcaaabca"};
    int nextArr1[kTblLen];
    // int nextArr2[kTblLen];
    biuldNextArr_exmp(pat);
    // biuldNextArr_BF(pat, nextArr2);
    // cout << "cnt = " << cnt << endl;
    // for (int i = 0; i < pat.length(); ++i)
    //     cout << pat[i] << "   ";
    // cout << endl;
    // for (int i = 0; i < pat.length(); ++i){
    //     if (nextArr1[i] != -1)
    //         cout << nextArr1[i] << "   ";
    //     else
    //         cout << 'd' << "   ";
    // }
    // cout << endl;
    // for (int i = 0; i < pat.length(); ++i){
    //     if (nextArr1[i] != nextArr2[i])
    //         cout << 0;
    //     else
    //         cout << 1;
    //     cout << "   ";
    // }
    // cout << endl;
}

/*OUTCOME:
18  cnt = 25
18  cnt = 25

50  cnt = 65

227  cnt = 250
*/



void biuldNextArr_BF(string& patt, int* nArr){
    const int kLen = patt.length();
    nArr[0] = nArr[1] = 0;
    for (int i = 1; i < kLen - 1; ++i){
        if (patt[nArr[i]] == patt[i])
            nArr[i + 1] = nArr[i] + 1;//shift one loc for "next";
        else//this condition is too simple to situation;
            nArr[i + 1] = 0;
    }
    nArr[0] = -1;
    /*optimize next arr:*/
    // for (int i = 1; i < kLen; ++i){//i starts from 1, it wont encounter with -1;
    //     if (patt[i] == patt[nArr[i]])
    //         nArr[i] = nArr[nArr[i]];
    // }
    return;
}


void biuldNextArr(string& patt, int nArr[]){
    const int kLen = patt.length();
    int ptr, shift_to;
    ptr = 0;
    /*-1 denotes a wildcard char : that matches with any char;*/
    nArr[ptr] = -1;
    shift_to = nArr[ptr];
    while (ptr < kLen - 1){
        /*shift_to saved the value of last time;*/
        if (shift_to == -1 || patt[ptr] == patt[shift_to]){
            /*if shift_to is valid, and crt char matches with char at shift_to,
            then the value of next loc would be the next of shift_to;*/
            nArr[++ptr] = ++shift_to;//nArr[i + 1] = nArr[i] + 1;
        }
        else {// shift_to != -1 && patt[ptr] != patt[shift_to];
            do {//trace backward,
                shift_to = nArr[shift_to];
            } while (shift_to != -1 && patt[ptr] != patt[shift_to]);
            //till shift_to == -1 || patt[ptr] == patt[shift_to];
            shift_to = nArr[ptr + 1] = shift_to + 1;
            ++ptr;
        }
    }
    return;
}


void findNext(string& patt, int* nArr){
	int ptr, shift_to;
	int m = patt.length();
    /*The value in the next arr denotes the loc of destination of shift;*/
	nArr[0] = -1;
    /*pointer to the current char;*/
	ptr = 0;
    /*pointer to the dest of shift;*/
	shift_to = -1;
	while (ptr < m - 1){//if use (ptr < m), it may overflow;
		while (shift_to >= 0 && patt[shift_to] != patt[ptr]){
            /*if shift_to is valid, 
            and the char at the loc of shift_to != the char at current loc,
            go to more left;*/
			shift_to = nArr[shift_to];
		}
		++ptr;
		++shift_to;
		// if (patt[shift_to] == patt[ptr])//for optimization;
		// 	nArr[ptr] = nArr[shift_to];
		// else
			nArr[ptr] = shift_to;
	}
	return;
}

int matchPatt_KMP(string& targ, int sta, string& patt, int* nArr){
    int pT = sta, pP = 0, 
        tStp = targ.length(), pStp = patt.length();
    
    while (true){
        while (pT < tStp && pP < pStp && targ[pT] == patt[pP]){
            ++pT;
            ++pP;
            ++cnt;
        }
        if (pP == pStp)
            return pT - pStp;
        else {
            if (pT + pStp > tStp)
                return -1;
            /*check the next table to set ptr of patt;*/
            pP = nArr[pP];
            if (pP == -1)
            if (pP == 0){//The first char is different;
                char test = patt[0];
                while (pT < tStp && targ[pT] != test){
                    ++pT;
                    ++cnt;
                }
            }
        }
    }
}

int matchPatt_KMP_slim(string& targ, int sta, 
    string& patt, int* nArr){
    int pT = sta, pP = 0, 
        tStp = targ.length(), pStp = patt.length();
    
    while (pT < tStp){
        ++cnt;
        if (targ[pT] == patt[pP]){
            ++pT;
            ++pP;
        }
        else if (pP != 0)//because nArr[pP] == -1;
            pP = nArr[pP];
        else //for when pP == 0;
            ++pT;
        if (pP == pStp)
            return pT - pStp;
        else if (pT + pStp > tStp)//trim or not?
            return -1;
    }
    return -1;
}