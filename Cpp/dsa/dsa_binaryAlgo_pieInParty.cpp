#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

constexpr double PI = 3.141592653589793;
constexpr double EPS = 1e-9;

vector<double> myvec;
int pieN, frdN;

bool cutPie(double pSize);
double bSearch(double left, double right);

int main(){
    freopen("E:\\Downloads\\in.txt", "r", stdin);
    double input;
    scanf("%d %d", &pieN, &frdN);
    for (int i = 0; i < pieN; ++i){
        scanf("%lf", &input);
        myvec.push_back(input);
    }
    sort(myvec.begin(), myvec.end());
    double res = bSearch(0., *myvec.rbegin());
    printf("%.3f", res * res * PI);
}

double bSearch(double left, double right){
    int cnt_loop = 0;
    double optim = left, mid;
    while (left + EPS < right){
        mid = (left + right) / 2.;
        if (cutPie(mid)){
            optim = mid;
            left = mid + EPS;
        }
        else 
            right = mid - EPS;
        if (++cnt_loop > 45)
            break;
    }
    return optim;
}

bool cutPie(double pSize){
    int restFrdN = frdN + 1;// Add on the host;
    for (auto it = myvec.begin(); it != myvec.end(); ++it){
        double curR = *it;//current pie's radius;
        int receivN = static_cast<int>(curR / pSize * curR / pSize);
        restFrdN -= receivN;
    }
    if (restFrdN <= 0) return true;
    return false;
}



/*
INPUT:
3 3
4 3 3

OUTPUT:
25.133


r = 2.82844168570
1670457.071
127970697.010

*/