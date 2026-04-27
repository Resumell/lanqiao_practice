//一、一维前缀和
//用区间和来理解，sum[r] - sum[1] = sum[l,r] (但l=0时，sum[r]=sum[l-r])
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
const int n = 5;
int sum[n]; // 注意像sum这种全局变量的定义要写在函数的外面，这样才能调用进所有函数，包括主函数
int get_sum(int L, int R)
{
	if (L != 0)
	{
		return sum[R] - sum[L - 1];
	}
	else
	{
		return sum[R];
	}
}
int main()
{

	int arr[n] = { 1,3,7,5,2 };

	sum[0] = arr[0];//需要注意，要提前把sum[0],arr[0]算出来
	/*				  这是前缀和（以及所有递推类算法）的特性，不是每道题都这样。
					  简单说：只要公式里用了 i - 1，就必须先把 i = 0 的情况单独算好，否则递推启动不了。*/
	for (int i = 1; i < n; i++)
		sum[i] = sum[i - 1] + arr[i];
	cout << get_sum(2, 4) << endl;
	cout << get_sum(0, 3) << endl;
	cout << get_sum(3, 4) << endl;
	return 0;
}





//二、一维差分：
//知识1.差分数组可以通过前缀和得到原数组
	  //arr = 1，3，7，5，2
	  //d = 1，2，4，-2，-3
	  //sum = 1，3，7，5，2 
//知识2.差分标记（公式）：[L,R] + v = d[L] + v，d[R+1]-v
//ps：这种情况用于多次操作，单次询问（多次询问用其他的）

//原理：利用知识1的性质得到，只要d改了一个数，那么sum后面所有计算都会改这一个数，d[R+1]-v是抵消后续影响
//自己：差分就是分离状态算变化
	//  这题因为不加，所以不减（就是怎么算d的过程，这里直接全部设为0开始）
	//  最好arr加上差分就是加上变化
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
int d[6] = { 0 };
void add(int l, int r, int v)
{
	d[l] += v;
	d[r + 1] -= v;
}
int main()
{
	int arr[5] = { 1,3,7,5,2 };
	add(2, 4, 5);
	add(1, 3, 2);
	add(0, 2, -3);
	for (int i = 1; i < 5; i++)
	{
		d[i] += d[i - 1];
	}
	for (int i = 0; i < 5; i++)
	{
		arr[i] += d[i];
		printf("%d\n", arr[i]);
	}
	memset(d, 0, sizeof(0));//好习惯你不知道后面有没有询问
	return 0;
}



//三、二维前缀和
//公式有点多，放进下面代码中
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
const int n = 3, m = 4;			  //如果你下面g[][]要直接用这个的话，那么就要加const
int g[n][m] = { {1,5,6,8},    //[] 管"尺寸和下标"， {} 管"第一次装填数据
				{9,6,7,3},
				{5,3,2,4} };
int sum[n][m];
void pre_sum()//排序用，不用返回用void,好像因为sum是全局变量，所以也不用传数据给它
{
	sum[0][0] = g[0][0];//不要脑子浑写成sum[0][0] = 0了
	for (int i = 1; i < 3; i++)
		for (int j = 1; j < 4; j++)//其实这样不太好，因为第一行被计算了两次
		{
			sum[0][j] = sum[0][j - 1] + g[0][j];//第一行
			sum[i][0] = sum[i - 1][0] + g[i][0];//第一列
		}
	for (int i = 1; i < 3; i++)
		for (int j = 1; j < 4; j++)
		{
			sum[i][j] = g[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
			//sum[i][j] = g[i][j] - sum[i - 1][j] - sum[i][j] + sum[i - 1][j - 1];错了！这是算sum[i][j]不是sum{[][],[][]}
		}
}

int get_sum(int x1, int y1, int x2, int y2)
{
	if (x1 == 0 && y1 == 0)return sum[x2][y2];//(x2 == y2 == 0)是错的
	else if (x1 == 0 && y1 != 0)return sum[x2][y2] - sum[x2][y1 - 1];
	//else if (x1 == 0 && y1 != 0)return sum[x2][y2] - sum[x1][y1 - 1];是错的，坐标对应要小心
	else if (x1 != 0 && y1 == 0)return sum[x2][y2] - sum[x1 - 1][y2];
	else return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
	//else return sum[x2][y2] - sum[x1][y1 - 1] - sum[x1 - 1][y1] + sum[x1 - 1][y1 - 1];是错的，坐标要小心不对应
}
int main()
{
	pre_sum();
	cout << get_sum(1, 1, 2, 2) << " " << get_sum(0, 1, 1, 3);//" "输出空格
	return 0;
}

//四、二维差分
//公式：d[x1][y1]+=v    d[x1][y2+1]-=v		d[x2+1][y1]-=v		d[x2+1][y2+1]+=v
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
const int n = 3, m = 4;
int g[n][m] = { {1,5,6,8},
				{9,6,7,3},
				{5,3,2,4} };
int sum[n][m];
int d[n + 1][m + 1];
void add(int x1, int y1, int x2, int y2, int v) //当你不用返回值的时候，用void！只能用void！
{
	d[x1][y1] += v;
	d[x1][y2 + 1] -= v;
	d[x2 + 1][y1] -= v;
	d[x2 + 1][y2 + 1] += v;
}
void pre_sum()
{
	//d的延展需要结合二维前缀和知识
	sum[0][0] = d[0][0];
	for (int i = 1; i < n; i++)
	{
		sum[i][0] = sum[i - 1][0] + d[i][0];
	}
	for (int j = 1; j < m; j++)
	{
		sum[0][j] = sum[0][j - 1] + d[0][j];
	}
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++)
		{
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + d[i][j] - sum[i - 1][j - 1];
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			g[i][j] += sum[i][j];
		}
}

void PRINTF()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", g[i][j]);
		}
		printf("\n");
	}

}

int main()
{
	add(0, 0, 2, 1, 3);
	add(1, 1, 2, 2, -1);
	pre_sum();
	PRINTF();
	return 0;
}
