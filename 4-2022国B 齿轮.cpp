//		思路1（错：根本没变复杂度）：
//		这题的并非用的是排列，枚举所有齿轮的全排列来找合法首尾——那确实是 O(n!) ，但n最大到 2×10**5，这个量级下 n!比宇宙原子数还多，绝对跑不动。
//	所以不能遍历所有的情况于除再对比答案，可以先输入所有齿轮情况，然后从第一个情况开始，看什么情况能乘出答案，如果没有对应齿轮就直接下一个齿轮再找。
//  注意：如果要找倍数是1的这种情况，需要特殊处理条件：要两个一样的齿轮尺寸

//	总结：查找对应元素是否存在,或集成两个共生条件达成最终目标,数理题可以把除改为乘!但本思路没有改变任何复杂度

//		思路2（对）：把qi看作答案，而不是中间式子的一部分，把所有存在的半径都当一遍"第一个齿轮"，把所有可能的倍数都扫一遍，所有能产生的 q 记录在案。

					//for (int r = 1; r <= MAXR; r++)
					//{
					//	if (!sta[r]) continue;   没有这个半径，直接跳过
					//
					//	// 枚举 r 的所有倍数：r, 2r, 3r, 4r... 一直到不超过 200000
					//	for (int multi = r; multi <= MAXR; multi += r)
					//	{
					//		if (sta[multi])  // 如果 multi 这个半径也存在
					//		{
					//			int q = multi / r;  // 比值
					//
					//			// 特殊情况：q = 1 意味着首尾半径相等，需要至少两个该半径的齿轮
					//			if (q == 1 && number[r] < 2) continue;
					//
					//			possible[q] = true;  // 标记这个 q 可行
					//		}
					//	}
					//}

//错误 1：越界+复杂度没变（思路1）
//		 int qj = i * qi;//半径个数和半径（i）不要搞错了！
//	 	 if (sta[qj]) 

//错误 2：为什么质数筛的 sqrt 在这里不能用？
//		 原理是：如果 n 有一个大于 sqrt(n) 的因子 a，那它一定还有一个小于 sqrt(n) 的对应因子 b = n / a。 所以只需检查到 sqrt(n) 就能覆盖所有因子对。

//扩1：	int x = sqrt(200010);  消除浮点转int误差
//		while (x * x < 20010) x--;
//		while ((x + 1) * (x + 1) >= 20010) x++;

//错误 3：错误的以为要清空数据

//错误 4：用了ios:sync_with_stdio(false);cin.tie(0);还用printf
#include<iostream>
#include<cstdio>
#include<algorithm>
bool sta[200010] = { 0 };
int number[200010] = { 0 };
bool qstate[200010] = { 0 };
int n, Q, ri, qi;
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::cin >> n >> Q;
	while (n--)
	{
		std::cin >> ri;
		sta[ri] = true;
		number[ri] += 1;
	}

	for (int i = 0; i < 200010; i++)
	{
		if (sta[i])
		{
			for (int now = i; now < 200010; now += i)
			{
				if (sta[now])
				{
					int q = now / i;
					if (q == 1 && number[i] < 2)continue;//注意
					qstate[q] = 1;
				}
			}
		}
	}
	while (Q--)
	{
		std::cin >> qi;
		if (qstate[qi] == 1)
		{
			std::cout << "YES";
			std::cout << std::endl;
		}
		else
		{
			std::cout << "NO";
			std::cout << std::endl;
		}
	}


	//std::fill(sta,sta + sizeof(sta) / sizeof(sta[0]), 0);		错误3
	//std::fill(number, number + sizeof(number) / sizeof(number[0]), 0);

	return 0;
}