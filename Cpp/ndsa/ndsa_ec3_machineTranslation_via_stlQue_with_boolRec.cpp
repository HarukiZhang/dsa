#include<cstdio>
#include<queue>

using namespace std;

constexpr int kLen = 7;

queue<int> myQue;
bool rec[kLen + 10]{};

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    int m, n;
    scanf("%d %d", &m, &n);
    int w, times = 0;
    for (int i = 0; i < n; ++i){
        scanf("%d", &w);
        if (!rec[w]){
            ++times;
            if (myQue.size() >= m){
                rec[myQue.front()] = false;
                myQue.pop();
            }
            myQue.push(w);
            rec[w] = true;
        }
    }
    printf("%d\n", times);
}