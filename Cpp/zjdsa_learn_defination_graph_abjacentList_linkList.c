#include<stdio.h>
#include<stdlib.h>

#define kMaxVertexNum 16
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct ENode* PtrToENode;
struct ENode {
    Vertex HeadV, TailV;
    WeightType Weight;
};
typedef PtrToENode Edge;

typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

typedef struct VNode {
    PtrToAdjVNode FirstEdge;
} AdjList[kMaxVertexNum];

typedef struct GNode* PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateGraph( int VertexNum ){
    Vertex V;
    LGraph Graph;

    Graph = (LGraph) malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (V = 0; V < VertexNum; ++V)
        Graph->G[V].FirstEdge = NULL;
    
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E){
    PtrToAdjVNode NewNode;

    NewNode = (PtrToAdjVNode) malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->HeadV;
    NewNode->Weight = E->Weight;
    NewNode->Next = NULL;

    PtrToAdjVNode OldNode = Graph->G[E->TailV].FirstEdge;
    if (!OldNode){
        Graph->G[E->TailV].FirstEdge = NewNode;
    }
    else {
        while (OldNode->Next) OldNode = OldNode->Next;
        OldNode->Next = NewNode;
    }
    return;
}

void Traversal(LGraph Graph){
    PtrToAdjVNode crtN;
    for (int i = 0; i < Graph->Nv; ++i){
        printf("%d :", i);
        crtN = Graph->G[i].FirstEdge;
        while (crtN){
            printf(" %d", crtN->AdjV);
            crtN = crtN->Next;
        }
        printf("\n");
    }
    return;
}

void freeGraph(LGraph Graph){
    PtrToAdjVNode crtN, last;
    for (int i = 0; i < Graph->Nv; ++i){
        crtN = Graph->G[i].FirstEdge;
        while (crtN){
            last = crtN;
            crtN = crtN->Next;
            free(last);
        }
    }
    free(Graph);
    return;
}

int sparceEdgeNum(int verN){
    /*compute the appropriate number of Edge in a graph that has verN vertex
    so that the graph is sparce enough for being space efficient stored in 
    adjacent-list comparing to adjacent-matrix;*/
    return (verN * verN * sizeof(WeightType) - verN * sizeof(PtrToAdjVNode)) / 
        (2 * sizeof(struct AdjVNode));
}

int main(){
    printf("%d", sparceEdgeNum(100));

    // freopen("E:\\in.txt", "r", stdin);
    // int vertexNum;
    // scanf("%d ", &vertexNum);
    // LGraph myGraph = CreateGraph(vertexNum);
    // int edgeNum;
    // scanf("%d ", &edgeNum);
    // if (edgeNum != 0){
    //     Edge E = (Edge) malloc(sizeof(struct ENode));
    //     for (int i = 0; i < edgeNum; ++i){
    //         scanf("%d %d %d ", &E->TailV, &E->HeadV, &E->Weight);
    //         InsertEdge(myGraph, E);
    //     }
    //     free(E);
    // }
    // Traversal(myGraph);
    // freeGraph(myGraph);
    return 0;
}