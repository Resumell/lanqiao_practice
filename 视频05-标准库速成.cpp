#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <algorithm>
using namespace std;


//下面vector部分中的sort部分
struct Student {
	string name;
	int score;
};
// 定义规则：分数高的排前面，分数一样按名字字典序
bool cmp(Student a, Student b) {
	if (a.score != b.score) return a.score > b.score;//返回为Ture的时候，大的在后面，小的在前面
	return a.name < b.name;
}




//1.vector(动态数组)
#include <vector> //引入库
vector<int> v;//申明有个叫“v”的动态数组

int main()
{
	//1.vector核心操作

	v.push_back(10);//尾部添加



	v.pop_back();	//尾部删除，()里面不能有数，永远只删最后一个



	int n = v.size();  //元素个数
	size_t n = v.size(); //更安全的写法（匹配返回类型）
	int n = (int)v.size();// 或者强转（确定数据量不大时）



	v[0] = 5;  //像数组一样去访问，和改值，但是改值之前必须确保那个位置已经有元素！



	sort(v.begin(), v.end()); //排序（配合algorithm（一个库））
	// v.begin()：指向 vector 第一个元素的位置（迭代器）
	// v.end()：指向 vector 最后一个元素的后面那个空位置（哨兵位，不是最后一个元素！）
	sort(v.begin(), v.end(), greater<int>());
	//greater<int>() 是"大于比较器"，告诉 sort："我要大的放前面"
	//需要头文件 #include <functional>（或者万能头 bits / stdc++.h 已包含）
	vector<Student> stu;
	sort(stu.begin(), stu.end(), cmp);



	// 创建包含5个元素的vector，每个默认初始化为0
	vector<int> v(5);           // v = [0, 0, 0, 0, 0]
	// 创建5个元素，每个都初始化为100
	vector<int> v(5, 100);      // v = [100, 100, 100, 100, 100]
	// 从数组拷贝初始化（省赛偶尔用）
	int arr[] = { 1, 2, 3 };
	vector<int> v(arr, arr + 3);  // v = [1, 2, 3]，arr 开始，到 arr+3 之前结束

	//fill填数要的是指针地址，不是数组本身！！
	// 错的：fill(v, v+v.size(), 5)  
	// 对的：传 begin() 和 end()
	fill(v.begin(), v.end(), 100);        // 全填100
	fill(v.begin(), v.begin() + 3, 5);      // 前3个填5


	//ps，题外话：普通数组不能在函数调用的时候用sizeof算大小
		//void foo(int a[]) {  // 这里 a 其实已经变成 int* 指针了
		//	cout << sizeof(a) / sizeof(a[0]);  // 错的！sizeof(a) = 8（64位系统）
		//}

		//int main() {
		//	int a[10];
		//	foo(a);  // 传进去就废了，算不出10
		//}


	vector<int> v = { 1, 2, 3 };
	v.resize(5);        // 扩大到5个，新增位置补0：[1, 2, 3, 0, 0]
	v.resize(2);        // 缩小到2个，后面的直接丢掉：[1, 2]
	v.resize(5, 100);   // 扩大到5个，新增位置补100：[1, 2, 100, 100, 100]



	vector<int> v;
	v.reserve(10000);   // 先申请能装10000个的空间，避免频繁扩容，只扩容不加元素
	// 然后你可以 push_back 10000次，效率比直接push快



	vector<int> v = { 1, 3, 4 };
	v.insert(v.begin() + 1, 2);        // 在第1个位置前插入2：[1, 2, 3, 4]
	v.insert(v.begin(), 0);          // 在最前面插入0：[0, 1, 2, 3, 4]
	v.insert(v.end(), 5);            // 在最后面插入5（等价于push_back）



	vector<int> v = { 1, 2, 3, 4, 5 };
	// 删单个：删第2个元素（下标1）
	v.erase(v.begin() + 1);            // v = [1, 3, 4, 5]
	// 删区间：删第1个到第3个（左闭右开！[begin, end)）
	v.erase(v.begin(), v.begin() + 3); // 删掉0,1,2位置，v = [4, 5]



	if (v.empty()) {
		cout << "空的";
	}
	// 等价于 if(v.size() == 0)，但 empty() 更快一点点



	// 二维：创建 n 行 m 列的矩阵，初始化为0
	int n = 5, m = 4;
	vector<vector<int>> mat(n, vector<int>(m, 0));
	// 访问
	mat[0][0] = 10;         // 第0行第0列
	mat[1][3] = 5;          // 跟数组一样用
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << mat[i][j] << " ";
		}
	}



	//遍历
	vector<int> v = { 10, 20, 30 };
	//只读
	for (const auto& x : v) {		//x是自己临时取的名字
		cout << x << endl;
	}
	//读写
	for (auto& x : v) {
		cout << x * 2 << endl;
	}



	//清空
	v.clear();
	return 0;
}




