#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

constexpr int kMaxLen = 16;

vector<int> graph[kMaxLen];
bool visited[kMaxLen]{};

int N, E;

void read(){
    int v1, v2;
    for (int i = 0; i < E; ++i){
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    for (int i = 0; i < E; ++i)
        sort(graph[i].begin(), graph[i].end());
    return;
}

void DFS(int v){
    cout << v << " ";
    visited[v] = true;
    for (int e : graph[v])
        if (visited[e] == false)
            DFS(e);
    return;
}

void print_DFS(){
    for (int i = 0; i < N; ++i){
        if (visited[i] == false){
            cout << "{ ";
            DFS(i);
            cout << "}\n";
        }
    }
    for (int i = 0; i < N; ++i)
        visited[i] = false;
    return;
}

void print_BFS(){
    queue<int> que;
    for (int i = 0; i < N; ++i){
        if (visited[i] == false){
            que.push(i);
            visited[i] = true;
            cout << "{ ";
            while (!que.empty()){
                int eg = que.front();
                que.pop();
                cout << eg << " ";
                for (int ei : graph[eg]){
                    if (visited[ei] == false){
                        visited[ei] = true;
                        que.push(ei);
                    }
                }
            }
            cout << "}\n";
        }
    }
    for (int i = 0; i < N; ++i)
        visited[i] = false;
    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> N >> E;
    read();
    print_DFS();
    print_BFS();
    return 0;
}