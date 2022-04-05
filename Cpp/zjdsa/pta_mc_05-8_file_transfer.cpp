#include<iostream>
using namespace std;

constexpr int kMaxLen = 10010;

int N;

class UCSet {
public:
    UCSet(int n) : capacity{n} {
        for (int i = 1; i <= capacity; ++i)
            list[i] = -1;
    }


    void input(){
        int n1, n2;
        cin >> n1 >> n2;
        unionSet(n1, n2);
        return;
    }
    void check(){
        int n1, n2;
        cin >> n1 >> n2;
        if ( checkSet(n1, n2) ) cout << "yes\n";
        else cout << "no\n";
        return;
    }
    void stop(){
        int cnt = 0;
        for (int i = 1; i <= capacity; ++i)
            if (list[i] < 0)
                ++cnt;
        if (cnt == 1)
            cout << "The network is connected.";
        else cout << "There are " << cnt << " components.";
        return;
    }


private:

    void unionSet(int x, int y){
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (list[x] < list[y]){
            list[x] += list[y];
            list[y] = x;
        }
        else {
            list[y] += list[x];
            list[x] = y;
        }
        return;
    }
    bool checkSet(int x, int y){
        return find(x) == find(y);
    }

    int find(int x){
        if (list[x] < 0) return x;
        return list[x] = find(list[x]);
    }
    int capacity;
    int list[kMaxLen];
};



int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> N;
    UCSet ucset(N);
    while (true){
        char cmd;
        cin >> cmd;
        if (cmd == 'C') ucset.check();
        else if (cmd == 'I') ucset.input();
        else {
            ucset.stop();
            break;
        };
    }
    return 0;
}