//算法应用于：
//直接用公式：求1到n的 n^2和：n^2 = n(n + 1)(2n + 1) / 6 

//第一步错误尝试：太照顾计算机了，实际上可以大胆一点，直接暴力全部枚举也行
#include<iostream>								//#你都能忘加
#include<cstdio>
using namespace std;
int main()
{
	long long a = 0, b = 0, c = 0, ret = 0;
	for (; 255 >= a; a++)			//for(a,b,c; ;)只有最右变c有效，分号最左边是定义，一次一个就好
	{
		b = 0;
		for (; a > b; b++)
		{
			c = 0;
			for (; b > c; c++)
			{
				ret = ret + 1;
			}
		}
	}
	cout << ret;
	return 0;
}

//暴力枚举的方法：
#include<iostream>					//#include <bits/stdc++.h>这种是偷懒引入，但VS不认
using namespace std;
int main()
{
	long long ret = 0;
	for (long long a = 0; a <= 255; a++)
		for (long long b = 0; b <= 255; b++)
			for (long long c = 0; c <= 255; c++)
			{
				if (a < b && a < c)
				{
					ret = ret + 1;
				}
			}
	cout << ret;
	return 0;
}

//优化（这里把这道题当数学题做了）：
//原理：(k+1)^3 = k^3 + 3k^2 + 3k + 1							//^是**的意思
//		在利用相邻立方差相消法，联立得到。PS 不能用等差公式，又不是等差的，你注意点平方
//		求1到n的n^2和：n^2 = n(n + 1)(2n + 1) / 6 
#include<iostream>
using namespace std;
int main()
{
	long long k = 255;
	long long ret = 0;
	ret = (k * (k + 1) * (2 * k + 1)) / 6;								//C语言不能写数学连乘
	cout << ret;
	return 0;
}