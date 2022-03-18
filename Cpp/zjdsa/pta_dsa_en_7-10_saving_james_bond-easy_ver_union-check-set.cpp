#include<iostream>
#include<cmath>
using namespace std;

constexpr int kBound = 50;
constexpr double kDiam = 15, kRadi = kDiam / 2;

struct Point {
    int x, y;
    int parent = -1;
    bool isSafe;
};

class UCSet {
public:
    UCSet(int n, int mj) : nums(n), list(new Point [n + 2]{}), maxJump(mj)
    {
        list[0] = Point { 0, 0, -1, false };//islend center as first loc;
        for (int i = 1; i <= nums; ++i){
            cin >> list[i].x >> list[i].y;
            list[i].isSafe = judgeSafe(list[i]);
        }
        findParent();
    }
    ~UCSet(){
        delete[] list;
    }

    bool checkSet(int crt, int tar){
        crt = find_compressPath(crt);
        tar = find_compressPath(tar);
        return crt == tar;
    }
    void unionSet(int crt, int tar){
        // cout << "Union:" << crt << "->" << tar << " : ";/*debug*/
        crt = find_compressPath(crt);
        tar = find_compressPath(tar);
        // cout << "; actual:" << crt << "->" << tar << "\n";/*debug*/
        if (list[tar].parent < list[crt].parent){
            list[tar].parent += list[crt].parent;
            list[crt].parent = tar;
        }
        else {
            list[crt].parent += list[tar].parent;
            list[tar].parent = crt;
        }
        return;
    }
    void escape(){
        for (int i = 1; i <= nums; ++i){
            if (list[i].isSafe && checkSet(i, 0)){
                cout << "Yes";
                return;
            }
        }
        cout << "No";
        return;
    }

    // void printOut(){
    //     cout << "No.\tx\ty\tparent\tisSafe\n" << flush;
    //     for (int i = 0; i <= nums; ++i){
    //         Point& out = list[i];
    //         cout << i << "\t" << out.x << "\t" << out.y << "\t"
    //             << out.parent << "\t" << boolalpha << out.isSafe << "\n";
    //     }
    //     return;
    // }

private:
    // int find(int x){
    //     int last;
    //     while (x != -1){
    //         last = x;
    //         x = list[x].parent;
    //     }
    //     return last;
    // }
    int find_compressPath(int x){
        if (list[x].parent < 0) return x;
        return list[x].parent = find_compressPath(list[x].parent);
    }

    // double distanceTo(const Point& a, const Point& b){
    //     return sqrt( pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0) );
    // }

    bool ableToJump(const Point& a, const Point& b){
        if ((a.x == 0 && a.y == 0) || (b.x == 0 && b.y == 0))
            return (maxJump + kRadi)*(maxJump + kRadi) >= 
            (a.x - b.x)*(a.x - b.x) + (a.y- b.y)*(a.y- b.y);
        return maxJump * maxJump >= (a.x - b.x)*(a.x - b.x) + (a.y- b.y)*(a.y- b.y); 
    }

    void findParent(){
        for (int i = 1; i <= nums; ++i){
            for (int j = 0; j <= nums; ++j){
                if ( !checkSet(i, j) && ableToJump(list[i], list[j]) ){
                    unionSet(i, j);
                }
            }
        }
        return;
    }

    bool judgeSafe(const Point& p){
        int absX = p.x >= 0 ? p.x : -p.x;
        int absY = p.y >= 0 ? p.y : -p.y;
        int oprd = absX > absY ? absX : absY;
        if (oprd + maxJump >= kBound) return true;
        return false;

        // if (absX + maxJump >= kBound) return true;
        // if (absY + maxJump >= kBound) return true;
        // return false;
    }

private:
    int nums;
    Point *list;
    int maxJump;
};

int main(){
    // freopen("E:\\in.txt", "r", stdin);
    int N, D;
    cin >> N >> D;
    UCSet ucset {N, D};
    ucset.escape();
    // cout << "\n";
    // ucset.printOut();
    return 0;
}