#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

char arrIn[10];

bool perm(char arr[], int size) {
    bool flag = false;
    int pos1, pos2;
    for (int i = size - 2; i >= 0; --i){
        if (arr[i] < arr[i + 1]){
            pos1 = i;
            flag = true;
            break;
        }
    }
    if (!flag){
        sort(arr, arr + size);
        return flag;
    }
    for (int i = pos1 + 1; i < size; ++i){
        if (arr[i] >= arr[pos1])
            pos2 = i;
    }
    
    char tmp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = tmp;

    sort(arr + (pos1 + 1), arr + size);

    return flag;
}

int main() {
    cin >> arrIn;
    int len = strlen(arrIn);

    sort(arrIn, arrIn + (len - 1));
    cout << arrIn << endl;

    while (perm(arrIn, len)) {
        cout << arrIn << endl;
    }
}