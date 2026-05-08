//1.思路1：
//把“一个一个填进最小组去看能出几套”的思路变为“我要x套，能不能达到？”
//为什么不用找"最小组"
//因为你不是真的在"补牌"，你是在批量验货。就像老板不问"这张牌写几、那张牌写几"，而是直接问："给我 x 套，仓库里现存的加上能手写的，够不够？"
//每种牌独立算账，加起来一比对，完事。O(n) 验一次。


//2.知识点：
//true一旦成立就是在最前面的哪个变量放到前面去
//大的在前（降序）	return a > b;	9, 5, 2, 1
//小的在前（升序）	return a < b;   1, 2, 5, 9

//3.错误1：if (Mid(int l,int r))这样是错的，不能再if语句里面定义变量，只能直接给变量
//		  if (Mid(l,r))

//4.思路2：Judge条件判断

//5.思路3：二分法的停止条件：两个特殊状态：一个是l = r的情况，一个是l和r只差1
//		争对1：while(l < r)代表你不用防l = r的情况
//		针对2：l和r只差1
	//		  while (l < r)
	//		{
	//			mid = (l + r) / 2;			//这里改成mid = (l + r + 1) >> 1 ,可以防止l 比 r 只小1的情况
	//			if (Judge(l, r, mid))
	//			{
	//				l = mid;
	//			}
	//			else
	//			{
	//				r = mid - 1;
	//			}
	//		 }

//6.知识点：mid = (l + r + 1) >> 1;其中>>1的效果是/2

//7.错误2：答案输出不是输出mid，是输出l，是把边界当答案判定线的！

//8.知识点：如果遇见逻辑没有问题，但是答案还是报错的情况下，可能是数据类型不符合条件

#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N = 200010;
LL ninumber[N];
LL binumber[N];
LL m;
LL n, l = 0, r = 400000, mid;
bool Judge(LL l, LL r, LL mid)
{
	LL need = 0;
	for (LL i = 0; i < n; i++)
	{
		if (ninumber[i] >= mid)continue;
		else if (ninumber[i] < mid && ninumber[i] + binumber[i] >= mid)
		{
			need += (mid - ninumber[i]); continue;
		}
		else if (ninumber[i] < mid && ninumber[i] + binumber[i] < mid)
		{
			return false;
		}
	}
	if (need <= m)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> ninumber[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> binumber[i];
	}
	while (l < r)
	{
		mid = (l + r + 1) >> 1;
		if (Judge(l, r, mid))
		{
			l = mid;
		}
		else
		{
			r = mid - 1;
		}
	}
	cout << l;//错误2，不能输出mid，是把边界当答案判定线的！
	return 0;
}