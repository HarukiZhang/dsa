#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

constexpr int kMaxLen = 100, kBound = 50;
constexpr double kDiam = 15, kRadi = kDiam / 2.0;
int depth = 0, jump, cnt = 0;
bool visited[kMaxLen + 10]{};

struct Point {
    int no;
    int x, y;
    bool safe;
};

vector<Point> arr, graph[kMaxLen + 10], path;
stack<Point> prt;

void biuldGraph(int num);

bool ableToJump(Point& p1, Point& p2);
bool isSafe(Point& p);

void BFS(int ptr);

int main(){
    int N;
    cin >> N >> jump;
    Point point;
    for (int i = 0;i < N; ++i){
        point.no = i;
        cin >> point.x >> point.y;
        isSafe(point);
        arr.push_back(point);
    }
    biuldGraph(N);
    BFS();
    cout << depth << endl;
    while (!path.empty()){
        cout << path.top().x << " " << path.top().y << endl;
        path.pop();
    }
    return 0;
}

void biuldGraph(int num){
    for (auto it1 = arr.begin(); it1 != arr.end(); ++it1){
        for (auto it2 = arr.begin(); it2 != arr.end(); ++it2){
            if (ableToJump(*it1, *it2))
                graph[it1->no].push_back(*it2);
        }
    }
    Point ori {num, 0, 0, false};
    for (auto it = arr.begin(); it != arr.end(); ++it)
        if (ableToJump(ori, *it))
            graph[num].push_back(*it);
    return;
}

bool ableToJump(Point& p1, Point& p2){
    int tmp = (p1.x-p2.x)*(p1.x*p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
    if ( (p1.x==0&&p1.y==0) || (p2.x==0&&p2.y==0) )
        return (kRadi+jump)*(kRadi+jump) >= tmp;
    return jump*jump >= tmp;
}

bool isSafe(Point& p){
    int absX = p.x >= 0 ? p.x : -p.x;
    int absY = p.y >= 0 ? p.y : -p.y;
    int oprd = absX > absY ? absX : absY;
    p.safe = (oprd + jump >= kBound);
    if (p.sage) return true;
    return false;
}

void BFS(int ptr){
    queue<Point> myQue;
    for (auto it = graph[ptr].begin(); it != graph[ptr].end(); ++it){
        if (!visited[it->no]){
            visited[it->no] = true;
            myQue.push(*it);
        }
    }
    while (!myQue.empty()){
        int tmp = myQue.front().no;
        myQue.front().no = cnt++;
        path.push_back(myQue.front());
        myQue.pop();
        BFS(tmp);
    }
    return;
}