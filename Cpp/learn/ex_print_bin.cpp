#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<type_traits>

template<class T>
void print_bin(T num){
    // print a scaler;
    int i = sizeof(T) * 8 - 1;
    for (int j = i; j >= 0; --j)
        std::cout << std::setw(2) << j << " ";
    std::cout << std::endl;
    // print the num;
    if (std::is_signed<T>::value && num >> i & 1) {
        size_t reagent = INT_MAX;
        if (sizeof(T) == 8) reagent = LLONG_MAX;
        else if (sizeof(T) == 1) reagent = CHAR_MAX;
        num = ~(num & (T)reagent) + 1;
        --i;
        std::cout << 1 << " ";
    }
    for (; i >= 0; i--)
        std::cout << std::setw(2) << (num >> i & 1) << " ";
    std::cout << std::endl;
}

void intToBinary(int deci_num, char* bin_buffer){
    int i = 31;
    if (deci_num < 0){
        deci_num = ~abs(deci_num) + 1;
        i = 30;
        *bin_buffer = '1';
    }
    for (; i >= 0; i--){
        *(bin_buffer + (31 - i)) = (deci_num >> i & 1) + 48;
    }
    *(bin_buffer + 32) = '\0';
}

int main(){
    int a = 0x1f'ff'ff'ff'ff;
    std::cout << a << std::endl;
}