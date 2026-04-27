#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>  // strlen 需要这个头文件
using namespace std;

int main()
{
    // 1. 必须指定数组大小！题目说长度<1000，开1010保险
    char a[1010], b[1010];
    // 2. %s 读字符串，a本身就是地址，不需要 &
    scanf("%s", a);
    scanf("%s", b);
    // 3. 用 strlen 获取实际长度，不要用 sizeof
    int l = strlen(a);
    // 4. i要初始化为0
    for (int i = 0; i < l; i++)
    {
        if (a[i] != b[i])  // 这样访问是对的！
        {
            // 翻转操作...
            a[i] = (a[i] == 'o') ? '*' : 'o';
            a[i + 1] = (a[i + 1] == 'o') ? '*' : 'o';
        }
    }
    return 0;
}


//自己打的
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    char a[1010], b[1010];//这里打印进数组要记
    scanf("%s %s", a, b);//不用&，因为a，b直接就是地址
    int l = strlen(a);
    int ans = 0;
    //int l = sizeof(a)/sizeof(0);不要用sizeof，用strlen
    for (int i = 0; i + 1 < l; i++)
    {
        if (a[i] != b[i])
        {
            a[i] = (a[i] == 'o') ? '*' : 'o';
            a[i + 1] = (a[i + 1] == 'o') ? '*' : 'o'; //?:本身就是和if类似的运算结构，这个要记
            ans += 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}