//1.知识点1：
//greater<int> 的判定逻辑：
//接收两个数 a 和 b，如果 a > b，返回 true。
//但在 priority_queue 的语境里，true 的意思不是 "a 更大"，而是 "a 的优先级更低，应该往下沉"。

//2.知识点2：typedef把pd从变量改成类型：typedef pair<int, int>pd;

//3.思路1：建图，把起点和边权加在一起
	//vector<vector<pii>> g(n + 1);  // g[u] 存从u出发的所有边
	//for (int i = 0; i < m; i++) {
	//    int u, v, w;
	//    cin >> u >> v >> w;
	//    // 双向边，但两个方向的"总时间"不一样
	//    g[u].push_back({ v, w + c[u] });  // 从u出发：路上w + 离开u的隔离c[u]
	//    g[v].push_back({ u, w + c[v] });  // 从v出发：路上w + 离开v的隔离c[v]
	//}

//4.错误1：map[u].push_back((v, c + wait_time[u]));vector加入pair类型数据，要用{}:map[u].push_back({v, c + wait_time[u]})

//5.知识点3： priority_queue<pii, vector<pii>, greater<pii>> pq;的创建：元素类型，底层容器，比较器；	它的创建是为了记录需要处理的最近的点！！
//           pq.push({ 0, 1 });堆的初始化
//		  	 auto [d, u] = pq.top();   // 取出堆里面的元素，注意不是front，是top
//			 pq.pop();

//			pd na = dui.top();	// 取出堆里面的元素，版本太低用这个
		//  int u = na.first;
		//  int d = na.second;
		//  dui.pop();

//6.错误2：用priority_queue来做最小路的查找的时候，pair应该把距离放在第一位
	//    Dijkstra 的遍历顺序。它不是"从1号走到N号"，而是"哪个离起点近就先处理哪个"
	//	  你那个 if (d != dist[u]) continue; 只是事后擦屁股。错误版虽然靠它勉强没算错答案，但堆已经炸了——10 万节点的图能让你堆到几百万条过期记录，直接超时。

//7.思路2：找路和更新
//		if (d != dist[u]) continue;
//		for (auto [v, w] : g[u])
	//	{
	//    if (dist[u] + w < dist[v]) {  // 发现更短路
	//    	  dist[v] = dist[u] + w;    // 更新最短时间
	//  	  pq.push({ dist[v], v });  // 把v塞进堆，等待后续处理。PS：不管他是不是最佳路线上的点都先推进堆里，如果不是会先删：pop后跳：if (d != dist[u]) continue;
	//    }
	//  }

//8.错误3：堆使用push加入新的元素，而不是push_back


//9.错误4：vector<int>dist(1010, 0x3f3f3f3f);应该在开始的时候给数组赋值，不然没法在下面做到替换

//10.错误5：dui.push({ nu,nd });推入应该是dui.push({ nu,dist[nu] });

//11.错误6：wait_time 下标错位（你是从0开始，和下面的城市索引有问题，和题目从1开始也有问题）

//12.错误7：map什么时候会自动增大？
  //	   只有 map.push_back(...) 这种写法，vector 才会自动扩容。但你用的是 map[u]，这是"给我拿第 u 个抽屉"，抽屉不存在就崩。
		// 写法一：push_back —— 合法，会自动扩容
	    //		  map.push_back({ {2, 100} });  
		// 写法二：直接 [u] —— 非法，不会自动扩容
		//		  map[1].push_back({ 2, 100 });

//13.错误8：vector<vector<pd>>map(N + 10);在N输入之前开辟map空间

#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#define LL long long
using namespace std;
LL N, M;
typedef pair<int, int>pd;//距离，城市
vector<int>wait_time(1010);
int main()
{
	cin >> N >> M;
	vector<vector<pd>>map(N + 10);
	for (int i = 1; i <= N; i++)
	{
		cin >> wait_time[i];
	}
	for (int i = 1; i <= M; i++)
	{
		int u, v, c;
		cin >> u >> v >> c;
		map[u].push_back({ c + wait_time[u] , v });
		map[v].push_back({ c + wait_time[v] , u });
	}
	priority_queue<pd, vector<pd>, greater<pd>>dui;
	vector<int>dist(1010, 0x3f3f3f3f);
	dui.push({ 0, 1 });
	dist[1] = 0;
	while (!dui.empty())
	{
		pd na = dui.top();
		int d = na.first;
		int u = na.second;
		dui.pop();

		if (d != dist[u]) continue;//如果不是目前最优记录，就continue
		for (const auto& mna : map[u])
		{
			int nd = mna.first;
			int nu = mna.second;
			if (dist[u] + nd < dist[nu])
			{
				dist[nu] = dist[u] + nd;
				dui.push({ dist[nu],nu });
			}
		}
	}
	cout << dist[N] - wait_time[1] << endl;
	return 0;
}