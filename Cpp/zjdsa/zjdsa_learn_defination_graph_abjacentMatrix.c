#include<stdio.h>
#include<stdlib.h>

#define kMaxVertexNum 10
#define INFINITY 65536

typedef int Vertex;
typedef int WeightType;

typedef struct ENode *PtrToEdge;
struct ENode {
    Vertex TailV, HeadV;
    WeightType Weight;
};
typedef PtrToEdge Edge;

typedef struct GNode *PtrToGraph;
struct GNode {
    int VertexNum;
    int EdgeNum;
    WeightType GMatrix[kMaxVertexNum][kMaxVertexNum];
};
typedef PtrToGraph MGraph;

MGraph CreateGraph( int _VertexNum ){
    MGraph Graph = (MGraph) malloc(sizeof(struct GNode));
    Graph->VertexNum = _VertexNum;
    Graph->EdgeNum = 0;
    for (Vertex i = 0; i < _VertexNum; ++i)
        for (Vertex j = 0; j < _VertexNum; ++j)
            Graph->GMatrix[i][j] = INFINITY;
    return Graph;
}

void InsertEdge( MGraph Graph, Edge E ){
    Graph->GMatrix[E->TailV][E->HeadV] = E->Weight;
    /*if bi-direction graph, Mtx[head][tail] is also need to set;*/
    Graph->GMatrix[E->HeadV][E->TailV] = E->Weight;
    return;
}

void showGraphMatrix(MGraph Graph){
    printf("   | ");
    for (int i = 0; i < Graph->VertexNum; ++i)
        printf("%-3d ", i);
    printf("\n\n");
    for (int i = 0; i < Graph->VertexNum; ++i){
        printf("%-3d| ", i);
        for (int j = 0; j < Graph->VertexNum; ++j){
            if (Graph->GMatrix[i][j] != INFINITY)
                printf("%-3d ", Graph->GMatrix[i][j]);
            else printf("0   ");
        }
        printf("\n");
    }
    return;
}

int main(){
    freopen("E:\\in.txt", "r", stdin);
    int N;
    scanf("%d ", &N);
    MGraph Graph = CreateGraph(N);
    scanf("%d ", &Graph->EdgeNum);
    struct ENode edgeIn;
    for (int i = 0; i < Graph->EdgeNum; ++i){
        scanf("%d %d %d ", &edgeIn.TailV, &edgeIn.HeadV, &edgeIn.Weight);
        InsertEdge(Graph, (Edge)&edgeIn);
    }
    showGraphMatrix(Graph);
    free(Graph);
    return 0;
}