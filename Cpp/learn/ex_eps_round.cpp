#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

#define EPS 0.0001

double eps_round(double val){
    /*
    delete the eps error if the eps error is smaller than given standard EPS;
    return original value the error is bigger than EPS;
    */
    double tempint = round(val);
    double err = abs(tempint - val);
    if (err < EPS)
        return tempint;
    else
        return val;
}

int main(){
    double temin, temout;
    char sigin, sigout;
    scanf("%lf%c", &temin, &sigin);
    if (sigin == 'F' || sigin == 'f'){
        temout = (temin - 32)/1.8;
        sigout = 'C';
    }
    else {
        temout = 1.8 * temin + 32;
        sigout = 'F';
    }
    double temp = eps_round(temout);
    if (temp == (int) temp)
        printf("%d%c", (int) temp, sigout);
    else
        printf("%.2f%c", temout, sigout);
    return 0;
}

/*描述
输入摄氏温度，就将其转换为华氏温度输出；输入华氏温度，就将其转换成摄氏温度数输出。两者的转换关系是：

摄氏温度 = （华氏温度 - 32 ) ÷ 1.8

输入
摄氏温度或华氏温度。摄氏温度的格式是一个整数或小数后面加'C'或'c'，华氏温度的格式是一个整数或小数后面加'F'或'f'。
输出
转换后的温度。摄氏温度就在数值后面加'C'，华氏温度就在数值后面加'F'。
如果数值是整数，就应该输出整数形式，
如果数值是小数，则保留小数点后面2位。

样例输入
样例1 33.8F
样例2 43C 
样例3 12.8c

样例输出
样例1 1C
样例2 109.40F
样例3 55.04F
*/