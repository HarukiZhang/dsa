
#include<cstdio>
using namespace std;

class MySet {
public:
    MySet(int sz)
        : arr(new int [sz + 10])
    {
        arr[0] = sz;//use loc 0 to store set size;
        for (int i = 1; i <= sz; ++i)//data starts from 1;
            arr[i] = -1;//initiate parent ptr;
    }
    ~MySet(){
        delete[] arr;
    }
    void unionSet(int a, int b){
        int x = find_compressPath(a);
        int y = find_compressPath(b);
        /*using minus to denote node num,
        the smaller the value, the more the node*/
        if (x == y) return;//already belong to the one set;
        if (arr[x] < arr[y]){
            arr[x] += arr[y];
            arr[y] = x;//let the shorter be unioned into the higher;
        }
        else {
            arr[y] += arr[x];
            arr[x] = y;
        }
        return;
    }
    bool checkElem(int a, int b) const {
        int x = find(a);
        int y = find(b);
        return x == y;
    }
    int getSetNum() const {
        int n = 0;
        for (int i = 1; i <= arr[0]; ++i)
            if (arr[i] < 0)
                ++n;
        return n;
    }
private:
    int find(int x) const {
        int crt = arr[x], last = x;
        while (crt > 0){
            last = crt;
            crt = arr[crt];
        }
        /*return value always be a valid index;*/
        return last;
    }

    /*path compressed find()*/
    int find_compressPath(int x){
        if (arr[x] < 0) return x;
        /*set all ptr in the path with root idx;*/
        return arr[x] = find_compressPath(arr[x]);
    }

    /*non-recursive path-compressed find()*/
    int find_compress_nonrec(int x){
        if (arr[x] < 0) return x;
        int res = x, crt = arr[x];
        /*Firstly find the root idx;*/
        while (crt > 0){
            res = crt;
            crt = arr[crt];
        }
        /*re-loop to set all ptr in the path;*/
        int last = x; crt = arr[x];
        while (crt > 0){
            arr[last] = res;
            last = crt;
            crt = arr[crt];
        }
        /*return result;*/
        return res;
    }

    int* arr;
};

void check_connection(MySet& set){
    int x, y;
    scanf("%d %d ", &x, &y);
    if ( set.checkElem(x, y) ) printf("yes\n");
    else printf("no\n");
    return;
}
void set_connection(MySet& set){
    int x, y;
    scanf("%d %d ", &x, &y);
    set.unionSet(x, y);
    return;
}
void check_network(MySet& set){
    int n = set.getSetNum();
    if (n == 1) printf("The network is connected.");
    else printf("There are %d components.", n);
    return;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);
    int N, x, y;
    char command;
    scanf("%d ", &N);
    MySet mSet {N};
    while (true){
        scanf("%c ", &command);
        switch(command){
        case 'C' : check_connection(mSet); break;
        case 'I' : set_connection(mSet); break;
        case 'S' : check_network(mSet); return 0;
        default  :
            return 0;
        }
    }
}