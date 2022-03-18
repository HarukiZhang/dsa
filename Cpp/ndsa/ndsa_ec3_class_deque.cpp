#include<iostream>

using namespace std;

class Queue {
private:
    int mSize;
    int iFront;
    int iBack;
    int* arr;

public:
    Queue(int sz = 1000)
    : mSize{sz + 1}, iFront{1}, iBack{0}, arr{new int [mSize]}
    {}
    ~Queue(){ delete[] arr; }
    void clear(){ iFront = (iBack + 1) % mSize; }
    bool empty(){ return (iBack + 1) % mSize == iFront; }
    bool full(){ return (iBack + 2) % mSize == iFront; }
    bool push(int elem){
        if (full())
            return false;
        iBack = (iBack + 1) % mSize;
        arr[iBack] = elem;
        return true;
    }
    bool pop_front(int& elem){
        if (empty())
            return false;
        elem = arr[iFront];
        iFront = (iFront + 1) % mSize;
        return true;
    }
    bool pop_back(int& elem){
        if (empty())
            return false;
        elem = arr[iBack];
        if (iBack != 0)
            iBack = (iBack - 1) % mSize;
        else
            iBack = mSize - 1;
        return true;
    }
};

int t, n, o, m, e;
Queue myQue;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    cin >> t;
    for (int i = 0; i < t; ++i){
        cin >> n;
        for (int j = 0; j < n; ++j){
            cin >> o >> m;
            if (o != 2){
                myQue.push(m);
            }
            else {
                if (m != 0){
                    myQue.pop_back(e);
                }
                else {
                    myQue.pop_front(e);
                }
            }
        }
        if (myQue.empty()){
            cout << "NULL" << endl;
        }
        else {
            while (!myQue.empty()){
                myQue.pop_front(e);
                cout << e << ' ';
            }
            cout << endl;
        }
    }
}