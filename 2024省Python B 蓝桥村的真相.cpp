#define _CRT_SECARE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#define LL long long
int main()
{
	LL N, n, ret = 1;
	std::cin >> N;
	while (N--)
	{
		std::cin >> n;
		if (n % 3 == 0)
		{
			ret = 2 * n;				//这个地方是赋值（=），不是比较（==）
			std::cout << ret;
			std::cout << "\n";
		}
		else
		{
			ret = n;
			std::cout << ret;
			std::cout << "\n";
		}
	}
	return 0;
}


//题解的快速写照方法：
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		long long n;
		cin >> n;
		cout << (n % 3 == 0 ? 2 * n : n) << endl;
	}

	return 0;
}
