/*讨论4.1 搜索树比较序列的判别
如果有人跟你说，在某棵搜索树上找63的过程是：先比较根39，然后比较根的右儿子101，
接着比较101的左儿子25，再比较25的右儿子63，这样就找到了。

也就是说，他在搜索树查找时的比较序列是：39，101，25，63。问：这样的查找序列可能吗？
你否能设计一个算法或者程序，判别给定的查找序列是否合理？
*/
#include<iostream>

int main(){
    freopen("E:\\in.txt", "r", stdin);
    int n, arr[64]{};
    std::cin >> n;
    for (int i = 0; i < n; ++i){
        std::cin >> arr[i];
    }
    for (int i = 0; i < n - 1; ++i){
        if (arr[i + 1] > arr[i]){
            for (int j = i + 1; j < n; ++j){
                if (arr[j] <= arr[i]){
                    std::cout << "No";
                    return 0;
                }
            }
        }
        else if (arr[i + 1] < arr[i]){
            for (int j = i + 1; j < n; ++j){
                if (arr[j] >= arr[i]){
                    std::cout << "No";
                    return 0;
                }
            }
        }
        else {
            std::cout << "no";
            return 0;
        }
    }
    std::cout << "Yes";
    return 0;
}