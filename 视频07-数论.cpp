#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include<math.h>
#define LL long long
using namespace std;

//找质数
//1.0,偏暴力
const int N = 1e5 + 10;
bool del[N];//定义当前位置是否是质数状态
int main()
{
	memset(del, 0, sizeof del);
	del[0] = del[1] = true;
	for (int i = 1; i <= 100; i++) {
		if (!del[i]) {
			cout << i << " ";//不是输出del[i]
			for (int j = i; j <= 100; j += i) {		//注意：找出了i的每个倍数的树，但是有重合的，所有有下面解法
				del[j] = true;
			}
		}
	}
	return 0;
}

//找质数
//2.0，vector记忆化数组空间
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include<math.h>
#include<vector>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
bool del[N];//定义当前位置是否是质数状态
vector<int>pri;	//质数数组
int main()
{
	memset(del, 0, sizeof del);
	del[0] = del[1] = true;
	for (int i = 1; i <= 1e5 + 10; i++)
	{
		if (!del[i])
		{
			pri.push_back(i);
		}
		for (int j = 0; j < pri.size() && i * pri[j] <= N; j++)
		{  //这里vector的size属性可以记一下
			del[i * pri[j]] = true;
			if (i % pri[j] == 0)
				break;	//这里很巧妙，反了你的直觉，这里偶数都只把之后自己的二倍解决就停，其他一样，然后刚刚好覆盖全部合数
		}
	}
	for (const auto& x : pri)
	{
		cout << x << " ";
	}
	return 0;
}













//货物摆放
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include<math.h>
#include<vector>
#define LL long long
using namespace std;

LL N = 2021041820210418;//const int N = 2021041820210418;  错误，int？
//bool del[N];错误，会占很多内存
vector<LL>factor;	//因数总和
int main()
{
	//找出所有因数：
	for (LL i = 1; i < N / i; i++)
	{
		if (N % i == 0)
		{
			factor.push_back(i);
			factor.push_back(N / i);
		}
	}
	//枚举所有因数：
	int ans = 0;
	for (LL i = 0; i < factor.size(); i++)//不是for(LL i = 0;i < factor.size;i++)那是调变量的，不是调函数的
		for (LL j = 0; j < factor.size(); j++)
			for (LL k = 0; k < factor.size(); k++)
			{
				if (factor[i] * factor[j] * factor[k] == N)
				{
					ans++;
				}
			}
	return 0;
}










//排列距离
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include<math.h>
#include<vector>
#define LL long long
using namespace std;
LL factoral[30];
LL weishu(string str)
//int factoral[30];这个是错误的，int类型要改LL，不然溢出直接是负数
//int weishu(string str)
{
	LL ans = 0;
	for (LL i = 0; i < str.length(); i++)//string类型的size()
	{
		LL ans1 = 0;
		for (LL j = i + 1; j < str.length(); j++)//str.length的提供值和j的下标索引是互相独立的
		{
			if (str[i] > str[j])
			{
				ans1++;
			}
		}
		ans += ans1 * factoral[str.length() - i - 1];//这个不是第i位，是反着来的
	}
	return ans;
}
int main()
{
	LL ans = 0;
	string str1 = "ncfjboqiealhkrpgd", str2 = "aejcldbhpiogfqnkr";
	//string ncfjboqiealhkrgpgd, aejcldbhpiogfqnkr;666,你这么写是说他们名字叫这个
	factoral[0] = factoral[1] = 1;
	for (LL i = 2; i <= 17; i++)
	{
		factoral[i] = factoral[i - 1] * i;
	}
	ans = abs(weishu(str1) - weishu(str2));//abs是取绝对值的意思
	cout << min(ans, factoral[17] - ans);//要给具体的数字
	return 0;
}