//2.map / unordered_map（字典）
#include<map>
#include<unordered_map>
map<int, string> cnt;
unordered_map<int, string> ump;
int main()
{
	// 构造：
	// 比赛一般用map
	// map 版（内部是排序树，像字典按拼音排序）
	map<int, string> mp;
	mp[1000000000] = "a";  // key=10亿，value="a"
	mp[5] = "b";
	// 遍历时：先输出 5->"b"，再输出 1000000000->"a"（自动按key从小到大排）

	// unordered_map 版（内部是哈希表，像散落的珠子）
	unordered_map<int, string> ump;
	ump[1000000000] = "a";
	ump[5] = "b";
	// 遍历时：可能是先 10亿，也可能是先 5（完全无序，看哈希心情）

	//别样创建方式：
	map<int, string> mp2(mp);

	vector<pair<string, int>> v = { {"Alice", 90}, {"Bob", 80} };
	map<string, int> mp3(v.begin(), v.end());



	//insert插入
	map<int, string> mp;
	mp[10] = "a";
	mp[5] = "b";   // 插入时，因为 5 < 10，放在 10 前面
	mp[20] = "c";  // 20 > 10，放在 10 后面
	// 遍历结果（自动排序）：
	// 5->"b", 10->"a", 20->"c"
	mp.insert(make_pair(1, "a"));
	mp.insert({ 1, "a" });  // 大括号直接构造 pair，和 make_pair 效果一样,返回类型：<iterator, bool>，前面是指针类型的
	auto result = mp.insert({ 1, "a" });  // insert 返回 pair<iterator, bool>
	result.first->second;
	(*result.first).second; // 先 * 解引用，再用点号，和上面等价




	//erase删除
	mp.erase(2);  // 删掉 key=2 的那一对，（最常用）

	auto it = mp.find(1);  // it 是指向 key=1 的迭代器（指针）
	if (it != mp.end()) {   // 找到了（不是空气）
		mp.erase(it);      // 删掉 it 指向的那个
	}

	mp.erase(mp.begin(), mp.end());  // 全删，等价于 mp.clear()



	//find查找
	auto it = mp.find(1);
	if (it != mp.end()) {
		cout << it->first << " " << it->second;
	}



	//count计数，map/set里面count只能看存不存在！！不能技术
	if (mp.count(1)) {  // 返回 1（存在）或 0（不存在）
		cout << "存在";
	}
	// 你真正想做的"计数"（统计频率）
	map<string, int> cnt;
	string names[] = { "张三", "李四", "张三", "王五", "张三" };
	for (const auto& name : names) {
		cnt[name]++;  // 这里是把value（抽屉里的数）+1
	}
	// 这时候：
	cnt["张三"];//的值是 3（表示出现了3次）
	cnt.count("张三"); //的值是 1（表示"张三"这个key存在）







	return 0;
}



//3.set
#include<set>

