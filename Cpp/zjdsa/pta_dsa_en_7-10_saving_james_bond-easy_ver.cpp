#include<cstdio>
#include<cmath>
using namespace std;

constexpr double kDiam = 15.,
                 kRadi = kDiam / 2;
constexpr int kBound = 50;

struct Point {
    int x, y;
};

struct Crocodiles {
    int nums;
    Point *list;
    bool *veds;
    Crocodiles(int n) : nums(n){
        list = new Point[nums + 2];
        veds = new bool [nums + 2]{};//set to zero;
        for (int i = 0;i < nums; ++i)
            scanf("%d %d ", &list[i].x, &list[i].y);
    }
    ~Crocodiles(){
        delete[] veds;
        delete[] list;
    }
};

class Agent {
public:
    Agent(int jumpDist, int crocNum) : maxJumpDist(jumpDist){
        stack = new Point*[crocNum + 2]{};
    }
    ~Agent(){
        delete[] stack;
    }
    bool escape(Crocodiles& ccdls){
        stack[++top] = &crtPos;
        while (top >= 0){
            int i;
            for (i = 0; i < ccdls.nums; ++i){
                if (ccdls.veds[i] == false){//not yet jumpped to;
                    if ( ableToJump(ccdls.list[i]) ){
                        crtPos = *(stack[++top] = &ccdls.list[i]);//push pointer;
                        ccdls.veds[i] = true;
                        if (isSafe()) return true;
                        break;
                    }
                }
            }
            if (i == ccdls.nums && top >= 0){//no head to jump based on crt pos;
                --top;//pop crt pos, which is still on the top of the stack;
                if (top >= 0)
                    crtPos = *stack[top];
            }
        }
        return false;
    }
    bool isSafe(){
        return ( abs(crtPos.x) + maxJumpDist >= kBound 
            || abs(crtPos.y) + maxJumpDist >= kBound );
    }
    bool ableToJump(const Point& tar){
        int cmp = (tar.x - crtPos.x) * (tar.x - crtPos.x) 
                + (tar.y - crtPos.y) * (tar.y - crtPos.y);
        if (crtPos.x == 0 && crtPos.y == 0)//if on the island;
            return cmp <= (maxJumpDist + kRadi) * (maxJumpDist + kRadi);
        return cmp <= maxJumpDist * maxJumpDist;
    }
    // double distanceTo(const Point& tar){
    //     return pow( 
    //         pow(fabs(tar.x - crtPos.x), 2 ) + pow(fabs(tar.y - crtPos.y), 2),
    //         0.5 
    //     );
    // }
private:
    int maxJumpDist;
    int top = -1;
    Point crtPos { 0, 0 };
    Point **stack;//stack is an array of pointer;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int N, D;
    scanf("%d %d ", &N, &D);
    Agent james {D, N};
    Crocodiles heads{N};
    if ( james.escape(heads) )
        printf("Yes");
    else printf("No");
    return 0;
}