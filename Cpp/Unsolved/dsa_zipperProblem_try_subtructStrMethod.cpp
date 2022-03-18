#include<iostream>
#include<string>
#include<vector>
#include<array>
/*Logic:
    There're str A, str B and str C, in which the str C is the sum str;
    
    Subtruct str A from the target str C with respect to different combination;
    Store each possible str C after subtructing into a matrix;
    Check whether there is a str in the matrix that matches with str B;
*/
using namespace std;

vector<string> myvec;

//How to transform the logic in the main() to a recursive function?
void subtructStr(string& base, string& subd, int idxB, int idxS){
    if (idxS == subd.length()){
        for (int i = 0; i < base.length(); ++i){

        }
    }
    string tmp;
    for (int i = idxB; i < base.length(); ++i){
        if (base[i] != subd[idxS]){
        }
        else {
            subtructStr(base, subd, i + 1, idxS + 1);
        }
    }
}

int main() {
    // cin >> str1 >> str2 >> strTar;

    /*Subtruct the longer str from strTar;
        The longer the substrund, the lesser the number of possi. of combination*/

    // int len1 = str1.length();
    // int len2 = str2.length();
    // int len3 = strTar.length();

    // string& subd = (len1 > len2) ? str1 : str2;
    // string& toth = (len1 > len2) ? str2 : str1;

    string subd, toth, strTar;
    cin >> subd >> toth >> strTar;
    int len3 = strTar.length();


    for (int i = 0; i < len3; ++i){
        for (int j = i + 1; j < len3; ++j){
            for (int k = j + 1; k < len3; ++k){
                
                
                string imtmp;
                if (strTar[i] == subd[0] && strTar[j] == subd[1] && strTar[k] == subd[2]){
                    for (int m = 0; m < len3; ++m){
                        if (m != i && m != j && m != k)
                            imtmp.push_back(strTar[m]);
                    }
                    myvec.push_back(imtmp);
                }
            
            
            }
        }
    }

    /*Compare whether the shorter str is left strTar*/
    bool flag = false;
    for (auto it = myvec.begin(); it != myvec.end(); ++it){
        // cout << *it << endl;
        if (toth.compare(*it))
            flag = true;
    }
    if (flag)
        cout << "YES";
}