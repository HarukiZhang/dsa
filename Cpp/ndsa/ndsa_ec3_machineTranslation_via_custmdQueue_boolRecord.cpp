#include<cstdio>

using namespace std;

constexpr int kLen = 7;

class Dict {
    int mSize = kLen + 10,
        pSize = 0,
        iFront = 1, iBack = 0;
    int* arr;
    bool* rec;
public:
    Dict() : arr{new int[mSize]}, rec{new bool[mSize]{}} {}
    ~Dict(){ 
        delete[] arr;
        delete[] rec;
    }
    bool empty(){ return pSize == 0; }
    int size(){ return pSize; }
    bool push(int v){
        if ((iBack + 2) % mSize == iFront) //queue full;
            return false;
        iBack = (iBack + 1) % mSize;
        arr[iBack] = v;
        rec[v] = true;
        ++pSize;
        return true;
    }
    bool pop_old(){
        if (empty())
            return false;
        rec[arr[iFront]] = false;
        iFront = (iFront + 1) % mSize;
        --pSize;
        return true;
    }
    bool absent(int v){
        return !rec[v];
    }
};


int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    Dict dict;
    int m, n;
    scanf("%d %d", &m, &n);
    int w, times = 0;
    for (int i = 0; i < n; ++i){
        scanf("%d", &w);
        if (dict.absent(w)){
            ++times;
            if (dict.size() >= m)
                dict.pop_old();
            dict.push(w);
        }
    }
    printf("%d\n", times);
}