int main()
{

	set<int> s;              // 默认升序（从小到大）

	// 插入：重复插入会被自动忽略
	s.insert(5);
	s.insert(3);
	s.insert(5);             // 这次插入无效，因为5已经有了

	// 查询在不在：count返回0或1（蓝桥杯里最常用）
	if (s.count(3)) cout << "3存在" << endl;

	// 遍历：自动是排好序的（3, 5）
	for (int x : s) cout << x << " ";

	// 删除
	s.erase(3);

	// 大小
	cout << s.size();        // 输出1



	set<int> s = { 1, 3, 5, 7, 9 };
	// lower_bound：找第一个 >= 5的元素
	auto it = s.lower_bound(5);
	cout << *it;  // 输出5（刚好等于
	// 如果找 >= 6的第一个
	it = s.lower_bound(6);
	cout << *it;  // 输出7（5不够大，下一个就是7）,另外it是迭代器，可以it++

	// upper_bound：找第一个 > 5的元素（不包括等于）
	it = s.upper_bound(5);
	cout << *it;  // 输出7




	multiset<int> ms; //（允许重复的set）
	ms.insert(90);
	ms.insert(90);
	ms.insert(80);
	cout << ms.count(90);  // 输出2（set的话永远输出0或1）
	ms.erase(90);//全部90一起删除
	multiset<int> ms = { 1, 2, 2, 2, 3 };
	// 找到第一个2的位置
	auto it = ms.find(2);  // 返回指向第一个2的迭代器
	ms.erase(it);          // 只删这一个！剩下{1, 2, 2, 3}
	// 想删第二个2？
	it = ms.find(2);  // 又找到第一个2（原来的第二个）
	ms.erase(it);     // 再删一个




	set<int> s1 = { 1, 2, 3 }, s2 = { 4, 5 };

	if (!s1.empty()) {      // 判断是否为空，比 size()==0 快
		s1.clear();			// 一键清空，变成空集
	}
	s1.swap(s2);           // 交换两个set的内容（O(1)，非常快）
	// 现在 s1={4,5}, s2={1,2,3}



	return 0;
}







//4.priority_queue(优先队列/堆)
#include <queue>
priority_queue<int> pq;//大顶堆（默认，最大的在顶）
priority_queue<int, vector<int>, greater<int>> pq;//小顶堆（最小的在顶），显现写三个就要把vector也写出来
int main()
{

	//核心操作
	priority_queue<int> pq;  // 大顶堆

	// 1. push(val) - 插入，O(log n)
	pq.push(10);
	pq.push(5);
	pq.push(20);  // 内部自动调整，20会浮到顶部
	pq.emplace(20);		// 直接构造（比push快一点点，避免拷贝，比如用在结构体的时候Node）

	// 2. top() - 看堆顶（不删除），O(1)
	cout << pq.top();  // 输出20（最大值）

	// 3. pop() - 弹出堆顶（删除最大元素），O(log n)，且要删除必须要top先提取出
	pq.pop();  // 20被删，现在顶部是10

	// 4. size() - 元素个数，O(1)
	cout << pq.size();  // 输出2

	// 5. empty() - 是否为空，O(1)
	if (!pq.empty()) cout << "还有元素";

	// ⚠️ 重点：priority_queue 没有 clear() 方法！
	// 清空方法：while(!pq.empty()) pq.pop();  或重新定义 pq = priority_queue<int>();




	//考法1：找最大的 K 个数（维护大小为K的小顶堆）
	//原理：小顶堆的top()是当前堆里最小的。如果新来的数比这个"垫底"的大，就把垫底的踢掉，让新来的进堆。
		// 维护大小为3的小顶堆（堆里存着目前找到的最大的3个）
	priority_queue<int, vector<int>, greater<int>> pq;

	int n = 100000, k = 3;
	for (int i = 0; i < n; i++) {
		int x = rand() % 100;  // 模拟输入
		if (pq.size() < k) {
			pq.push(x);  // 先填满K个位置
		}
		else if (x > pq.top()) {
			// 新来的比当前第K名还大？
			pq.pop();    // 踢掉垫底的（第K名）
			pq.push(x);  // 新强者入列
		}
	}

	// 堆里剩下的就是前K大（无序）
	while (!pq.empty()) {
		cout << pq.top() << " ";  // 输出这K个数
		pq.pop();
	}

	//考法2：找第 K 大的数（一样的套路）
	//考法3：找最小的 K 个数（维护大顶堆）




	priority_queue<int> pq;
	pq.push(10); pq.push(20);

	// 这句是什么意思？
	pq = priority_queue<int>();
	// 右边：priority_queue<int>() 是构造一个新的空优先队列
	// 左边：pq被赋值为这个新的空队列（旧的那个被系统回收销毁）



	return 0;
}







