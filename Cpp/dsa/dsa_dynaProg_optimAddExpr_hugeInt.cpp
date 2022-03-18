#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>

using namespace std;

constexpr int kMxDg = 52;
int counter = 0;

class MyHI {
public:
    /*Small-end storage;
    The 52th char denote the digits of the num;
    According to problem, the 50 digits is the max;*/
    /* char num[] : Initiation default to all 0 */
    char num[kMxDg]{};
    //default construct with 0 (not '0');
    MyHI() {}
    //copy constructor
    MyHI(const MyHI& myhi) {
        int i = 0;
        for (; myhi.num[i]; ++i)
            num[i] = myhi.num[i];
        num[i] = 0;
        num[kMxDg - 1] = myhi.num[kMxDg - 1];
    }
    //assignment operator
    MyHI& operator=(const MyHI& myhi) {
        int i = 0;
        for (; myhi.num[i]; ++i)
            num[i] = myhi.num[i];
        num[i] = 0;
        num[kMxDg - 1] = static_cast<char>(i);
        return *this;
    }
    //addition operator
    MyHI operator+(const MyHI& myhi) {
        MyHI res;
        if (num[0] == 'I' || myhi.num[0] == 'I') {
            res.infG();
            return res;
        }
        int idx = 0;
        char carry = 0, tmp;
        while (num[idx] && myhi.num[idx]) {
            /* '\140' == '0' + '0' */
            tmp = num[idx] - '\140' + myhi.num[idx] + carry;
            res.num[idx] = tmp % 10 + '0';
            carry = tmp / 10;
            ++idx;
        }
        while (num[idx]) {
            tmp = num[idx] - '0' + carry;
            res.num[idx] = tmp % 10 + '0';
            carry = tmp / 10;
            ++idx;
        }
        while (myhi.num[idx]) {
            tmp = myhi.num[idx] - '0' + carry;
            res.num[idx] = tmp % 10 + '0';
            carry = tmp / 10;
            ++idx;
        }
        if (carry && idx != kMxDg - 2)
            res.num[idx++] = carry + '0';
        res.num[idx] = 0;
        res.num[kMxDg - 1] = static_cast<char>(idx);
        return res;
    }
    //comparation
    bool operator<(const MyHI& myhi) {
        //If the 0th loc is 'I', recognize it as infinitly-great;
        /*If self == inf-g, it cannot be lesser than the oprd: return false*/
        if (num[0] == 'I') return false;
        /*If self != inf-g and the oprd == inf-g: self lesser than inf-g: return true*/
        else if (myhi.num[0] == 'I') return true;
        /*If not above: (self != inf and oprd != inf) need digit-by-digit comparation*/
        /*the digit of MyHI stored in the last char*/
        int dig1 = num[kMxDg - 1], dig2 = myhi.num[kMxDg - 1];
        if (dig1 != dig2) {
            return dig1 < dig2;
        }
        /*If digits of the two are all the same*/
        else {
            int idx = dig1 > dig2 ? dig1 : dig2;
            for (; idx >= 0; --idx) {
                if (num[idx] != myhi.num[idx])
                    return num[idx] < myhi.num[idx];
            }
            /*if all digits of two num are all same*/
            return false;
        }
    }
    //Set infinitly-great
    void infG() {
        num[0] = 'I';
    }
    //output
    friend ostream& operator<< (ostream& os, const MyHI& myhi) {
        MyHI tmp;
        int tLen = myhi.num[kMxDg - 1];
        reverse_copy(myhi.num, myhi.num + tLen, tmp.num);
        tmp.num[tLen] = 0;
        os << tmp.num;
        return os;
    }
};

char cstrIn[kMxDg];
MyHI myHIMtx[kMxDg][kMxDg];
/*minSumMtx accessing method: (N, M) : N digits from right with M operators
     0 : unset (initiation);
    'I' : infinitely-great; */
MyHI minSumMtx[kMxDg][kMxDg];

void cstrToMyHIMtx(int strL);

void optimAddExpr(int strL, int optN);

