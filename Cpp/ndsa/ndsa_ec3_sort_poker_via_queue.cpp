#include<iostream>
#include<queue>
#include<string>
using namespace std;
struct Node {
    char suit;
    char numb;
};
queue<Node> firQue[9];
queue<Node> secQue[4];
string str;
int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    int N;
    Node node;
    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> node.suit >> node.numb >> ws;
        switch (node.numb){
            case '1' :
                firQue[0].push(node);
                break;
            case '2' :
                firQue[1].push(node);
                break;
            case '3' :
                firQue[2].push(node);
                break;
            case '4' :
                firQue[3].push(node);
                break;
            case '5' :
                firQue[4].push(node);
                break;
            case '6' :
                firQue[5].push(node);
                break;
            case '7' :
                firQue[6].push(node);
                break;
            case '8' :
                firQue[7].push(node);
                break;
            case '9' :
                firQue[8].push(node);
                break;
            default : break;
        }
    }
    for (int i = 0; i < 9; ++i){
        cout << "Queue" << i + 1 << ':';
        while (!firQue[i].empty()){
            node = firQue[i].front();
            cout << node.suit << node.numb << ' ';
            switch (node.suit){
                case 'A' :
                    secQue[0].push(node);
                    break;
                case 'B' :
                    secQue[1].push(node);
                    break;
                case 'C' :
                    secQue[2].push(node);
                    break;
                case 'D' :
                    secQue[3].push(node);
                    break;
                default : break;
            }
            firQue[i].pop();
        }
        cout << endl;
    }
    for (int i = 0; i < 4; ++i){
        cout << "Queue";
        switch (i) {
            case 0 :
                cout << "A:";
                break;
            case 1 :
                cout << "B:";
                break;
            case 2 :
                cout << "C:";
                break;
            case 3 :
                cout << "D:";
                break;
            default : break;
        }
        while (!secQue[i].empty()){
            node = secQue[i].front();
            cout << node.suit << node.numb << ' ';
            str.push_back(node.suit);
            str.push_back(node.numb);
            str.push_back(' ');    
            secQue[i].pop();
        }
        cout << endl;
    }
    cout << str << endl;
    return 0;
}