#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
LL n, ai[200010], sum, S;
int main()
{
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::cin >> ai[i];
		sum += ai[i];
	}
	for (int i = 0; i < n; i++)
	{
		S += (ai[i] * (sum - ai[i]));
		//S += (ai[i] * (sum - ai[i]));思路是对的，但是答案是错的，原因是因为每个数字会在另一个数字倒乘它的时候又多算一次，所以遇到不重复乘积的时候要/2
	}
	printf("%lld", S / 2);//上面需要的/2操作
	return 0;
}