//5.queue

	/*  | 特性   | queue（队列）    | priority\_queue（优先队列）     |
		| -- -   | ------------ -   | -------------------- -          |
		| 头文件 | `<queue > `      | `<queue > `                     |
		| 访问   | `front()` 取队头 | `top()` 取堆顶                  |
		| 顺序   | 先进先出（FIFO） | 按优先级（最大 / 最小先出）     |
		| 遍历   | 不能遍历         | 不能遍历（没有迭代器）          |
		| 底层   | deque / list     | vector + 堆调整                 |*/



int main() {
	queue<int> q;

	// 1. push(val) - 队尾入队，O(1)
	q.push(10);  // 队伍：[10]
	q.push(20);  // 队伍：[10, 20]（20在队尾）
	q.push(5);   // 队伍：[10, 20, 5]

	// 2. front() - 看队头（不删除），O(1)
	cout << q.front();  // 输出10（第一个来的）

	// 3. back() - 看队尾（不删除），O(1)
	cout << q.back();   // 输出5（最后一个来的）

	// 4. pop() - 队头出队（删除），O(1)，**无返回值**
	q.pop();  // 10被删，队伍变成[20, 5]

	// 5. size()/empty() - 元素个数/是否为空，O(1)
	cout << q.size();   // 输出2
	if (!q.empty()) cout << "还有人排队";





	return 0;
}


//本质：一层一层向外扩散，像水波纹或病毒传染。
//模板（迷宫最短路）：
const int N = 1005;          // 地图最大尺寸
int dist[N][N];              // 记录"从起点走到这里用了几步"，-1表示"还没走到过"
int dx[4] = { -1, 1, 0, 0 };   // 上下左右四个方向的x变化
int dy[4] = { 0, 0, -1, 1 };   // 上下左右四个方向的y变化

int bfs(int sx, int sy, int ex, int ey, int n, int m) {
	// n,m是地图实际行列数（防止越界）
	memset(dist, -1, sizeof(dist));  // 全部初始化为-1（都没访问过）

	queue<pair<int, int>> q;  // 队列里存坐标对 (x,y)
	q.push({ sx, sy });// 起点入队
	dist[sx][sy] = 0;          // 起点距离为0（自己到自己0步）

	while (!q.empty()) {
		// 取出队头（当前要处理的点）ps:front是函数！
		int x = q.front().first;    // 当前横坐标
		int y = q.front().second;   // 当前纵坐标
		q.pop();              // 把这个点请出队列（处理完了）

		// 如果到了终点，直接返回答案
		if (x == ex && y == ey)
			return dist[x][y];

		// 尝试往四个方向走
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];  // 新位置的x
			int ny = y + dy[i];  // 新位置的y

			// 判断新位置能不能走：
			// 1. nx,ny在地图范围内（0 <= nx < n, 0 <= ny < m）
			// 2. 这个点之前没走过（dist[nx][ny] == -1，防止回头路/死循环）
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1) {
				dist[nx][ny] = dist[x][y] + 1;  // 新点的步数 = 当前点步数 + 1
				q.push({ nx,ny });      // 新坐标入队，等待后续处理
			}
		}
	}
	return -1;  // 队列空了都没找到终点，说明到不了
}
int main() {
	int n, m, sx, sy, ex, ey;

	cin >> n >> m;      // 地图大小
	cin >> sx >> sy;    // 起点
	cin >> ex >> ey;    // 终点

	int ans = bfs(sx, sy, ex, ey, n, m);
	cout << ans << endl;

	return 0;
}





