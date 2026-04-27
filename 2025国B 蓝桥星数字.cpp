//算法应用于：
// 运用于输入一个值，从而通过特殊处理方式输出一个对应值，适合没有循环体的函数


#include <iostream>//                                       提供cout等标准输入输出功能
#include <cstdio>//                                         stdio的进阶版，提供getchar()函数
using namespace std;                                      //直接给cout等函数直接设置一个标签（标准）
#define LL long long
#define ULL unsigned long long
LL n, tmp, len, flag;
LL read()
{
    LL su = 0, pp = 1; char ch = getchar();               //不用cin：同步缓冲区+锁+类型解析，getchar是缓冲区直接读取
    while (ch < '0' || ch>'9')
    {
        if (ch == '-')
            pp = -1; 
        ch = getchar(); 
    }
    while (ch >= '0' && ch <= '9') 
    { 
        su = su * 10 + ch - '0'; ch = getchar();        //getchar返回的是一个int，所以ch是ASCLL码值，可以被计算
    }                                                   
    return su * pp; 
}
int main() {
    n = read();                                         //输入N
    tmp = 45, len = 2;
    while (n > tmp)
        n -= tmp, len++, tmp *= 5;                     //这样写比较紧凑了解一下就行
    tmp /= 9;                                          //找基数，最高位每个数字对应有多少个
    n--;                                               //要算正确阶层，且防止计算机向下取整导致的最高位实际值变大
    flag = (n / tmp + 1) % 2;                          //记录最高位奇偶性，1奇0偶
    cout << n / tmp + 1;                               //算最高位是几并输出
    n %= tmp;                                          //注意是余数用作后续处理
    for (int i = 1; i < len; i++) 
    {
        tmp /= 5;
        cout << (n / tmp) * 2 + 1 - flag;              //*2是因为一奇一偶为一组，跳过的走然后奇偶性取定值
        flag = 1 - flag;                               //改变奇偶性
        n %= tmp;                                      //下一个数（行）的"本钱"
    }
    cout << "\n";
    return 0;  
}

//没有用到的：
//#include <string>//代码中未实际使用                       属于预留头文件
//#include <vector>//代码中未实际使用                       属于预留头文件
// //#define UInt unsigned int  //无符号整形，实际没有使用
//#define LD long double//双精度浮点型
////#define pii pair<int,int>                                 存坐标/键值对
////#define pLL pair<LL,LL> 
////#define pDD pair<LD,LD>
//#define fr first  //pair的
//#define se second
//#define pb push_back
//#define isr insert//笔误加没使用  

//1.时间复杂度是当数据量变大时，代码运行时间增长的趋势
//  空间复杂度是代码运行时需要的额外存储空间随数据量增长的趋势

//2.通过简单计算可以找出具体题目（1e12）对应的函数关系最小可包含（1e12）的位数

//3.一字节时8bit，bit采用二进制的方式存内存，所以一字节可以存2**8 = 256个不同状态数
//  char 1
//  short 2
//  int 4
//  long long 8

//4.负号记录提取数字方法getchar
//  LL su = 0, pp = 1; char ch = getchar(); while循环;

//5.伪计算实际是拼接
//  su = su * 10 + ch - '0'; ch = getchar();

//6.防止计算机向下取整导致的最高位实际值变小操作
//  n--;和cout << n / tmp + 1; 

//7.两个斜杠的整除是python，C语言只有一个斜杠，区分的是int和double类型

//8.分组思路+奇偶数取定值（条件取分组中值）
//  flag = (n / tmp + 1) % 2;                      //初始化奇偶性
//  cout << (n / tmp) * 2 + 1 - flag;              //*2是因为一奇一偶为一组，跳过的走然后奇偶性取定值
//  flag = 1 - flag;                               //改变奇偶性

//9.记录状态的解体框架：while和for循环加上变量


//10.自己写，解决不足不会和反思版
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long						//命名在前面，类型在后面
LL N, zuidazfhan, len, flag;						//用lg N结构：输入N,10个数对比行内数,位置锚点，额外输出规则
LL read()
{
	//读取三要素：返回值，符号值，临时值（都是局部变量）
	long long su = 0;
	long long fu = 1;						//fu开始用1
	char  ch = getchar();					//读取N用
	while (ch < '0' || ch > '9')					//排除读取的ch非数字，利用返回值是ASCLL原理，但比用''
	{
		if (ch == '-')
		{
			fu = -1;						//这个直接写-1即可，不是fu = ch;此时ch是ASCLL为45
		}
		ch = getchar();						//getchar会自动往后,但被忘记了ch赋值
	}
	while (ch >= '0' && ch <= '9')
	{
		su = su * 10 + ch - '0';			//不要忘记ch是ASCLL，要减去'0'，还有不是+=，是直接=
		ch = getchar();
	}
	return (su * fu);
}
int main()
{
	zuidazfhan = 45, len = 2;				//最大换，根据题目改，10进制是90，不要1-9
	N = read();								//函数不能主动赋值，要给N主动赋值，读取数据用函数
	while (N > zuidazfhan)
	{
		N -= zuidazfhan;
		zuidazfhan *= 5;						//这里是要*=，细节不要错了，不然大数据做不了
		len++;
	}
	N--;									//不要忘记了要加N--
	zuidazfhan /= 9;
	flag = (N / zuidazfhan + 1) % 2;			//不要把第一个和整体奇偶性搞错了
	cout << N / zuidazfhan + 1;
	N = N % zuidazfhan;
	for (int i = 1; i < len; i++)		    //i=1才是运行len-1次，用while也可以，但是用for更省事
	{
		zuidazfhan /= 5;					//是/=不是/，/只有一次计算，但实际没改
		cout << (N / zuidazfhan) * 2 + 1 - flag;
		flag = 1 - flag;
		N = N % zuidazfhan;
	}
	return 0;
}



