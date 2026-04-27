#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
LL T, l, r;
LL SUM(LL l, LL r)
{
	LL k = (r - 2 * l);
	if (k < 0)
	{
		return 0;
	}
	LL sum = ((k + 1) * (k + 2)) / 2;
	return sum;
}
int main()
{
	cin >> T;
	while (T--)
	{
		cin >> l >> r;
		cout << SUM(l, r) << "\n";
	}
	return 0;
}
