#include<cstdio>
using namespace std;

/*constexpr int kMaxUserNum = 1000, kMaxLevel = 6;*/
constexpr int kMaxFollower = 100;

typedef struct User *Link;
struct User {
    int UserID;
    Link link = nullptr;
    User() = default;
    User(int uid, Link lk) : UserID{uid}, link{lk} {}
};
typedef User Follower;

class SocialNet {
public:
    SocialNet(int n, int ml)
        : nums{n}, maxLevel{ml}, 
        users{new User[n+10]}, 
        visited{new bool[n+10]{}},
        queue{new int [n+10]}
    {
        read();
    }
    ~SocialNet(){
        delete[] queue;
        delete[] visited;
        delete[] users;
    }
    void insert(int flwer, int flwed){
        users[flwed].link = new Follower { flwer, users[flwed].link };
        return;
    }
    int BFSearch(int idx){
        int cnt = 0, level = 0, last = idx, tail;
        // queue<int> myque;
        int maxQSize = nums + 10, front = 0, back = 0;
        visited[idx] = true;
        // myque.push(idx);
        queue[back++] = idx;
        while (back != front){//queue.empty() == false;
            // int crt = myque.front(); myque.pop();
            int crt = queue[front];
            front = (front + 1) % maxQSize;
            Link ptr = users[crt].link;
            while (ptr){
                if (!visited[ptr->UserID]){
                    visited[ptr->UserID] = true;
                    // myque.push(ptr->UserID);
                    queue[back] = ptr->UserID;
                    back = (back + 1) % maxQSize;
                    tail = ptr->UserID;
                    ++cnt;
                }
                ptr = ptr->link;
            }
            if (crt == last){
                ++level;
                last = tail;
            }
            if (level == maxLevel) break;
        }
        for (int i = 1; i <= nums; ++i)
            visited[i] = false;
        return cnt;
    }
    void read(){
        int M, fd;
        for (int fr = 1; fr <= nums; ++fr){
            scanf("%d ", &M);
            while (M--){
                scanf("%d ", &fd);
                insert(fr, fd);
            }
        }
        return;
    }
private:
    int nums;
    int maxLevel;
    Link users;
    bool *visited;
    int *queue;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);

    int N, L, K, uid;
    scanf("%d %d ", &N, &L);
    SocialNet snw {N, L};
    scanf("%d ", &K);
    while (K--){
        scanf("%d ", &uid);
        printf("%d\n", snw.BFSearch(uid));
    }
    return 0;
}

/*
follow list:
1 : 3  2 3 4
2 : 0
3 : 2  5 6
4 : 2  3 1
5 : 2  3 4
6 : 1  4
7 : 1  5

followed list:
1 : 4
2 : 1
3 : 1 4 5
4 : 1 5 6
5 : 3 7
6 : 3
7 : 
*/