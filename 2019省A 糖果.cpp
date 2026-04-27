//ps  if (dp[i]==INF) continue; 是状压 DP 的标准起手式这题没加上，是因为数据没卡你
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define LL long long
int N, M, K;				   //定义可以写在外面
int dp[1 << 20], v[1 << 20];//dp[1<<20]记录状态，v记录每种状态的编号
int main()
{
	scanf("%d%d%d", &N, &M, &K); //scanf只能读取int类型！
	memset(dp, 0x3f, sizeof(dp));//memset(dp, 0x3f3f3f, sizeof(dp));也行，一样的，用fill更好
	dp[0] = 0;					 //必须要在memset之后设置
	//记录下每一包
	for (int i = 1; i <= N; i++)
	{
		int h, h0 = 0;
		for (int j = 1; j <= K; j++)
		{
			scanf("%d", &h);
			h0 = h0 | (1 << (h - 1));	//把状态压缩的关键代码		//不要忘记-1，因为h是从0开始数的
		}
		dp[h0] = 1;			//记录当前这个状态	//同时说明直接就有一包
		v[i] = h0;			//给定此状态一个编号
	}
	for (int i = 0; i <= (1 << M) - 1; i++)//这里从i = 0开始，不是1，而且要设置开始dp[0]=0;
	{
		for (int j = 1; j <= N; j++)
		{
			dp[i | v[j]] = min(dp[i | v[j]], dp[i] + 1);// dp[i]+1说的是加一包	//dp[i|v[j]]是新dp（状态），真有的话会直接运行 dp[i]+1
			// 因为用的是min，所有dp一开始设置memset最大
			//我知道v有迷惑性，但实际上输出值是dp（状态）的大小（满足状态有多少包），v只是每包的编号
		}
	}
	if (dp[(1 << M) - 1] != 0x3f3f3f3f)				//注意这里填几个3f
	{
		printf("%d\n", dp[(1 << M) - 1]);
0	}
	else
	{
		printf("-1");
	}
	return 0;
}