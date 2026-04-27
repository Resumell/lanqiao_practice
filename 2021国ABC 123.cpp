//算法应用于：
//2025省PythonA 偏蓝那到题目用的公式，这道题不行，得算法
//PS:sum(k)=i=1开始到k的i(i+1)/2  = i(i + 1)(i + 2)/6 //本题没有用这个思路和公式
//用的算法：坐标二分-截段取余-前缀差分法（找中间片段都可以用）
#include<iostream>
#include<cstdio>
using namespace std;

long long Rxk(long long x)
{
	if (x <= 0)
	{
		return 0;
	}
	long long k, mid, left = 1, right = 10000000, test, n, sum;	//这里的right不是x，不是pos  
	while (left <= right)
	{
		mid = (left + right) / 2;
		test = mid * (mid + 1) / 2;						//二分法是用一条自己的线通过函数覆盖题目的线
		if (test >= x)									//而其中的二分mid要确保要覆盖的住你给的标定数本身的全部，所以if中test>=x	
		{
			right = mid - 1;							//left和right决定越来越靠近答案和结束条件
			k = mid;									//点金之笔，让答案k不会因为right = mid - 1错过真正的答案mid，下一次找的到更对的mid才又改k
		}												  //简单的记就是，记录答案的又不会随着解除循环的一起减一
		else
		{
			left = mid + 1;
		}
	}
	k = k - 1;
	n = x - (k * (k + 1) / 2);
	sum = (n * (n + 1) / 2) + (k * (k + 1) * (k + 2) / 6);
	return sum;
}

int main()
{
	int T;
	cin >> T;
	long long l, r, sum1, sum2;
	while (T--)        //这种简单的输入提取记住
	{
		cin >> l >> r;
		cout << Rxk(r) - Rxk(l - 1);//不用写sum = Rxk(r)这种，直接给Rxk
		cout << "\n";
	}
	return 0;
}


//自己又写一遍
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
LL Rxk(LL x)
{
	LL k, n, sum, left = 1, right = 2000000, mid, test;
	while (left <= right)
	{
		mid = (left + right) / 2;
		test = (mid * (mid + 1)) / 2;
		if (test >= x)
		{
			right = mid - 1;
			k = mid;						//点金之笔，让答案k不会因为right = mid - 1错过真正的答案mid，下一次找的到更对的mid才又改k
		}
		else
		{
			left = mid + 1;
		}
	}
	return k;
}
LL SUM(LL x)
{
	if (x <= 0)
	{
		return 0;
	}
	LL k, n, sum1, sum2;
	k = Rxk(x);
	k = k - 1;
	sum1 = (k * (k + 1) * (k + 2)) / 6;
	n = (x - (k * (k + 1) / 2));
	sum2 = n * (n + 1) / 2;
	return sum1 + sum2;
}
int main()
{
	LL x, T, l, r;
	cin >> T;
	while (T--)
	{
		std::cin >> l >> r;
		cout << SUM(r) - SUM(l - 1) << "\n";
	}
	return 0;
}