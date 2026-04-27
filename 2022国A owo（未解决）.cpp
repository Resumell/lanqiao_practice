//贪心算法：先把有价值的资源用了，防止后面资源贬值砸手里了 
#define _CRT_SECURE_NO_WARNINGS 1					//要在顶部加这个（include之前）
#include <cstdio>
#include <iostream>


using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

int cnt[9], t[9], ans;

/*
0: o-o
1: o-ow
2: o-ww

3: wo-o
4: wo-ow
5: wo-ww

6: ww-o
7: ww-ow
8: ww-ww 不用管

w: w
*/

inline				//内联函数，直接跳过跳转开销
int merge()
{
	int k = 0, res = 0;
	for (int i = 0; i < 9; i++) t[i] = cnt[i];

	// o-o, wo-ow

	if (t[0] || t[4]) res += t[1] + t[3], t[1] = t[3] = 0;

	// o-ow, wo-o

	if (t[1] && (t[2] || t[7])) res += t[1], t[1] = 0;
	if (t[3] && (t[5] || t[6])) res += t[3], t[3] = 0;

	// 2:o-ww, 5:wo-ww

	if (t[0] && t[5]) k = min(t[0], t[4]), res += k << 1, t[0] -= k, t[4] -= k;
	k = min(t[0], t[5]), res += k, t[0] -= k, t[5] -= k, t[2] += k;

	if (t[2] && t[4]) k = min(t[0], t[4]), res += k << 1, t[0] -= k, t[4] -= k;
	k = min(t[2], t[4]), res += k, t[2] -= k, t[4] -= k, t[5] += k;

	k = min(t[0], t[5]), res += k, t[0] -= k, t[5] -= k, t[2] += k;

	// 6:ww-o, 7:ww-ow

	if (t[0] && t[7]) k = min(t[0], t[4]), res += k << 1, t[0] -= k, t[4] -= k;
	k = min(t[0], t[7]), res += k, t[0] -= k, t[7] -= k, t[6] += k;

	if (t[4] && t[6]) k = min(t[0], t[4]), res += k << 1, t[0] -= k, t[4] -= k;
	k = min(t[4], t[6]), res += k, t[4] -= k, t[6] -= k, t[7] += k;

	k = min(t[0], t[7]), res += k, t[0] -= k, t[7] -= k, t[6] += k;

	// 2:o-ww, 5:wo-ww, 6:ww-o, 7:ww-ow

	k = min(t[2], t[7]), res += k, t[2] -= k, t[7] -= k;
	k = min(t[5], t[6]), res += k, t[5] -= k, t[6] -= k;

	// o-ow, wo-o

	if (t[1]) res += t[1] - 1, t[1] = 1;
	if (t[3]) res += t[3] - 1, t[3] = 1;

	// o-o, wo-ow

	k = min(t[0], t[4]);
	if (k && t[0] == t[4]) res--, t[1] < t[3] ? t[1]++ : t[3]++;

	// o-o + wo-ow : wo-ow + o-o

	t[0] -= k, t[4] -= k, res += k << 1;

	// ?-o + w + o-?, o-o + w + o-o + ... 

	int pre = t[3] + t[6], suf = t[1] + t[2];

	k = min({ pre, suf, t[8] }), pre -= k, suf -= k, t[8] -= k, res += k;
	if (!(k | pre | suf)) t[0] = max(t[0] - 1, 0);						// 需要一个 ?-o 或 o-? 
	return res + min(t[0], t[8]);
}

int n, m; char s[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s), m = strlen(s);									//strlen就是数一下s有几个字符
		for (int i = 0; i <= m - 3; i++)
		{
			if (s[i] == 'o' && s[i + 1] == 'w' && s[i + 2] == 'o')
				ans++;
		}
		//找组合的时候注意有效段的联合拼接，比如owo为有效段，那么o-o和o-wo就是等效的
		// w
		if (m == 1 && *s == 'w') cnt[8]++;								//cnt表示对应物品栏++
		// o-?
		else if (*s == 'o' && s[m - 1] == 'o') cnt[0]++;
		else if (*s == 'o' && s[m - 2] == 'o' && s[m - 1] == 'w') cnt[1]++;			//*s就是s[0]
		else if (*s == 'o' && s[m - 2] == 'w' && s[m - 1] == 'w') cnt[2]++;
		// wo-?
		else if (*s == 'w' && s[1] == 'o' && s[m - 1] == 'o') cnt[3]++;
		else if (*s == 'w' && s[1] == 'o' && s[m - 2] == 'o' && s[m - 1] == 'w') cnt[4]++;
		else if (*s == 'w' && s[1] == 'o' && s[m - 2] == 'w' && s[m - 1] == 'w') cnt[5]++;
		// ww-?
		else if (*s == 'w' && s[1] == 'w' && s[m - 1] == 'o') cnt[6]++;
		else if (*s == 'w' && s[1] == 'w' && s[m - 2] == 'o' && s[m - 1] == 'w') cnt[7]++;

		printf("%d\n", ans + merge());
	}
}