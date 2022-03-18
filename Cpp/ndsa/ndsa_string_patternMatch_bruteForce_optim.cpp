/*char string pattern matching:

optimized Brute Force method: 
    find a way to reduce the redundency when looping to search 
    same pattern;
*/
#include<iostream>
#include<string>

using namespace std;

int cnt = 0;

int matchPatt(string& targ, string& patt){
    int tarPtr = 0, patPtr = 0,
        tarStp = targ.length(), patStp = patt.length();
    
    if (patStp > tarStp)
        return -1;
    if (patStp == 0)
        return -2;//empty str is substr of any str;

    while (true){
        /*Compare char-by-char;*/
        while (tarPtr < tarStp && patPtr < patStp
            && patt[patPtr] == targ[tarPtr]){
            ++patPtr;
            ++tarPtr;
            ++cnt;
        }
        /*Judge whether found;*/
        if (patPtr == patStp)//Pattern matched;
            return tarPtr - patStp;
        else {//Not-Found;
            /*Search for the NEXT start ptr for targ;
            here, targ[tarPtr] != patt[patPtr];
            So, need to at least find a char in targ that is 
            same as the present char in patt, in the post period
            of targ; */
            char test = patt[patPtr];
            while (tarPtr < tarStp && targ[tarPtr] != test){
                ++tarPtr;
                ++cnt;
            }
            tarPtr -= patPtr;
            if (tarPtr + patStp > tarStp)//targ not enough;
                return -1;
            else
                patPtr = 0;//Reset patPtr;
        }
    }
}

int main(){
    freopen("E:\\Downloads\\in.txt", "r", stdin);

    string tar, pat{"accurate"};
    getline(cin, tar);
    cout << matchPatt(tar, pat)
        << "  Cnt == " << cnt << endl;

}

/*OUTCOME:
18  Cnt == 40
18  Cnt == 24

50  Cnt == 59
*/