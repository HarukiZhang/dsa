#include <cstdio>
#include <list>

std::list<int> mylist;
int cowN;
bool settleCows(int dist);
inline int bSearch(int left, int right);

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    
    int stallN, input;
    scanf("%d %d", &stallN, &cowN);
    for (int i = 0; i < stallN; ++i){
        scanf("%d", &input);
        mylist.push_back(input);
    }
    mylist.sort();
    int res = bSearch(1, (*mylist.rbegin() - *mylist.begin())/(cowN - 1));
    printf("%d", res);
}

int bSearch(int left, int right){
    int optim = left;
    while (left <= right){
        int mid = (right + left) / 2;
        if (settleCows(mid)){
            if (optim < mid) optim = mid;
            left = mid + 1;
        }
        else right = mid - 1;
    }
    return optim;
}

bool settleCows(int dist){
    auto it = mylist.begin();
    int restCowsN = ::cowN - 1,
        curLoc = *it;
    for (; it != mylist.end(); ++it){
        if (*it >= curLoc + dist){
            curLoc = *it;
            --restCowsN;
        }
    }
    if (restCowsN <= 0) return true;
    return false;
}
