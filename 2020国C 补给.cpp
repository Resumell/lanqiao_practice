//前置知识点：

//1. ^ 异或：13 ^ (1 << 2) 是干嘛的？（把第2位的1变成0）

//2.Floyd的循环上的关键理解（算本身）：
//k中转站（单个） i头 j尾
/*假如0->3->2->5->1可以到达，0->1不可以到达，太远了，这种情况下，如果是i作为阶段象征的情况，
0->1和1->0可以的情况就运行不了，因为它当i = 0的时候它最重要的3->1的情况被卡死了，要想打通要等到i = 3的时候，
给3->2打通，同理1->0也是相同的问题，都是被小大小这种情况卡住了，导致0和1这种情况原本可以的被断了，而如果是k为
阶段的时候，情况就不一样了，k为阶段，是把每个节点看成一个个小孤岛，把一条条路找出来点亮，然后连起来，就算0->1和
1->0一开始没有被第一时间连起来，可是随着路越来越多之后，他们最终会被连起来，而i作为阶段就不会被”点亮“，就更没
有连起来一说了*/

//3.最后一个for循环集合体：状压（算状态）
//i状态 j当前状态的光标位置 k中转站（所有）
//包括最后一个for循环，也是一样的


#include<iostream>
#include<cstdio>
using namespace std;
const int N = 20, inf = 1e9;
int n, d;
double ans = inf, x[N], y[N], f[1 << N][N], dis[N][N];
int main() {
	cin >> n >> d;
	for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			double dist = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));//欧几里得距离 
			if (dist > d) dis[i][j] = inf;//不让该边过去 
			else dis[i][j] = dist;
		}
	for (int k = 0; k < n; ++k)//Floyd 最短路 
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	memset(f, 0x7f, sizeof(f)), f[1][0] = 0;//初始化 
	for (int i = 1; i < 1 << n; ++i)//阶段 
		for (int j = 0; j < n; ++j) if (i >> j & 1)
			for (int k = 0; k < n; ++k) if ((i ^ 1 << j) >> k & 1)//状态 
				f[i][j] = min(f[i][j], f[i ^ 1 << j][k] + dis[k][j]);//转移 
	for (int i = 0; i < n; ++i) ans = min(ans, f[(1 << n) - 1][i] + dis[i][0]);//注意题意要求回到第一个点 
	printf("%.2lf", ans);
	return 0;
}
