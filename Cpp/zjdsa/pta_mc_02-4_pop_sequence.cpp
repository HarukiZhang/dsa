#include<cstdio>
using namespace std;

class Stack {
public:
    Stack(int maxSize)
        :cap(maxSize), arr(new int [maxSize])
    {}
    ~Stack(){
        delete[] arr;
    }
    bool empty() const {return top == -1;}
    bool push(int x){
        if (top == cap - 1) return false;
        arr[++top] = x;
        return true;
    }
    int pop(){
        if (empty()) return -1;
        return arr[top--];
    }
    int getSize() const {
        return top + 1;
    }
    void clear(){
        top = -1;
        return;
    }
private:
    int cap, top = -1;
    int* arr;
};

int main(){
    freopen("E:\\in.txt", "r", stdin);
    int M, N, K, tmp;
    scanf("%d %d %d ", &M, &N, &K);
    Stack myStk {M};
    for (int i = 0; i < K; ++i){
        int num = 1;
        bool flag = true;
        for (int j = 0; j < N; ++j){
            scanf("%d", &tmp);
            if (!flag) continue;
            while (num < tmp){
                if(!myStk.push(num++)){
                    flag = false;
                    break;
                }
            }
            if (num > tmp){
                if (myStk.pop() != tmp) flag = false;
            }
            else {//num == tmp;
                if (myStk.getSize() + 1 > M) flag = false;
                ++num;
            }
        }
        if (flag) printf("YES\n");
        else printf("NO\n");
        myStk.clear();
    }
    return 0;
}

/*
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2

ans:
YES
NO
NO
YES
NO //for beyond maxSize of stack;
*/