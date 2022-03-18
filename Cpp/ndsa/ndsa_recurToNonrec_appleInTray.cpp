#include <iostream>
#include<stack>
using namespace std;

int appleTray(int appleN, int trayN){
/*label_0*/
    int locVar;
	if (appleN == 1 || trayN == 1 || appleN == 0){
		locVar = 1;
    }
    else {
        if (trayN > appleN){
            locVar = appleTray(appleN, appleN);
            /*label_2*/
        }
        else {
            locVar = appleTray(appleN, trayN - 1);
            /*label_1*/
            locVar += appleTray(appleN - trayN, trayN);
            /*label_2 (same as above one)*/
        }
    }
    return locVar;
}

struct Elem {
    int rd, pA, pT, locVar;
};

class Nonrec {
    stack<Elem> nexus;
public:
    Nonrec(){}
    int replace(int, int);
    int rplc_optm(int, int);
};

int main() {
	Nonrec nonrec;
    int aN, tN;
	cin >> aN >> tN;
	cout << appleTray(aN, tN) << endl;
    cout << nonrec.rplc_optm(aN, tN) << endl;
}

int Nonrec::rplc_optm(int a, int t){
    int retV, tmpA, tmpT;
    Elem tmp { 3, a, t, 0 };
    nexus.push(tmp);
    do {
    /*Process according to param value;*/
        tmpA = nexus.top().pA;
        tmpT = nexus.top().pT;
        if (tmpA == 1 || tmpT == 1 || tmpA == 0){
            nexus.top().locVar = 1;
            /*goto label_OA;*/
        }
        else {
            do {
                if (tmpT > tmpA){
                    tmp.rd = 2;
                    tmp.pA = tmpA;
                    tmp.pT = tmpA;
                    tmp.locVar = 0;
                    nexus.push(tmp);
                    /*goto label_0;*/
                }
                else {
                    tmp.rd = 1;
                    tmp.pA = tmpA;
                    tmp.pT = tmpT - 1;
                    tmp.locVar = 0;
                    nexus.push(tmp);
                    /*goto label_0;*/
                }
                tmpA = nexus.top().pA;
                tmpT = nexus.top().pT;
            } while (tmpA != 1 && tmpT != 1 && tmpA != 0);
            /*if (tmpA == 1 || tmpT == 1 || tmpA == 0)*/
            nexus.top().locVar = 1;
            /*goto label_OA;*/
        }

    /*Start to process according to return directory;*/
        /*label_2:*/
        while (nexus.top().rd == 2){
            retV = nexus.top().locVar;
            nexus.pop();
            nexus.top().locVar += retV;
            /*goto label_OA to schedule (may need to come back to 2);*/
        }

        /*label_1:*/
        if (nexus.top().rd == 1){
            /*Pass return value;*/
            retV = nexus.top().locVar;
            nexus.pop();
            nexus.top().locVar = retV;
            /*Push in a new layer of stack;*/
            tmp = nexus.top();
            tmp.rd = 2;
            tmp.pA = tmp.pA - tmp.pT;
            tmp.locVar = 0;
            nexus.push(tmp);
            /*goto label_0;*/
        }

    } while(nexus.top().rd != 3);
    /*if rd == 3;*/
    retV = nexus.top().locVar;
    nexus.pop();
    return retV;
}


int Nonrec::replace(int a, int t){
    int retV;
    Elem tmp { 3, a, t, 0 };
    nexus.push(tmp);
label_0:
    tmp = nexus.top();
    if (tmp.pA == 1 || tmp.pT == 1 || tmp.pA == 0){
        nexus.top().locVar = 1;
        goto label_OA;
    }
    /*else*/
        if (tmp.pT > tmp.pA){
            tmp.rd = 2;
            tmp.pT = tmp.pA;
            tmp.locVar = 0;
            nexus.push(tmp);
            goto label_0;
        }
        else {
            tmp.rd = 1;
            --tmp.pT;
            tmp.locVar = 0;
            nexus.push(tmp);
            goto label_0;
        }
    /*else end;*/
label_1:
    retV = nexus.top().locVar;
    nexus.pop();
    nexus.top().locVar = retV;
    tmp = nexus.top();
    tmp.rd = 2;
    tmp.pA = tmp.pA - tmp.pT;
    tmp.locVar = 0;
    nexus.push(tmp);
    goto label_0;
label_2:
    retV = nexus.top().locVar;
    nexus.pop();
    nexus.top().locVar += retV;
label_OA:
    switch(nexus.top().rd){
    case 1 :
        goto label_1;
    case 2 :
        goto label_2;
    case 3 :
        retV = nexus.top().locVar;
        nexus.pop();
        return retV;
    default :
        break;
    }
    return -1;
}