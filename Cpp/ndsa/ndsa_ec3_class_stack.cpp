#include<iostream>
using namespace std;

template<typename T>
class Stack {
private:
    int mSize;
    int iTop;
    T* arr;

public:
    Stack()
        : mSize{512}, iTop{-1}, arr{new T [mSize]}
    {}
    ~Stack(){
        delete[] arr;
    }
    void clear(){
        iTop = -1;
    }
    bool empty(){
        return iTop == -1;
    }
    bool push(T elem){
        if (iTop == mSize - 1)
            return false;
        arr[++iTop] = elem;
        return true;
    }
    bool pop(){
        if (empty())
            return false;
        --iTop;
        return true;
    }
    T top(){
        return arr[iTop];
    }
};

int main(){
    Stack<int> myStk;
    myStk.push(1);
    myStk.push(2);
    myStk.push(3);
    myStk.push(4);
    myStk.pop();
    myStk.push(5);
    while (!myStk.empty()){
        cout << myStk.top() << endl;
        myStk.pop();
    }

}