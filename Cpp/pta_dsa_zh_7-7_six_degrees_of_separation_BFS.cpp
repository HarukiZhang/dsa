#include<cstdio>
#include<queue>
using namespace std;

/*
Using linked-list is more savable of space than matrix;
    when N == 1000, as long as E < 166333, that is 166.3 times of N;
    and there are only less than 33 * N edges in this problem;
*/

class LNode {
    friend class LGraph;
public:
    LNode() = default;
    LNode(int e, LNode *lk) : edgeTo{e}, link{lk} {}
private:
    int edgeTo;
    LNode *link = nullptr;
};

class LGraph {
public:
    LGraph(int vN, int eN)
    : vertNum{vN}, edgeNum{eN}, 
        vertex   {new LNode[vN + 10]},
        visited {new bool [vN + 10]{}}//initiate to zero;
    {
        readIn();
    }
    ~LGraph(){
        delete[] visited;
        delete[] vertex;
    }
    int sixDegSearch(int idx){
        int cnt = 0;
        queue<Elem> myque;
        myque.push(Elem {idx, 0} );
        while (!myque.empty()){
            Elem crtE = myque.front();
            if (crtE.depth == 7) break;
            ++cnt;//count for each popped/visited;
            myque.pop();
            visited[crtE.index] = true;
            LNode *crtP = vertex[crtE.index].link;
            while (crtP){
                if (!visited[crtP->edgeTo]){
                    myque.push(Elem {crtP->edgeTo, crtE.depth + 1} );
                }
                crtP = crtP->link;
            }
        }
        for (int i = 1; i <= vertNum; ++i)
            visited[i] = false;
        return cnt;
    }
    void insert(int tail, int head){
        /*insert at node head;*/
        LNode *node     = new LNode { head, vertex[tail].link };
        LNode *node_rev = new LNode { tail, vertex[head].link };
        vertex[tail].link = node;
        vertex[head].link = node_rev;
        return;
    }
    void readIn(){
        int tV, hV;
        for (int i =0; i < edgeNum; ++i){
            scanf("%d %d ", &tV, &hV);
            insert(tV, hV);
        }
        return;
    }

    struct Elem { int index, depth; };

private:
    int vertNum,
        edgeNum;
    LNode *vertex;//with head node, vertex starts from index 1;
    bool *visited;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int N, M;
    scanf("%d %d ", &N, &M);
    LGraph graph { N, M };
    for (int i = 1; i <= N; ++i){
        int cntedN = graph.sixDegSearch(i);
        double ratio = (double)cntedN / (double)N;
        printf("%d: %.2f%%\n", i, ratio * 100.0);
    }
    return 0;
}