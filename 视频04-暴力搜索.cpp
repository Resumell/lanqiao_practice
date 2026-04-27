//暴力搜索
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
int n, m, v[1001], w[1001];
int ans = 0;
void dfs(int i, int vi, int wi)
{
	if (i > n)
	{
		if (wi <= m && ans < vi)
		{
			ans = vi;
		}
		return;
	}
	dfs(i + 1, vi + v[i], wi + w[i]);//这里的wi和vi是记录对应的体积和价值大小的
	dfs(i + 1, vi, wi);
}
int main()
{
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;

		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &v[i]);
			scanf("%d", &w[i]);
		}
		ans = 0;
		dfs(1, 0, 0);//如果有多组要算的话，可以把dfs放在while循环里面，并且ans每次全部清0,输出也要在while循环里面
		cout << ans;
	}
	return 0;
}


//进阶：加上记忆
//进阶：记忆化搜索（数组空间）
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
int n, m, v[1001], w[1001];
int ans = 0;
int dp[1001][1001];//用来记录状态，比较之后记录或更新,要敢想，最多1001*1001种可能（那也比2**n要强！）
void dfs(int i, int vi, int wi)
{
	if (i > n)
	{
		if (ans < vi)ans = vi;
		return;
	}
	//接下来使用dp[][]需要有横向的思想，[i]表示当前状态，肤浅的理解也可以说是表示当前是第几个，[wi+w[i]]是对应选之后的重量
	//无论怎么比较的，ans拿的是最大的那个情况的v
	if (wi + w[i] <= m && dp[i][wi + w[i]] < vi + v[i]) //更新选择i的情况
	{
		dp[i][wi + w[i]] = vi + v[i];
		dfs(i + 1, vi + v[i], wi + w[i]);
	}
	if (dp[i][wi] < vi)//更新不选择i的情况 
	{
		dp[i][wi] = vi;
		dfs(i + 1, vi, wi);
	}
	//ps：两个dps互不影响，互相交叉推算所有可能，同时融合dp[][]记忆算法(每次i更新对应dp两种方案更新)，以空间换时间
}
int main()
{
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &v[i], &w[i]);
		}
		ans = 0;
		memset(dp, -1, sizeof(dp));//注意初始化，要填的数字可能会影响上面代码判断的报错，比如填0，导致第二个dfs一直0<0不成立运行不了
		dfs(1, 0, 0);
		cout << ans;

	}
	return 0;
}



//进阶：递推/迭代
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
int n, m, v[1001], w[1001], dp[1001][1001];
int main()
{
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		memset(dp, 0, sizeof(dp));//这里价值为0最低，就是背包的价值
		for (int i = 1; i <= n; i++) {
			scanf("%d", &v[i]);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &w[i]);
		}
		//直接找到两个阶段的最优解（几个（i）物品，用多少（j）空间）
		for (int i = 1; i <= n; i++) {  //这里思路变成i是考虑到第i个物品，j表示容量限制
			for (int j = 1; j <= m; j++) {   //j表示容量
				if (j - w[i] >= 0) {
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]); //注意dp[i - 1][j - w[i]] + v[i]是i-1的最优[j-w[i]]的情况+v[i]和dp[i - 1][j]比！
				}
				else
					dp[i][j] = dp[i - 1][j];
			}
		}
		cout << dp[n][m] << endl;
	}
	return 0;
}