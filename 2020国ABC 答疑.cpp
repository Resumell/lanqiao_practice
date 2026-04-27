//一代自己写的版本，无结构体（错误）
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
int s[1010];
int a[1010];//开数组大小看的是人数N;
int e[1010];
int whole[1010];
int ans[1010];
int sum[1010];
int main()
{
	int n, answer = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &s[i]);
		scanf("%d", &a[i]);
		scanf("%d", &e[i]);
		whole[i] = s[i] + a[i] + e[i];
	}
	whole[0] = a[0] = s[0] = e[0] = 0;
	sort(&whole[1], &whole[n + 1]);
	//1.sort要么要指针，要么要取地址，不能直接给数组（sort(whole[1], whole[n]);）注意左闭右开
	//2.关于sort第三个参数可以这么写：
	// bool cmp(Node x, Node y)
	// {
	//return (x.s + x.a + x.e) > (y.s + y.a + y.e);
	// }
	//sort(&whole[1], &whole[n+1],cmp);
	//3.注意排了什么！只是排了whole是没绑定a，s，e的！他们没排！这些情况用结构体打包在一起！！！
	  //下面有例子
	sum[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1] + whole[i];
	}
	for (int i = 1; i <= n; i++)
	{
		ans[i] = sum[i - 1] + a[i] + s[i];
	}
	for (int i = 1; i <= n; i++)
	{
		answer += ans[i];
	}
	printf("%d", answer);
	return 0;
}






//二代自己写的版本，有结构体(错误版本)
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
struct node {
	int s[1010];
	int a[1010];
	int e[1010];
	int whole[1010];
}p[1010];//这样实际开了1010 * 1010个空间！！是错的！
int ans[1010];
int sum[1010];
int main()
{
	int n, answer = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &p->s[i]);//注意结构体写法，这个实际一直在往p[0]输入数据，其他的根本没有用到！
		scanf("%d", &p->a[i]);//这样写实际上：p->s[i] 等价于 (*p).s[i] 等价于 p[0].s[i]
		scanf("%d", &p->e[i]);
		p->whole[i] = p->s[i] + p->a[i] + p->e[i];
	}
	p->whole[0] = p->a[0] = p->s[0] = p->e[0] = 0;
	sort(&p->whole[1], &p->whole[n + 1]);
	sum[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1] + p->whole[i];
	}
	for (int i = 1; i <= n; i++)
	{
		ans[i] = sum[i - 1] + p->a[i] + p->s[i];
	}
	for (int i = 1; i <= n; i++)
	{
		answer += ans[i];
	}
	printf("%d", answer);
	return 0;
}






//三代自己写的版本，有结构体
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
#define LL long long //数据太多了，会炸掉
using namespace std;
struct node {
	LL s;
	LL a;
	LL e;
	LL whole;
}p[1010];
LL ans[1010];
LL sum[1010];
int main()
{
	LL n, answer = 0;
	scanf("%d", &n);
	for (LL i = 1; i <= n; i++)
	{
		scanf("%lld", &p[i].s);//注意结构体写法
		scanf("%lld", &p[i].a);
		scanf("%lld", &p[i].e);
		p[i].whole = p[i].s + p[i].a + p[i].e;
	}
	p[0].whole = p[0].a = p[0].s = p[0].e = 0;
	//sort(&p[1].whole, &p[1+n].whole);这么写是错的！还是调动不了整体的移动，只能动whole这一个元素
	//用函数定义，或者Lambda现场做一个
	sort(&p[1], &p[n + 1], [](node x, node y) {
		return x.whole < y.whole;//这里可以只写一个<的判断，是因为sort会无限对比所有数！
		});
	sum[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1] + p[i].whole;
	}
	for (int i = 1; i <= n; i++)
	{
		ans[i] = sum[i - 1] + p[i].a + p[i].s;
	}
	for (int i = 1; i <= n; i++)
	{
		answer += ans[i];
	}
	printf("%lld", answer);
	return 0;
}

//加：bool 函数名(int x，int y)这种只返回1和0