int main() {
    //freopen("E:\\Downloads\\in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int optNum;
    while (cin >> optNum) {
        cin >> ::cstrIn;
        int strLen = strlen(::cstrIn);
        cstrToMyHIMtx(strLen);
        optimAddExpr(strLen, optNum);
        cout << ::minSumMtx[strLen][optNum] << "\n" << flush;
        //clog << counter << "\n" << flush;
    }
    //    //debug
    //    //for (int i = 1; i <= strLen; ++i) {
    //    //    for (int j = 1; j <= i; ++j) {
    //    //        cout << setw(47) << ::myHIMtx[i][j];
    //    //    }
    //    //    cout << "\n" << flush;
    //    //}
    //}

    //testing hugeint:
    //cin >> cstrIn;
    //int cstrLen = strlen(cstrIn);
    //cstrToMyHIMtx(cstrLen);
    //MyHI a{ ::myHIMtx[1][1] },
    //    b{ ::myHIMtx[2][2] },
    //    c{ ::myHIMtx[3][3] },
    //    d{ ::myHIMtx[4][4] },
    //    e{ ::myHIMtx[5][5] },
    //    f{ ::myHIMtx[6][6] },
    //    g{ ::myHIMtx[7][7] },
    //    h{ ::myHIMtx[8][8] };
    //cout << a << " + " << a << " = " << a + a << endl;
    //cout << b << " + " << g << " = " << b + g << endl;
    //cout << c << " + " << h << " = " << c + h << endl;
    //cout << d << " + " << e << " = " << d + e << endl;
    //cout << e << " + " << g << " = " << e + g << endl;
    //cout << f << " + " << h << " = " << f + h << endl;
    //cout << g << " + " << c << " = " << g + c << endl;
    //cout << h << " + " << d << " = " << h + d << endl;
    //cout << a << " + " << g << " = " << a + g << endl;

}

/*INPUT:
44
1111274238584359484875958348749595954893736597   <----Wrong
46
111127423858435948487595834874959595489373659787  <----Wrong
260 <---- myWrongAns = 123
275 <---- myWrongAns = 123
*/

void optimAddExpr(int strL, int optN) {
    for (int iCurL = 1; iCurL <= strL; ++iCurL) {
        for (int iOptN = 0; iOptN <= optN; ++iOptN) {
            MyHI& curOprd = ::minSumMtx[iCurL][iOptN];
            ++::counter;
            /*Return the number converted from current whole str*/
            if (iOptN == 0)
                curOprd = ::myHIMtx[iCurL][iCurL];
            /*Return infinity*/
            else if (iCurL <= iOptN)
                curOprd.infG();
            /*Current str is just separated into even pieces*/
            /* here, optN > 0 */
            else if (iCurL % (iOptN + 1) == 0) {
                /*Sum up each piece as a single int*/
                int interval = iCurL / (iOptN + 1);
                MyHI tmp;
                for (int i = iCurL; i > 0; i -= interval)
                    tmp = tmp + ::myHIMtx[i][interval];
                curOprd = tmp;
            }
            /*iCurL is odd, and 1 operator left*/
            else if (iOptN == 1) {
                /*1 optr split the str into two parts, so if curLen is odd,
                the one above branch cannot catch this sitution*/
                /*Intercept at half of current str and judge left or right*/
                /* 2 == (optN + 1) pieces */
                int interval = iCurL / 2;
                /*the half starts from (idx + interval) */
                if (::cstrIn[strL - iCurL] > ::cstrIn[strL - iCurL + interval])
                    curOprd = ::myHIMtx[iCurL][interval] 
                        + ::myHIMtx[iCurL - interval][interval + 1];
                else
                    curOprd = ::myHIMtx[iCurL][interval + 1]
                        + ::myHIMtx[iCurL - interval - 1][interval];
            }

            /*Reverse inference DynaProg*/
            else {
                /*Set current operand inf-great*/
                curOprd.infG();
                for (int i = 1; i <= iCurL; ++i) {
                    MyHI tmp{ ::myHIMtx[iCurL][i] + ::minSumMtx[iCurL - i][iOptN - 1] };
                    if (tmp < curOprd)
                        curOprd = tmp;
                }
            }
        }
    }
}

void cstrToMyHIMtx(int strL) {
    /*i : len from right*/
    for (int i = 1; i <= strL; ++i) {
        /*j : the interval to right*/
        for (int j = 1; j <= i; ++j) {
            MyHI& oprd = ::myHIMtx[i][j];
            int idx = 0, stp = strL - i;
            for (int k = strL - i + j - 1; k >= stp; ++idx, --k)
                oprd.num[idx] = ::cstrIn[k];
            oprd.num[idx] = 0;
            oprd.num[kMxDg - 1] = static_cast<char>(idx);
        }
    }
}