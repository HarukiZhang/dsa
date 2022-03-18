#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
    int main() {
        freopen("E:\\Downloads\\in.txt", "r", stdin);
        char nums[20];
        char* pbg = nums;
        scanf("%s", nums);
        int length = strlen(nums);
        char* digit = nums + length;
        while (--digit != nums) {
            if (*(digit - 1) == '-') break;
            else if (*digit == '0') *digit = '\0';
            else break;
        }
        length = (digit - nums) / sizeof(char);
        int times;
        if (nums[0] == '-') {
            pbg++;
            times = length / 2;
        }
        else times = (length + 1) / 2;
        while (times-- > 0) {
            char tmp = *pbg;
            *pbg = *digit;
            *digit = tmp;
            pbg++;  digit--;
        }
        printf(nums);
    }