//跳台阶1.0（没有记忆，直接嵌套输出答案）
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int n, ans;
int digui(int x)
{
	if (x != 1 && x != 2)
	{
		return digui(x - 1) + digui(x - 2);
	}
	else
	{
		return 1;
	}

}
int main()
{
	cin >> n;
	ans = digui(n);
	cout << ans << endl;
	return 0;
}
//跳台阶2.0（有记忆，嵌套输出答案，ps：N大栈出溢出）
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
LL jiyi[100010];
LL n, ans;
LL digui2(int x)
{
	if (jiyi[x] > 0)
	{
		return jiyi[x];
	}
	if (x != 1 && x != 2)
	{
		jiyi[x] = digui2(x - 1) + digui2(x - 2);
		return jiyi[x];
	}

}
int main()
{
	cin >> n;
	fill(jiyi, jiyi + 100010, -1);//memset(jiyi, -1, sizeof(jiyi));最好用fill，memset只能填写0和-1
	ans = digui2(n);
	jiyi[1] = jiyi[2] = 1;
	cout << ans << endl;
	return 0;
}



//跳台阶2.0（有记忆，直接用数组递推）
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
LL f[N];  // 直接用数组递推

int main() {
	int n;
	cin >> n;

	f[1] = f[2] = 1;
	for (int i = 3; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];  // 没有递归，O(n)顺序计算
	}
	cout << f[n] << endl;
	return 0;
}












//1-n取任意数个，输出所有方案（按每个数的状态输出答案）
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
const int N = 100010;
int state[N];
int n;
void dfs(int x)
{
	if (x > n)
	{
		for (int i = 1; i <= n; i++)
		{
			if (state[i] == 1)
			{
				cout << i;
			}
		}
		cout << endl;
		return;
	}
	state[x] = 1;
	dfs(x + 1);
	state[x] = 0;

	//不选直接给新状态2，不要犹豫
	state[x] = 2;
	dfs(x + 1);
	state[x] = 0;
}
int main()
{
	cin >> n;
	dfs(1);
	return 0;
}





//1-n全排列（for循环填数组填满输出答案，状态是看这个数填没填过）
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
const int N = 10010;
int n;
int state[N] = { 0 };
int ans[N] = { 0 };
void dfs(int x) //dfs给的x是arr的位数，算第几个数的意思
{
	if (x > n)
	{
		for (int i = 1; i <= n; i++)
		{
			cout << ans[i];
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= n; i++)
	{
		if (state[i] != 1)
		{
			state[i] = 1;//这里不要写成state[i] == 1了！！
			ans[x] = i;
			dfs(x + 1);
			state[i] = 0;
			ans[x] = 0;
		}
	}
}
int main()
{
	cin >> n;
	dfs(1);
	return 0;
}


















//1-n个数，选3个出来，找出全部可能（像是上上题的简单版，没有记录数的状态，单纯选出三个数）//呵呵，还是记录了数的状态的，不然会重复数
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
#define LL long long
const int N = 10010;
int n;
int arr[4];//保证for循环按你的习惯不会出现越界，要开成n+1
int state[N];
void dfs(int x)
{
	if (x > 3)
	{
		for (int i = 1; i <= 3; i++)
		{
			cout << setw(3) << arr[i];
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= n; i++)
	{
		if (state[i] != 1)
		{
			state[i] = 1;
			arr[x] = i;
			dfs(x + 1);
			arr[x] = 0;
			state[i] = 0;
		}

	}
	return;
}
int main()
{
	cin >> n;
	dfs(1);
	return 0;
}







//p1036（试除法判断质数）
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, k, ans = 0;
int su[25];
int arr[25];

// 试除法判断质数，适用于 x 不是特别大（比如 < 1e7）
bool is_prime(int x) {
	if (x < 2) return false;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) return false;
	}
	return true;
}

void dfs(int x, int start) {
	if (x > k) {
		int sum = 0;  // 局部变量，每次自动初始化
		for (int i = 0; i < k; i++) {
			sum += arr[i];
		}
		if (is_prime(sum)) ans++;
		return;
	}
	for (int i = start; i <= n; i++) {
		arr[x - 1] = su[i];  // 存到 0~k-1 位置
		dfs(x + 1, i + 1);
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> su[i];
	}
	dfs(1, 1);
	cout << ans;
	return 0;
}
















//p1036 筛选法判断质数
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;
int n;
#define LL long long
const int N = 10010;
int ans = 0;
vector<int>pri;
int del[50000 * N] = { false };
int su[25];
int sum, k;
int arr[25];
int state[25];
void dfs(int x, int start)//！！！为了保证不会出现重复组合，加上start//额，还得把state记忆标记去掉，它对应的是全排列的逻辑，直接覆盖好像才不会出现重复组合
{
	if (x > k)
	{
		for (int i = 0; i < k; i++)
		{
			sum += arr[i];
		}
		if (del[sum] == false)
		{
			ans++;
		}
		sum = 0;
		return;
	}
	for (int i = start; i <= n; i++)
	{
		arr[x - 1] = su[i];
		dfs(x + 1, i + 1);
	}
	return;
}
int main()
{
	for (int i = 2; i <= N; i++)//这种筛选法一般从2开始
	{
		if (del[i] == false)
		{
			pri.push_back(i);
		}
		for (int j = 0; j < pri.size() && i * pri[j] <= N; j++)
			//for (int j = 0;i*pri[j]<=N && j < pri.size();j++)这么写会有越界风险
			//for (const auto& x : pri)的写法中x是值！//注意<=还是<
		{
			del[i * pri[j]] = true;
			if (i % pri[j] == 0)
			{
				break;
			}
		}
	}
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> su[i];
	}
	dfs(1, 1);
	cout << ans;
	return 0;
}