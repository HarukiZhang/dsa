//拨钟问题
#include <iostream>
using namespace std;

int clockPlt[3][3];
int mainRoot[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};		 //当前的最短路径
void isOk(const int i1, const int i2, const int i3); //如果验证成功 那么返回1  否则返回0
									//将前3行的拨钟数目进行枚举 返回枚举方法 循环写在这里面
void enumerate(){//结果存在mainRoot中
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int l = 0; l < 4; l++)
				isOk(i, j, l);
}
/*
 1        ABDE 
 2        ABC 
 3        BCEF 
 4        ADG 
 5        BDEFH 
 6        CFI 
 7        DEGH 
 8        GHI 
 9        EFHI         
*/
void isOk(const int i1, const int i2, const int i3) //如果验证成功 那么返回1  否则返回0
{
	static int resMin = 30; //用来记录最少的次数；

	int i4 = (4 - (clockPlt[0][0] + i1 + i2) % 4) % 4;			  //确定A   A   B  C
	int i5 = (4 - (clockPlt[0][1] + i1 + i2 + i3) % 4) % 4;	      //确定B   D   E   
	int i6 = (4 - (clockPlt[0][2] + i2 + i3) % 4) % 4;			  //确定C   G
	int i7 = (4 - (clockPlt[1][0] + i1 + i4 + i5) % 4) % 4;	      //确定D
	int i8 = (4 - (clockPlt[2][0] + i4 + i7) % 4) % 4;			  //确定G
	int i9 = (4 - (clockPlt[1][1] + i1 + i3 + i5 + i7) % 4) % 4;  //确定E
	//f  h  i
	if ((clockPlt[1][2] + i3 + i5 + i9) % 4 == 0 
		&& (clockPlt[2][1] + i5 + i7 + i8 + i9) % 4 == 0 
		&& (clockPlt[2][2] + i6 + i8 + i9) % 4 == 0) //满足条件
	{

		int resultTemp[9] = {i1, i2, i3, i4, i5, i6, i7, i8, i9};
		int sumTmp = 0;
		for (int i = 0; i < 9; ++i)
			sumTmp += resultTemp[i];
		if (sumTmp < resMin){ //找到了更优秀的解
		
			resMin = sumTmp;
			
			for (int i = 0; i < 9; i++)
				mainRoot[i] = resultTemp[i]; //更新解决方案
			return;
		}
		else //不符合要求 直接return继续寻找
		{
			return;
		}
	}
}

int main()
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> clockPlt[i][j];
		}
	}

	//将前3行的拨钟数目进行枚举 返回枚举方法
	enumerate();

	for (int i = 0; i < 9; i++)
	{
		while (mainRoot[i]){
			cout << i + 1 << " ";
			--mainRoot[i];
		}
	}

	return 0;
}