#define _CRT_SECARE_NO_WARNINGS
#include<iostream>
#include<cstdio>
using namespace std;
#define LL long long
int main()
{
	int i, j, cnt = 0;
	for (i = 1; i; i++)
	{
		cnt = 0;
		for (j = 1; j <= i; j++)
		{
			if (i % j == 0 && cnt < 100)
			{
				cnt++;
			}
			if (cnt == 100)
			{
				cout << i;
				return 0;
			}
		}

	}
	return 0;
}