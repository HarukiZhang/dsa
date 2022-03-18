#include<iostream>
#include<stack>
using namespace std;

class Queue {
public:
    Queue(){}
    ~Queue(){}
    bool empty(){ return enque.empty() && otque.empty(); }
    void push_back(int x);
    int pop_front();
    int front();
private:
    stack<int> enque;
    stack<int> otque;
};

int main(){
    freopen("E:\\in.txt", "r", stdin);

    int N,tmp;
    char buf[5];
    cin >> N >> ws;
    Queue myque;
    for (int i = 0; i < N; ++i){
        cin >> buf >> ws;
        if (buf[0] == 'p'){
            cin >> tmp >> ws;
            myque.push_back(tmp);
        }
        else cout << myque.pop_front() << endl;
    }

    cout << ":::::" << endl;
    while (!myque.empty()) cout << myque.pop_front() << endl;
    return 0;
}

void Queue::push_back(int x){
    enque.push(x);
    return;
}

int Queue::pop_front(){
    if (otque.empty()){
        while (!enque.empty()){
            otque.push(enque.top());
            enque.pop();
        }
    }
    int ret = otque.top();//if otque still empty, segmentation error;
    otque.pop();
    return ret;
}

int Queue::front(){
    if (otque.empty()){
        while (!enque.empty()){
            otque.push(enque.top());
            enque.pop();
        }
    }
    return otque.top();//emtpy will cause error;
}