//总结你踩的坑（下次别踩）：
//变量遮蔽：循环里写 int a = ... 会造新变量，盖住外面的 a
//忘记输出：算完 ans 没 printf，程序直接退出
//scanf 格式： % d\n 里的 \n 会等换行，评测机直接卡死。后面是文件才会停，空白会一直读
//位数≠索引：i 是长度（3），不是位置（索引 3 是第 4 个数）

//总共 9 位，a 用了前 i 位，还剩 9 - i 位
//c 占最后 k 位，所以 c 从索引 9 - k 开始，到 8 结束
//b 占中间，从 i 开始，到 9 - k - 1（即 < 9 - k）结束
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
int main() {
    int n, a, b, c, ans = 0;
    cin >> n;
    int p[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    do {
        for (int i = 1; i <= 7; i++) {          // a 占 i 位
            a = 0;
            for (int j = 0; j < i; j++) a = a * 10 + p[j];
            if (a >= n) continue;               // a 必须 < N，否则 b/c 为负
            for (int k = 1; k <= 8 - i; k++) {  // c 占 k 位，保证 b 至少 1 位
                b = c = 0;
                for (int j = i; j < 9 - k; j++) b = b * 10 + p[j];  // 中间是 b
                for (int j = 9 - k; j < 9; j++) c = c * 10 + p[j];  // 末尾是 c
                if (a * c + b == n * c) ans++;  // 等价于 a + b/c == n，无浮点误差
            }
        }
    } while (next_permutation(p, p + 9));
    cout << ans;
    return 0;
}



//自己写的：
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;
int main()
{
	int n = 0;
	int ans = 0;
	scanf("%d\n", &n);
	int N[9] = { 1,2,3,4,5,6,7,8,9 };
	do {
		for (int i = 1; i <= 7; i++)//i只表示对应位数，不表示索引
		{
			int a = 0;
			for (int j = 0; j < i; j++)
			{
				a = a * 10 + N[j];	//注意这里是用j，不是用i，还是那句ik是ac的位数，不是索引值 
				//不要重新定义！！int a = a * 10 + N[j];写成 a = a * 10 + N[j];
			}
			if (a >= n) { continue; }//细节
			//计算分数的时候，可以不用double，你可以改式子，两边同时乘以对应除数即可
			for (int k = 1; k <= 8 - i; k++)//k也只表示对应位数，三个变量，需要两个标识，且标识要主动分区（分开b，c）
			{
				int b = 0, c = 0;
				for (int j = i; j < 9 - k; j++)  b = b * 10 + N[j];
				for (int j = 9 - k; j < 9; j++)  c = c * 10 + N[j];
				if (a * c + b == n * c)
				{
					ans++;
				}
			}
		}
	} while (next_permutation(N, N + 9));
	printf("%d\n", ans);
	return 0;
}