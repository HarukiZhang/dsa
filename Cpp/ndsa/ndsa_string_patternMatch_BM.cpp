#include<iostream>
#include<string>

using namespace std;

constexpr int kTblLen = 16;
constexpr int kHashLen = 256;

void biuldBadCharTbl(string& patt, int* bct);
void biuldGoodSufTbl(string& patt, int* gst);

int matchPatt_r2l_brtFrc(string& text, int sta, string& patt);
int postfixBfMatch(const string & text, const string & pat);
int matchPatt_BoyMoo(string&, int, string&);

int cnt = 0;

//acafacafacaf
int main(){
    freopen("E:\\Downloads\\in.txt", "r", stdin);

    string str, pat{"doomsday"};
    getline(cin, str);
    int res = matchPatt_BoyMoo(str, 0, pat);
    cout << res << "\tcnt = " << cnt << endl;

}


//--------------------------------------------------------------------

void suffixes(char *x, int m, int *suff) {
   int f, g, i;
 
   suff[m - 1] = m;
   g = m - 1;
   for (i = m - 2; i >= 0; --i) {
      if (i > g && suff[i + m - 1 - f] < i - g)
         suff[i] = suff[i + m - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && x[g] == x[g + m - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }
}

void preBmGs(char *x, int m, int bmGs[]) {
   int i, j, suff[kTblLen];
 
   suffixes(x, m, suff);
 
   for (i = 0; i < m; ++i)
      bmGs[i] = m;
   j = 0;
   for (i = m - 1; i >= 0; --i)
      if (suff[i] == i + 1)
         for (; j < m - 1 - i; ++j)
            if (bmGs[j] == m)
               bmGs[j] = m - 1 - i;
   for (i = 0; i <= m - 2; ++i)
      bmGs[m - 1 - suff[i]] = m - 1 - i;
}

//--------------------------------------------------------------------

void biuldBadCharTbl(string& patt, int* bct){
    for (int i = 0; i < 256; ++i)
        bct[i] = -1;
    for (int i = 0; i < patt.length(); ++i){
        bct[patt[i]] = i;
        ++cnt;
    }
}

void biuldGoodSufTbl(string& patt, int* gst){
    int auxTbl[kTblLen];
    /*Biuld a suffix auxiliary table*/
    const int kLen = patt.length();
    const int kLast = kLen - 1;
    int ptr = kLast;
    auxTbl[ptr--] = kLen;//the last is the whole;
    while (ptr >= 0){
        int subLen = 0;
        while (patt[ptr - subLen] == patt[kLast - subLen]){
            ++subLen;
            ++cnt;
        }
        auxTbl[ptr] = subLen;
        --ptr;
    }
    /*Biuld Good Suffix Table;*/
    /*Firstly, pre-set every loc to "longest" movement, 
        ie, for no-match situation;*/
    for (ptr = 0; ptr <= kLast; ++ptr){
        gst[ptr] = kLen;
        ++cnt;
    }
    /*Secondly, prefix substr can intervene more loc;*/
    for (ptr = 0; ptr < kLast; ++ptr){//the last loc has no GS;
        if (auxTbl[ptr] == ptr + 1){//a PREFIX substr matched with a substr of GS;
            int offset = kLen - auxTbl[ptr];
            for (int i = kLast - auxTbl[ptr]; i >= 0; --i){
                gst[i] = offset;
                ++cnt;
            }
        }
        ++cnt;
    }
    /*Finally, infix substr only intervene one specific loc;*/
    for (ptr = 0; ptr < kLast; ++ptr){
        /*it must be "kLast - ptr" but not "kLen - auxTbl[ptr]" for reasons:
            Regarding to the last loc, it seems that the rule is a bit little diff;
            Logically, when mismatching at the last loc, pattern should be moved
            to the first (right-to-left) non-self loc for reducing redundency;
            According the suffix auxiliary table, only when auxTbl[i] == 0,
            this loc would intervene with the last loc, because that 
            the intervened loc == kLast - auxTbl[i];*/
        gst[kLast - auxTbl[ptr]] = kLast - ptr;
        ++cnt;
    }
    return;
}

int matchPatt_BoyMoo(string& text, int st, string& patt){
    int bct[kHashLen], gst[kTblLen];
    biuldBadCharTbl(patt, bct);
    biuldGoodSufTbl(patt, gst);
    const int lenT = text.length();
    const int lenP = patt.length();
    int iT = st, iP, offset;
    while (iT + lenP - 1 < lenT){
        iP = lenP - 1;
        while (iP >= 0 && text[iT + iP] == patt[iP]){
            --iP;
            ++cnt;
        }
        if (iP < 0)
            return iT;
        else {
            int tmp = iP - bct[text[iT + iP]];
            offset = gst[iP];
            /*gst[i] can't be minus (at least 1);*/
            iT += offset > tmp ? offset : tmp;
            ++cnt;
        }
    }
    return -1;
}

int matchPatt_r2l_brtFrc(string& text, int sta, string& patt){
    int iT, iP,
        stpT = text.length(), stpP = patt.length();

    iT = sta + stpP - 1;
    iP = stpP - 1;
    int i = 0;
    while (iT < stpT){
        while (iP >= 0 && text[iT] == patt[iP]){
            --iT;
            --iP;
        }
        if (iP < 0)
            return iT + 1;
        else {
            iP = stpP - 1;
            iT = sta + stpP - 1 + i;
        }
        ++i;
    }
    return -1;
}

int postfixBfMatch(const string & text, const string & pat)
{
    int lenT = text.length(), lenP = pat.length();
    //patAt指向了当前pat[0]相对于text位置
    int patAt = 0;
    int cmp;
    const size_t PATLAST = pat.length() - 1;
    while (patAt + lenP <= lenT)
    {
        cmp = PATLAST;
        while (cmp >= 0 && pat[cmp] == text[patAt + cmp])
            --cmp;

        //如果匹配成功，cmp就会来到-1的位置上
        if (cmp == -1)
            break;
        else
            ++patAt;
    }
    return patAt;
}