#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int dx[4] = { -1,0 ,1,0 };
int dy[4] = { 0,1,0,-1 };
int sx, sy, ex, ey, n, m;
int ans;
int dp[1001][1001];//这题没有用到这个，原本打算用来记录状态
int dist[1001][1001];
int bfs(int sx, int sy, int ex, int ey, int n, int m)//是要返回值的
{
	memset(dist, -1, sizeof(dist));
	queue<pair<int, int>>dp;
	dp.push({ sx,sy }); //推入
	dist[sx][sy] = 0;	//起点不一定是[0][0],要用sx，sy
	while (!dp.empty()) //这个条件可以记一下
	{

		int x = dp.front().first;	//这里和下面都有妙用！x，y（当前）和nx，ny（下一步）要分开！逻辑还能更清晰！！
		int y = dp.front().second;
		dp.pop();
		if (x == ex && y == ey)
		{
			return dist[ex][ey];	/*cout << dist[ex][ey];是错的 */
		}
		for (int i = 0; i < 4; i++)		//可以先走再判断！！不一定要先判断再走！
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			// dfs(x+dx[i], y+dy[i], ex, ey, n, m);这个思路是错的！BFS你用调用函数肯定错！
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1)// dp[nx][ny] == false,dp[x + dx[i]][y + dy[i]] == false是错的！dp不是数组！！！
			{
				dist[nx][ny] = dist[x][y] + 1;	//这里就是上面说的妙用，分开，逻辑清晰明了
				dp.push({ nx,ny });
			}
		}
	}
	return -1;//不要忘记可能没有终点！
}
int main()
{
	cin >> sx >> sy >> ex >> ey >> n >> m;
	ans = bfs(sx, sy, ex, ey, n, m);
	cout << ans;
	return 0;
}











#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int dx[4] = { -1,0 ,1,0 };
int dy[4] = { 0,1,0,-1 };
int sx, sy, ex, ey, n, m;
int ans;
int dp[1001][1001];
int dist[1001][1001];
vector<pair<int, int>>path;//注意只要是两个数字都要加pair
pair<int, int>pre[1001][1001];//你要定义怎么来的得这么定义
int bfs(int sx, int sy, int ex, int ey, int n, int m)//是要返回值的
{
	memset(dist, -1, sizeof(dist));
	memset(pre, -1, sizeof(pre));
	queue<pair<int, int>>dp;
	dp.push({ sx,sy }); //推入
	dist[sx][sy] = 0;	//起点不一定是[0][0],要用sx，sy
	pre[sx][sy] = { -2,-2 };         // 起点特殊标记，方便倒推时知道停
	while (!dp.empty()) //这个条件可以记一下
	{

		int x = dp.front().first;	//这里和下面都有妙用！x，y（当前）和nx，ny（下一步）要分开！逻辑还能更清晰！！
		int y = dp.front().second;
		dp.pop();
		if (x == ex && y == ey)
		{
			ans = dist[ex][ey];	/*cout << dist[ex][ey];是错的 */
			break;
		}
		for (int i = 0; i < 4; i++)		//可以先走再判断！！不一定要先判断再走！
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			// dfs(x+dx[i], y+dy[i], ex, ey, n, m);这个思路是错的！BFS你用调用函数肯定错！
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1)// dp[nx][ny] == false,dp[x + dx[i]][y + dy[i]] == false是错的！dp不是数组！！！
			{
				dist[nx][ny] = dist[x][y] + 1;	//这里就是上面说的妙用，分开，逻辑清晰明了
				pre[nx][ny] = { x,y };
				dp.push({ nx,ny });
			}
		}
	}
	if (pre[ex][ey].first == -1)
	{
		return -1;//到不了终点要结束条件要写在打印路径之前
	}
	int x = ex;
	int y = ey;
	while (!(x == sx && y == sy))
	{
		path.push_back({ x,y });
		int px = pre[x][y].first;//写成这样了pre(sx).first？脑袋别晕！pre是pair类型，你可以把它看出类数组！
		int py = pre[x][y].second;
		x = px;
		y = py;
	}
	path.push_back({ sx,sy });  // 补上起点
	reverse(path.begin(), path.end());
	return ans;	//能到终点！
}
int main()
{
	cin >> sx >> sy >> ex >> ey >> n >> m;
	ans = bfs(sx, sy, ex, ey, n, m);
	cout << ans;
	for (int i = 0; i < path.size(); i++)
	{
		cout << path[i].first << path[i].second << ">>";//pair的专属打印方式
	}
	return 0;
}


























































