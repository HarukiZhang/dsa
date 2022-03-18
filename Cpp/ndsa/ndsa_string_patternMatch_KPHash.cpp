#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int d = 0;

int kpHash(string& str, int ln){
    if (d == 0){
        d = 1;
        for (int i = 1; i < ln; ++i)
            d = d << 1;
    }

    int hv = (int)str[0];
    for (int i = 1; i < ln; ++i)
        hv = (hv << 1) + str[i];
    return hv;
}

inline int kpRehash(char lf, char rt, int hv){
    return ((hv - ::d * (int)lf) << 2) + (int)rt;
}

int matchPatt_KarpRabin(string& text, string& patt){
    const int kLenT = text.length();
    const int kLenP = patt.length();

    int hp = kpHash(patt, kLenP);
    int ht = kpHash(text, kLenP);

    int ptr = 0;
    while (ptr + kLenP < kLenT){
        if (hp == ht){
            bool f = true;
            for (int i = 0; i < kLenP; ++i){
                if (text[ptr + i] != patt[i]){
                    f = false;
                    break;
                }
            }
            if (f)
                return ptr;
        }
        else
            ht = kpRehash(text[ptr], text[ptr + kLenP], ht);
        ++ptr;
    }
    return -1;
}

int main(){
    string text {"GCATCGCAGAGAGTATACAGTACG"},
        pattern {"GCAGAGAG"};
    cout << matchPatt_KarpRabin(text, pattern);
}