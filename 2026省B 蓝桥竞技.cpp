//错误思路：错在没有考虑类型数组可以再拆分的情况，6种类每种类5人就炸
#include <iostream>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
LL arr[5], Aarr[10010];
LL T, N, Ai;

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> Ai;
			Aarr[i] = Ai;
		}
		sort(Aarr, Aarr + N, greater<int>());//降序greater<int>()
		for (int i = 0; i < N; i++)
		{
			sort(arr, arr + 5);
			arr[0] += Aarr[i];
		}
		if (arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4])
			//if (arr[0] == arr[1] == arr[2] == arr[3] == arr[4])是错的！所以少年加油吧
		{
			printf("T");
		}
		else
		{
			printf("F");
		}
		memset(Aarr, 0, sizeof(Aarr));
		memset(arr, 0, sizeof(arr));
	}
	return 0;
}







//正确思路：按照题目要求条件，针对性解决
/*
要求：
5 人成团：每支战队由且只能由 5 名选手组成。
职业互斥：同一支战队内的 5 名选手，必须来自 5 种完全不同的位置。
*/
/*
S 必须能被 5 整除（不然总有人剩）
mx <= k（人数最多的职业，不能超过战队数。否则这种职业必然有两个人挤进同一支战队，直接违规）
*/
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include<cstring>	//是为了memset函数加上
#define LL long long
using namespace std;
LL Aarr[100010], T, N, sumA, Ai, k;
int flase = 0;
int main()
{
	cin >> T;
	while (T--)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> Ai;
			Aarr[i] = Ai;
			sumA += Ai;
		}
		if (sumA % 5 != 0)
		{
			printf("F");
			printf("\n");
			sumA = 0;
			memset(Aarr, 0, sizeof(Aarr));
			continue;//注意不要把重新初始化跳过了！
		}
		k = sumA / 5;
		for (int i = 0; i < N; i++)
			//for (const auto& x : Aarr)这题这么写不好，他会把一整个数组都看一遍，没必要
		{
			if (Aarr[i] > k)
			{
				printf("F");
				flase = 0;	//它的对立输出需要标识！ //要记得标假！不能忘！	
				break;	//如果是假就直接break
			}
			else
			{
				flase = 1;
			}
		}
		if (flase != 0)
		{
			printf("T");
		}
		printf("\n");	//注意输出细节
		memset(Aarr, 0, sizeof(Aarr));		//注意循环体数组初始化
		sumA = 0;
		flase = 0;
	}
	return 0;
}