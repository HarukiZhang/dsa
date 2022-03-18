#include<iostream>
#include<cstring>
using namespace std;

int str_search(char pat[], char str[]){
    /* judge whether pat[] is in string[]
    return the position of the first char of pat[] in the str[] if it is,
    return -1 if not */
    if (pat[0] == 0)//empty string is substring of any other string
        return 0;
    int j;
    for (int i = 0; str[i]; i++){
        for (j = 0; pat[j]; j++){
            if (pat[j] != str[j + i])
                break;
        }
        if (pat[j] == 0)
            return i;
    }
    return -1;
}

char ch1[110], ch2[110];

int main(){
    // freopen("E:\\Downloads\\in (9).txt", "r", stdin);
    cin.getline(ch1, 110);
    cin.getline(ch2, 110);
    int a = str_search(ch1, ch2);
    if (a == -1)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
    return 0;
}