#include<iostream>
#include<queue>
using namespace std;
constexpr int kMaxVN=12;

class MGraph {
public:
    MGraph(int vertN, int edgeN)
        :Nv(vertN),Ne(edgeN)
    {
        for (int i = 0; i < Nv; ++i){
            visited[i] = false;
            for (int j = 0; j < Nv; ++j){
                GMtx[i][j] = 0;
            }
        }
    }
    ~MGraph(){}
    void insert(int tV, int hV){
        GMtx[tV][hV] = 1;
        GMtx[hV][tV] = 1;
        return;
    }
    void DFS_recur(int crtV){
        cout<<crtV<<" ";
        visited[crtV] = true;
        for(int i=0;i<Nv;++i)
            if(GMtx[crtV][i]!=0 && !visited[i])
                DFS_recur(i);
        return;
    }
    void DFS(){
        for(int i=0;i<Nv;++i){
            if(!visited[i]){
                cout<<"{ ";
                DFS_recur(i);
                cout<<"}\n";
            }
        }
        for(int i=0;i<Nv;++i)
            visited[i]=false;
        return;
    }
    void BFS(){
        queue<int> myque;
        for(int i=0;i<Nv;++i){
            if (visited[i]) continue;
            cout<<"{ "<< i << " ";
            visited[i] = true;
            myque.push(i);
            while(!myque.empty()){
                int j = myque.front();
                myque.pop();
                for (int k = 0; k < Nv; ++k)
                    if (GMtx[j][k] != 0 && !visited[k]){
                        cout << k << " ";
                        visited[k] = true;
                        myque.push(k);
                    }
            }
            cout<<"}\n";
        }
        for (int i = 0; i < Nv; ++i)
            visited[i] = false;
        return;
    }
private:
    int Nv, Ne;
    int GMtx[kMaxVN][kMaxVN]{};
    bool visited[kMaxVN]{};
};

int main(){
    freopen("E:\\in.txt", "r", stdin);

    int N, E, tailV, headV;
    cin >> N >> E;
    MGraph graph {N,E};
    for (int i=0;i<E;++i){
        cin >> tailV >> headV;
        graph.insert(tailV, headV);
    }
    graph.DFS();
    graph.BFS();
    return 0;
}