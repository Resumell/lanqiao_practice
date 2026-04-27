//前驱所有知识或要点：
//1.注意文字游戏，比如暗示你说多个点，但实际上可以取一个点也可以
//2.DFS = 深度优先搜索 = 选择一条路走到底，返回上一个岔路口，选择另外一条
	//DP需要记忆对应值，而且有时需要给每个值加一个标签（vis）
	//下面给了案例（斐波那契数列）
//3.for(int v : g[u])把g[u]里的每个元素依次给到v用
//4.逆元 = 模意义下的"倒数"  -> a / b = a * inv (b)(mod 998244353) 用这个是因为模运算不能直接用/
//5.对 998244353 取模的结果意思是 %998244353取余数
	//1(mod MOD)的意思除以MOD余1
	//b × inv(b) ≡ 1 (mod MOD)
	//a ≡ b(mod MOD)表示a和b除以MOD之后余数相同
//6.判断奇偶可以用(b & 1)当两个都是1作结尾的时候返回1
//7.在这题的DP:
	//dp[u][0] = dp[v1][2]+dp[v2][2]
	//dp[u][1] = dp[v1][0]*(dp[w1][1]+dp[w2][2])
	//dp[u][2] = dp[v1][1]+dp[v1][2]
//8.mod意思是取模，取余数；7 mod 8 = 7，x %= mod，x≡y(modm)【x%m=y%m 】；

/*
9. 逆元：为什么 x−1≡x**mod−2(modmod)？
这是费马小定理的推论。
费马小定理说：
如果 mod 是质数（998244353确实是），且 x 不是 mod 的倍数，那么：x**mod−1≡1(modmod)
变形求逆元：两边同时乘以 x−1（也就是除以 x ）：x**mod−2≡x**−1(modmod)
所以算逆元就是算 x**mod−2，用快速幂跑一遍就行。
*/
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream> 
#include<cstdio>
#include<vector>h'h'
#define LL long long
using namespace std;
 
vector<int> g[300010];//vector是动态成员函数，g[]防止越界，多开10个
void add(int x, int y)
{
	g[x].push_back(y); //push_back是vector的成员函数，末尾加上（x）.还有其他的pop_vack(),size()，clear()，empty()等
	g[y].push_back(x);
}
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		add(u, v);
	}
	return 0;
}


//记忆运用的简单运用
//long long f(int n) {
//	if (n <= 2) return 1;
//	if (vis[n]) return dp[n];  // 检查：算过没？
//
//	// 没算过，开始算
//	dp[n] = f(n - 1) + f(n - 2);   // 算答案
//
//	vis[n] = true;              // 算完了！贴标签！改0为1
// 
//	return dp[n];
//}