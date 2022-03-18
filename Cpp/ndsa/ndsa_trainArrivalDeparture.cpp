/*Train Arrival/Departure Problem
Count the number of the order for n trains arriving and then departing;
Specifically, what is each order;
*/
#include<iostream>
#include<stack>
#include<cmath>

int n, cnt;
int arr[10]{};
std::stack<int> myStk;

int main(){
    while (std::cin >> n){
        for (int i = 0; i < n; ++i)
            arr[i] = i + 1;
        int itm = 1 << (2 * n);
        int dig = 2 * n - 1;
        cnt = 0;
        for (int i = 0; i < itm; ++i){
            int balc = 0;
            int j;
            for (j = dig; j >= 0; --j){
                if (i >> j & 1)
                    ++balc;
                else
                    --balc;
                if (balc < 0)
                    break;
            }
            if (j < 0 && balc == 0){
                ++cnt;
                int m = 0;
                for (int k = dig; k >= 0; --k){
                    if (i >> k & 1)
                        myStk.push(arr[m++]);
                    else {
                        std::cout << myStk.top();
                        myStk.pop();
                    }
                }
                std::cout << "\n" << std::flush;
            }
        }
        std::cout << "There are " << cnt << "kinds.\n" << std::flush;
        std::cout << "\n" << std::flush;
    }
}