//1.万能头文件
	//#include<bits/stdc++.h>
#include <iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<string>
using namespace std;
//2.fixed（用小数）
#define _CRT_SECARE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#define LL long long
int main()
{
	double a = 123.456789;
	cin >> a;
	cout << setprecision(2) << fixed << a << endl;//setprecision(2)保留两位小数，fixed保证小数输出，endl表示换行加刷新，实际还是从左往右

//补1 avg = 1.0*jige/n提前变小数

//3.round（用于取整）
//例子：ans = round(ans * 1000) / 1000.0; 

//补2 cout << 常数 << "%" <<endl;
//补3 在开始创建变量的时候赋初值，max = 0，min = 0，sum = 0；
//补4 avg（平均数） = 1.0*sun/n

//4.排列字母（sort）,用<algorithm>
int arr[3];
int n = sizeof (arr) / sizeof(arr[0]);
sort(arr, arr + n);
//如果并不是数组，是vector
vector<int> v = { 5,3,1 };
sort(v.begin(), v.end());  // 注意是 begin/end，不是 v 和 v+n

//5.erase(7,5)删除第7个字符之后的5个

//6.reverse反转		用的库：<algorithm>
#include <algorithm>  // 在这
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main() {
    // 1. 数组版
    int a[] = { 1, 2, 3, 4, 5 };
    reverse(a, a + 5);           // 变成 5 4 3 2 1

    // 2. vector 版（刷题最常用）
    vector<int> v = { 1, 2, 3, 4, 5 };
    reverse(v.begin(), v.end()); // 变成 5 4 3 2 1

    // 3. string 版（翻转字符串，回文题常用）
    string s = "hello";
    reverse(s.begin(), s.end()); // 变成 "olleh"

    // 4. 只翻转一部分（第2个到第4个，注意左闭右开）
    vector<int> b = { 1, 2, 3, 4, 5 };
    reverse(b.begin() + 1, b.begin() + 4); // 只翻转 2,3,4 → 1 4 3 2 5
}

//7.GCD欧几里得
    //即约分数
int gcd(int a, int b) {
    if (b == 0) return a;        // 余数为0，当前a就是最大公约数
    return gcd(b, a % b);        // 问题缩小：变成算(b, 余数)
}
//到最小的时候，得到的是最大的公约数

//8.assign  "整体重新填充/指派"，相当于把容器里原来的东西全部扔掉，换成一批新的。
vector<int> v;
v.assign(3, 66);  // 把 v 变成 [66, 66, 66]
// 不管 v 之前是什么（空的、有 10 个元素的），现在都只有 3 个 66

//9.count 就是"数数"
vector<int> a = { 1, 2, 3, 2, 4, 2, 5 };
int num = count(a.begin(), a.end(), 2);  // 数 2 出现了几次

// 结果：num = 3（因为 a 里有三个 2）


//10.sprintf 就是"字符串打印机"，把各种数据（整数、浮点等）按指定格式写进字符数组（char[]）里存起来，而不是直接打印到屏幕。
char buffer[100];  // 准备一个能装 100 个字符的"口袋"
int n = 123;

// 把 "The number is 123" 写进 buffer，而不是打印到屏幕
sprintf(buffer, "The number is %d", n);

// 现在 buffer 里存着字符串，可以后续使用
printf("%s\n", buffer);  // 输出：The number is 123



//8,9,10合一
//int main() {
//    char s[5];        // 存数字的字符数组（2020是4位，加上'\0'刚好5个位置）
//    int sum = 0;      // 统计2的总出现次数
//    string str;       // 用string包装一下，方便用count函数
//
//    for (int i = 1; i <= 2020; i++) {  // 遍历1到2020每个数字
//        sprintf(s, "%d", i);          // 把数字i"写"进字符数组s
//        str.assign(s);                // 把s的内容交给string管理
//        sum += count(str.begin(), str.end(), '2');  // 数这个字符串里有几个'2'
//    }
//
//    cout << sum << endl;
//    return 0;
//}

  















return 0;
}