#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

constexpr int kMaxLen = 100, kBound = 50;
constexpr double kDiam = 15, kRadi = kDiam / 2.0;

struct Point {
    int x, y;
    bool safe;
};

int vertN, jump, cnt = 0;
vector<Point> arr;
vector<int> graph[kMaxLen + 10];
int dist[kMaxLen + 10], path[kMaxLen + 10];

struct comp_dist {
    bool operator()(int a, int b) const {
        int dA = arr[a].x * arr[a].x + arr[a].y * arr[a].y;
        int dB = arr[b].x * arr[b].x + arr[b].y * arr[b].y;
        return dA < dB;
    }
};
bool ableToJump(Point& p1, Point& p2);
bool isSafe(Point& p);
void biuldGraph(int num);
/*min path unweighted single-source*/
int minPath(int ptr);
void printPath(int ptr);

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    cin >> vertN >> jump;
    Point point;
    for (int i = 0;i < vertN; ++i){
        cin >> point.x >> point.y;
        isSafe(point);
        arr.push_back(point);
    }
    /*also need to insert origin node for BFS to run;*/
    arr.push_back(Point { 0, 0, false});
    isSafe(arr.back());

    biuldGraph(vertN);
    
    int ptr = minPath(vertN);

    printPath( ptr );
    
    return 0;
}

int minPath(int ptr){
    /*initialization*/
    queue<int> myQue;
    for (int i = 0; i <= vertN; ++i){//all crocdiles + origin;
        dist[i] = path[i] = -1;
    }
    /*algorithm*/
    myQue.push(ptr);
    dist[ptr] = 0;//self to self, dist is 0;
    if (arr[ptr].safe){
        return ptr;//when james can directly escape;
    }
    while (!myQue.empty()){
        int crt = myQue.front();
        myQue.pop();
        auto it   = graph[crt].begin(),
             ited = graph[crt].end();
        for ( ; it != ited; ++it){
            if ( dist[*it] == -1 ){//un-visited;
                dist[*it] = dist[crt] + 1;//path len + 1;
                path[*it] = crt;//prev vertex;
                if (arr[*it].safe) return *it;//return entry;
                myQue.push(*it);
            }
        }
    }
    return -1;
}

void printPath(int ptr){
    int i = ptr;
    if (i == -1){
        cout << 0 << endl;
        return;
    }
    int myStk[kMaxLen + 10]{}, top = -1;
    cout << dist[i] + 1 << endl;//plus the last one jump towards the shore;
    while (i != -1 && i != vertN){
        myStk[++top] = i;
        i = path[i];
    }
    while (top >= 0){
        Point &tmp = arr[ myStk[top--] ];
        cout << tmp.x << " " << tmp.y << endl;
    }
    return;
}

void biuldGraph(int num){
    auto ited = arr.end(),
         it1  = arr.begin();
    for (int i = 0; it1 != ited; ++it1, ++i){
        auto it2  = arr.begin();
        for (int j = 0; it2 != ited; ++it2, ++j){
            if (i != j && ableToJump(*it1, *it2))
                graph[i].push_back(j);
        }
    }
    /*special for origin: need to sort by jump distance;*/
    sort(graph[num].begin(), graph[num].end(), comp_dist());
    return;
}

bool ableToJump(Point& p1, Point& p2){
    int tmp = (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
    if ( (p1.x==0&&p1.y==0) || (p2.x==0&&p2.y==0) )
        return (kRadi+jump)*(kRadi+jump) >= tmp;
    return jump*jump >= tmp;
}

bool isSafe(Point& p){
    int absX = p.x >= 0 ? p.x : -p.x;
    int absY = p.y >= 0 ? p.y : -p.y;
    int oprd = absX > absY ? absX : absY;
    p.safe = (oprd + jump >= kBound);
    if (p.safe) return true;
    return false;
}