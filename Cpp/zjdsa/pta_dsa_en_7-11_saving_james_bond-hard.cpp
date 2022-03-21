/*Logic is just pure BFS in GuoWei's paradigm;

Specific for this problem, it require that when there are more than one shortest path,
    choose the one with shortest first jump;
    For this requirement, I just sort the connections of origin node, so that in BFS,
        it will access nodes by order of shortest first jump;

struct Point node consume many space, so only store them once in vector<Point> arr,
    in all other container, just store the index of them (like the logic of list sort);
    later, if need to get info of Point, just use index to access arr;

Moreover, attention to the special situation when James can directly jump from Island
    to the Safe, which should output jump step as 1, and no crocdile need to be stepped;
*/
#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

constexpr int kMaxLen = 100, kBound = 50;
constexpr double kDiam = 15, kRadi = kDiam / 2.0;
int jt = 0, jump, cnt = 0;
bool visited[kMaxLen + 10]{};

struct Point {
    int no;
    int x, y;
    bool safe;
};

struct Elem {
    int ptr, parent;
};


vector<Point> arr;
vector<int> graph[kMaxLen + 10];
vector<Elem> path;
stack<int> printStk;

/*getDist just compute square-sum, which is differentiable enough;*/
inline int getDist(Point& p);

struct comp_dist {
    bool operator()(int a, int b) const {
        return getDist(arr[a]) < getDist(arr[b]);
    }
};

void biuldGraph(int num);

bool ableToJump(Point& p1, Point& p2);
bool isSafe(Point& p);

bool BFS(int ptr);

void printPath();

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N;
    cin >> N >> jump;
    Point point;
    for (int i = 0;i < N; ++i){
        point.no = i;
        cin >> point.x >> point.y;
        isSafe(point);
        arr.push_back(point);
    }
    /*also need to insert origin node for BFS to run;*/
    arr.push_back(Point {N, 0, 0, false});
    isSafe(arr.back());

    biuldGraph(N);
    
    if ( BFS(N) ) printPath();
    else cout << 0 << endl;
    
    return 0;
}

void biuldGraph(int num){
    auto ited = arr.end();
    for (auto it1 = arr.begin(); it1 != ited; ++it1){
        for (auto it2 = arr.begin(); it2 != ited; ++it2){
            if (it1 != it2 && ableToJump(*it1, *it2))
                graph[it1->no].push_back(it2->no);
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

bool BFS(int ptr){//should start from (0, 0)
    queue<Elem> myQue;
    visited[ptr] = true;
    if (arr[ptr].safe) return true;//special for when James can directly escape;
    myQue.push(Elem { ptr, -1} );//the first elem's parent is -1;
    Elem tmp;
    while (!myQue.empty()){
        tmp = myQue.front();
        path.push_back(tmp);
        myQue.pop();
        if (arr[tmp.ptr].safe) return true;
        auto ited = graph[tmp.ptr].end();
        for (auto it = graph[tmp.ptr].begin(); it != ited; ++it){
            if (!visited[*it]){
                visited[*it] = true;
                //parent counter depends on myQue.pop() opt;
                myQue.push(Elem {*it, ::cnt});
            }
        }
        ++::cnt;
    }
    return false;
}

void printPath(){
    int i = cnt;
    if (i != 0){
        while (path[i].parent != -1){
            printStk.push(path[i].ptr);
            i = path[i].parent;
            ++jt;
        }
    }
    cout << jt + 1 << endl;
    while (!printStk.empty()){
        Point& ref = arr[printStk.top()];
        cout << ref.x << " " << ref.y << endl;
        printStk.pop();
    }
    return;
}

int getDist(Point& p){
    return p.x * p.x + p.y * p.y;
}


/*Sample1
17 15
10 -21
10 21
-40 10
30 -50
20 40
35 10
0 -10
-25 22
40 -40
-30 30
-10 22
0 11
25 21
25 10
10 10
10 35
-30 10

output:
4
0 11
10 21
10 35

*/

/*Sample2:
4 13
-12 12
12 12
-12 -12
12 -12

output:
0

*/