const int N = 105;  // 注意：如果要记录路径，地图不能太大，否则内存爆炸
int map4[N][N];
int dist[N][N];
pair<int, int> pre[N][N];  // 新增：记录每个点的前驱坐标 (从哪个点走过来的)
int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

// 打印路径：从终点回溯到起点
void printPath(int ex, int ey, int sx, int sy) {
	vector<pair<int, int>> path;
	int x = ex, y = ey;

	// 从终点倒着往回追
	while (!(x == sx && y == sy)) {
		path.push_back({ x, y });
		auto p = pre[x][y];  // 取前驱
		x = p.first;		 //把前驱x填进路径
		y = p.second;		 //把前驱y填进路径
	}
	path.push_back({ sx, sy });  // 加入起点

	// 倒序输出（从起点到终点）
	reverse(path.begin(), path.end());

	cout << "路径长度：" << path.size() - 1 << "步" << endl;
	cout << "路线：";
	for (auto& p : path) {
		cout << "(" << p.first << "," << p.second << ") ";
	}
	cout << endl;
}

int bfs(int sx, int sy, int ex, int ey, int n, int m) {
	memset(dist, -1, sizeof(dist));
	queue<pair<int, int>> q;
	q.push({ sx, sy });
	dist[sx][sy] = 0;
	pre[sx][sy] = { -1, -1 };  // 起点无前驱，标记为-1

	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		int x = cur.first, y = cur.second;

		if (x == ex && y == ey) {
			printPath(ex, ey, sx, sy);  // 找到就打印路径
			return dist[x][y];
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1) {
				dist[nx][ny] = dist[x][y] + 1;
				pre[nx][ny] = { x, y };  // 记录：我是从(x,y)走到(nx,ny)的
				q.push({ nx, ny });
			}
		}
	}
	return -1;
}
int main() {
	// 输入格式：
	// 第一行：n m（地图行列）
	// 接下来n行：每行m个数字（0或1，0可走，1障碍）
	// 最后一行：sx sy ex ey（起点终点坐标）
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> map4[i][j];
	int sx, sy, ex, ey;
	cin >> sx >> sy >> ex >> ey;

	int ans = bfs(sx, sy, ex, ey, n, m);
	if (ans == -1) cout << "无法到达" << endl;
	else cout << "最短距离：" << ans << endl;

	return 0;
}




//| 函数                                               | 作用               | 蓝桥杯场景                          |
//| ------------------------------------------------ | ---------------- | ------------------------------ |
//| `__gcd(a, b)`                                    | 最大公约数（GNU C++内置） | 分数约分、周期计算                   
//| `abs(int)` / `fabs(double)` / `llabs(long long)` | 绝对值              | 坐标差值、距离计算                      |
//| `sqrt(x)`                                        | 开方（返回 double）    | 几何题，注意强转 `(int)sqrt(x)` 时的精度问题 |


