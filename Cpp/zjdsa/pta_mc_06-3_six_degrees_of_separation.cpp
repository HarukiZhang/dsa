#include<iostream>
#include<iomanip>
#include<vector>
#include<cstring>
using namespace std;

constexpr int kMaxVertex = 1024, kMaxEdge = 33 * kMaxVertex;
constexpr int kMaxDegree = 6;

vector<int> graph[kMaxVertex];
int myque[kMaxVertex], front = 0, back = 0;
bool visited[kMaxVertex]{};

int vertN, edgeN;

double BFS(int ptr){
    int cnt = 0, tail = ptr, last = -1, degree = 0;
    memset(visited + 1, 0, vertN);
    front = back = 0;
    myque[back++] = ptr;
    visited[ptr] = true;
    ++cnt;
    while ( front != back ){
        int crt = myque[front];//top();
        front = (front + 1) % kMaxVertex;//pop();
        for (int vi : graph[crt]){
            if ( visited[vi] == false ){
                visited[vi] = true;
                myque[back] = vi;
                back = (back + 1) % kMaxVertex;
                ++cnt;
                last = vi;
            }
        }
        if (crt == tail){
            tail = last;
            ++degree;
        }
        if (degree == kMaxDegree)
            break;
    }
    return (double)cnt;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> vertN >> edgeN;
    int vi1, vi2;
    for (int i = 0; i < edgeN; ++i){
        cin >> vi1 >> vi2;
        graph[vi1].push_back(vi2);
        graph[vi2].push_back(vi1);
    }
    for (int i = 1; i <= vertN; ++i){
        double tmp = BFS(i);
        cout << i << ": ";
        cout << setiosflags(ios::fixed) << setprecision(2) 
             << tmp / vertN * 100.0 << "%" << endl;
    }
    return 0;
}
