/*
请编写程序判定一个给定的工程项目的任务调度是否可行；
如果该调度方案可行，则计算完成整个工程项目需要的最短时间，并输出所有的关键活动。

输入格式:
输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点
（即衔接相互依赖的两个子任务的节点，例如：若任务2要在任务1完成后才开始，
则两任务之间必有一个交接点）的数量。
交接点按1~N编号，M是子任务的数量，依次编号为1~M。
随后M行，每行给出了3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，
整数间用空格分隔。

输出格式:
如果任务调度不可行，则输出0；否则第1行输出完成整个工程项目需要的时间，
第2行开始输出所有关键活动，每个关键活动占一行，按格式“V->W”输出，
其中V和W为该任务开始和完成涉及的交接点编号。关键活动输出的顺序规则是：
任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。
*/
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

constexpr int kMaxVertexN = 128, kInfty = ~(1<<31);

struct Edge {
    int start, end, consum, mobile;
};
struct Vertex {
    int earlyT, lateT, inDegree, outDegree;
};
typedef int VertexIdx;
typedef int EdgeIdx;

/*linearly store real node of vertices and edges;*/
vector<Edge> edges;
vector<Vertex> vertices;

/*only store ptr/idx in graph structure*/
vector<EdgeIdx> network      [kMaxVertexN];
vector<EdgeIdx> rev_adj_list [kMaxVertexN];

int N, M;

int traversal_forward(){
    /*initialization*/
    queue<VertexIdx> que;
    int inDegrees[kMaxVertexN];
    for (VertexIdx i = 1; i <= N; ++i){
        inDegrees[i] = vertices[i].inDegree;
        if (vertices[i].inDegree == 0){
            vertices[i].earlyT = 0;
            que.push(i);            
        }
    }
    int vertN = 0, totTime = 0;
    /*algorithm*/
    while ( !que.empty() ){
        int crt = que.front();
        que.pop();
        ++vertN;
        for (EdgeIdx ei : network[crt]){
            Edge &rE = edges[ei];
            Vertex &rV = vertices[rE.end];
            int tmpTime = vertices[crt].earlyT + rE.consum;
            if (tmpTime > rV.earlyT)//take max;
                rV.earlyT = tmpTime;
            /*core logic: visit a vertex after its degree becomes 0*/
            --inDegrees[rE.end];
            if (inDegrees[rE.end] == 0){
                que.push(rE.end);
                /*update total time by taking max;*/
                if (totTime < rV.earlyT)
                    totTime = rV.earlyT;
            }
        }
    }
    if (vertN != N)//cyclic;
        return -1;
    return totTime;
}

void traversal_backward(int totT){
    queue<VertexIdx> que;
    int outDegrees[kMaxVertexN];
    for (VertexIdx i = 1; i <= N; ++i){
        outDegrees[i] = vertices[i].outDegree;
        if (vertices[i].outDegree == 0){
            /*exit vertices should all be set to total time,
            rather than itself's earlyT*/
            vertices[i].lateT = totT;
            que.push(i);
        }
    }
    while ( !que.empty() ){
        int crt = que.front();
        que.pop();
        for (EdgeIdx ei : rev_adj_list[crt]){
            Edge &rE = edges[ei];
            Vertex &rV = vertices[rE.start];
            int tmpTime = vertices[crt].lateT - rE.consum;
            if (tmpTime < rV.lateT)//take min;
                rV.lateT = tmpTime;
            /*mobile = latest completion - earliest starting - task consumption;*/
            int tmpMobl = tmpTime - rV.earlyT;
            if (tmpMobl > rE.mobile)//take max; mobile initally = -1;
                rE.mobile = tmpMobl;
            /*backward traversal also apply to degree logic but out degree;*/
            --outDegrees[rE.start];
            if (outDegrees[rE.start] == 0){
                que.push(rE.start);
            }
        }
    }
    return;
}

void printKeyTask(){
    stack<EdgeIdx> stk;
    /*by input order iterate vertices;*/
    for (VertexIdx i = 1; i <= N; ++i){
        for (EdgeIdx ei : network[i]){
            if (edges[ei].mobile == 0)//no mobile time == key task;
                stk.push(ei);
        }
        /*using print stack to reverse order of input;*/
        while ( !stk.empty() ){
            Edge &rE = edges[stk.top()];
            stk.pop();
            cout << rE.start << "->" << rE.end << endl;
        }
    }
    return;
}

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    Edge edgein {-1, -1, -1, -1};
    cin >> N >> M;
    edges.push_back(edgein);//head node index 0;
    for (EdgeIdx i = 1; i <= M; ++i){
        cin >> edgein.start >> edgein.end >> edgein.consum;
        edges.push_back(edgein);
        network[edgein.start].push_back(i);
        /*using reversed adjacent list to statistic indegree;*/
        rev_adj_list[edgein.end].push_back(i);
    }
    Vertex tmpV {-1, kInfty, 0, 0};//initial value: earlyT = minValue, lateT = maxValue;
    vertices.push_back(tmpV);//head node index 0;
    for (VertexIdx i = 1; i <= N; ++i){
        tmpV.inDegree = rev_adj_list[i].size();
        tmpV.outDegree = network[i].size();
        vertices.push_back(tmpV);//real node of vertex;
    }
    int totalTime = traversal_forward();
    if ( totalTime == -1 )
        cout << 0;
    else {
        /*assure DAG, Directed-Acyclic-Graph;*/
        cout << totalTime << endl;
        traversal_backward(totalTime);
        printKeyTask();
    }
    return 0;
}

/*
Reference:
https://blog.csdn.net/tuzigg123/article/details/46923963

Case one:
Input:	
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2

Output:
17
1->2
2->4
4->6
6->7


Case two:
Input:
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4

Output:
18
1->2
2->5
5->8
5->7
7->9
8->9


Case three:
Input:
11 14
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
8 3 7
9 3 7
9 10 6
4 10 2
10 6 5
6 11 4

Output:
21
3->4
4->10
6->11
8->3
9->3
10->6


Case four:
Input:	
4 5
1 2 4
2 3 5
3 4 6
4 2 3
4 1 2

Output:
0
*/