//下面这一类函数都用指针
//| 函数                             | 作用              | 蓝桥杯场景                            |
//| ------------------------------ | --------------- | -------------------------------- |

//| `sort(a, a+n, greater<int>())` | 降序排序            | 贪心策略，从大到小处理                      |
// 
	// Lambda写法
	//	sort(arr, arr + 3, [](string a, string b)
	//		{
	//		return a.length() > b.length();  // 长的在前
	//		});
	
	//string a = "applePie";
	//string b = "appleJuice";
	// 比较前5个字符
	//if (a.compare(0, 5, b, 0, 5) == 0) {
	//	cout << "前5个相同，都是apple" << endl;
	//}
	//参数：起始位置, 长度, 对方字符串, 对方起始, 对方长度


//| `lower_bound(a, a+n, x)`       | 返回第一个 ≥ x 的位置指针 | 二分查找，配合有序数组                      |
//| `upper_bound(a, a+n, x)`       | 返回第一个 > x 的位置指针 | 找插入位置、统计个数                       |


//| `unique(a, a+n)`               | 去重（先 sort 再用）   | 离散化、统计不同元素个数                     |
// int a[6] = {1,1,2,2,3,3};
// unique 后：a = [1, 2, 3, 垃圾, 垃圾, 垃圾]
//                   ↑
//              返回这个地址（指向第4个位置）
//int m = unique(a, a + 6) - a;  // (第4个地址) - (第1个地址) = 3  -->  下标是3-0


//| `reverse(a, a+n)`              | 反转区间            | 回文串构造、翻转操作                       |
//| `max_element(a, a+n)`          | 返回最大值的迭代器/指针    | 找最大值下标：`max_element(a, a+n) - a` |
//| `min_element(a, a+n)`          | 返回最小值的迭代器/指针    | 同上                               |



//下面这三个都是直接冲进内存里面修改值
//| 函数                        | 作用        | 注意                                         |
//| ------------------------- | --------- | ------------------------------------------ |
//| `fill(a, a+n, val)`       | 把区间填成 val | 可以填任意值（如 `fill(a, a+n, -1)`），比 `memset` 灵活 |
//| `memset(a, 0, sizeof(a))` | 按字节填充     | 只能填 `0` 或 `-1`（0x3f 填充无穷大常用），**不能填 1**     |
//| `swap(a, b)`              | 交换两个变量    | C++11 后万能，数组元素也能换                          |





//| 容器           | 增加                     | 删除                                  | 适用场景         | 蓝桥杯频率 |
//| ------------ | ---------------------- | ----------------------------------- | ------------ | ----- |
//| **`vector`** | `push_back(x)` 尾部加     | `pop_back()` 尾部删<br>`erase(it)` 中间删 | 动态数组，随机访问    | ⭐⭐⭐⭐⭐ |
//| **普通数组**     | 直接赋值 `a[i]=x`          | **无法删除**，只能覆盖或标记                    | 固定范围，极致速度    | ⭐⭐⭐⭐  |
//| **`queue`**  | `push(x)` 队尾           | 先front 再`pop()` 队头                          | **BFS**、拓扑排序 | ⭐⭐⭐   |
//| **`stack`**  | `push(x)` 栈顶           | 先top 再`pop()` 栈顶                          | **DFS**、括号匹配 | ⭐⭐    |
//| **`set`**    | `insert(x)`            | `erase(x)` 或 `erase(it)`            | 自动去重、快速查找    | ⭐⭐    |
//| **`map`**    | `mp[key]=val`          | `erase(key)`                        | 离散化、计数、映射    | ⭐⭐    |
//		补：priority_queue	top()【不是用front】	pop()	值丢失（堆顶没了）
