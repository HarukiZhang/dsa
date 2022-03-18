#include<cstdio>
#include<queue>

using namespace std;

class EdgeNode {
    friend class LGraph;
public:
    using Edge = EdgeNode*;
    EdgeNode(int headV, Edge next = nullptr)
        : vertex(headV), link(next)
    {}
private:
    int vertex = -1;
    Edge link = nullptr;
};

class VertexNode {
    friend class LGraph;
public:
private:
    bool visited = false;
    EdgeNode::Edge first = nullptr;
};

class LGraph {
public:
    using Vertex = VertexNode*;
    using Edge = EdgeNode*;
    LGraph(int vN, int eN)
        : vertexNum(vN), edgeNum(eN), headArr(new VertexNode [vertexNum + 2])
    {}
    ~LGraph(){
        Edge crt, last;
        for (int i = 0; i < vertexNum; ++i){
            crt = headArr[i].first;
            while (crt){
                last = crt;
                crt = crt->link;
                delete last;
            }
        }
        delete[] headArr;
    }
    void insertEdge(int tailV, int headV);
    void DFS();
    void DFS_recur(int vtxPtr);
    void BFS();
private:
    int vertexNum, edgeNum;
    Vertex headArr;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int N, E, tailV, headV;
    scanf("%d %d ", &N, &E);
    LGraph graph {N, E};
    for (int i = 0; i < E; ++i){
        scanf("%d %d ", &tailV, &headV);
        graph.insertEdge(tailV, headV);
        graph.insertEdge(headV, tailV);//bi-direction graph;
    }
    graph.DFS();
    graph.BFS();
    return 0;
}

void LGraph::insertEdge(int tailV, int headV){
    if (!headArr[tailV].first){
        headArr[tailV].first = new EdgeNode {headV};
        return;
    }
    Edge crt, last;
    last = headArr[tailV].first;
    crt = last->link;
    if (last->vertex > headV){
        headArr[tailV].first = new EdgeNode {headV, last};
        return;
    }
    while (crt && crt->vertex < headV){
        last = crt;
        crt = crt->link;
    }
    last->link = new EdgeNode {headV, last->link};
    return;
}

void LGraph::DFS_recur(int vtxPtr){
    Edge crt = headArr[vtxPtr].first;
    printf("%d ", vtxPtr);
    headArr[vtxPtr].visited = true;
    while (crt){
        if (!headArr[crt->vertex].visited)
            DFS_recur(crt->vertex);
        crt = crt->link;
    }
    return;
}

void LGraph::DFS(){
    Edge crt;
    for (int i = 0; i < vertexNum; ++i){
        if (!headArr[i].visited){
            printf("{ ");
            DFS_recur(i);
            printf("}\n");
        }
    }
    for (int i = 0; i < vertexNum; ++i)
        headArr[i].visited = false;
    return;
}

void LGraph::BFS(){
    Edge crt;
    queue<int> myque;
    for (int i = 0; i < vertexNum; ++i){
        if (headArr[i].visited) continue;
        printf("{ %d ", i);
        headArr[i].visited = true;
        if (headArr[i].first){
            myque.push(i);
            while (!myque.empty()){
                int ptr = myque.front();
                myque.pop();
                crt = headArr[ptr].first;
                while (crt){
                    if (!headArr[crt->vertex].visited){
                        printf("%d ", crt->vertex);
                        headArr[crt->vertex].visited = true;
                        myque.push(crt->vertex);
                    }
                    crt = crt->link;
                }
            }
        }
        printf("}\n");
    }
    for (int i = 0; i < vertexNum; ++i)
        headArr[i].visited = false;
    return;
}