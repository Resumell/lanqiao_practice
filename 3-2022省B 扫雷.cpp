#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
LL dxi[50010], dyi[50010], hxi[50010], hyi[50010], n, m, dri[50010], hri[50010];
int ans = 0;
int main()
{
	std::cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		std::cin >> dxi[i];
		std::cin >> dyi[i];
		std::cin >> dri[i];
	}
	for (int i = 0; i < m; i++)
	{
		std::cin >> hxi[i];
		std::cin >> hyi[i];
		std::cin >> hri[i];
	}
	return 0;
}



//不熟悉，要记忆的：

//1.
//ios::sync_with_stdio(false);
//cin.tie(nullptr);

//2.grid是格子的意思

//3.unordered_map 和 vector 都住在 std 命名空间里，调用时必须加 std::

//4.unordered_map 和 map 都可以自动变大，不需要预开空间

//5.grid(encode(int d[i].xi, int d[i].yi)).push_back(i);这样是错的
//  grid[encode(d[i].xi,d[i].yi)].push_back(i);这样写是对的，但是进阶的版本有用到/W划分区块，而不是像这样一个一个来找
//  进阶：加入了W这个边界条件，gx，gy这些都是为了划分格子，这样找雷，排雷都是20，20（假设W是20）这样找

//6./是向0取整,

//7.边界W的选取是找到最小影响1个区块，最大影响2**n个区块的边界线的值，n是对应维度

//8.遍历寻找地雷的时候：
// 
// for(int i = gxR; i <= gxL;i++)
//  for (int j = gyB; j <= gyT; i++)
//  {
//      if (grid[encode(i, j)] != grid.end);    不能这么写！grid[encode(i, j)]返回的是一个vector<int>，而grid.end是一个指针迭代器
//                                              可以走grid[key].empty()的逻辑，但是这个远没有find快！如果对应位置没有数据，它要插入创建一个key+判断+删除
//   }
//
// 这么写：
// for (int gx = gxL; gx <= gxR; ++gx) {
//  for (int gy = gyL; gy <= gyR; ++gy) {
//       auto it = grid.find(encode(gx, gy));
//       if (it == grid.end()) continue;
//

//9.find函数返回的类型是std::unordered_map<LL, std::vector<int>>::iterator，它是一个迭代器，所以你用auto来省时省力，引用它的时
//  候，要把它看成单独unordered_map位置的LL，vector<int>复合数组！

//10.把会被波及到的地方的雷提取出来（就是it迭代器的第二部分）
//   auto& vec = it->second;一次全部提取出来
//   for (int k = (int)vec.size() - 1; k >= 0; --k) 

//11.倒着遍历一个数组 for (int k = (int)vec.size() - 1; k >= 0; --k)
//   配合后面删除用在不要求顺序的时候；注意要-1，因为下标从0开始；注意要强制转换为int类型size()返回的是size_t类型
//  if (a[id].vis) 
//   {
//   vec.erase(vec.begin() + k);     中间删除，后面元素前移
//   continue;
//   }

//12.注意unordered_map它存储的类型第二个只是记得雷的编号，不是雷本身！它管的只是“地图”哪里有雷


//13.要加vis状态，就是为了确保不会重复计算！这也是关键！
//  if (a[id].vis) 
//     {
//         vec[k] = vec.back();
//         vec.pop_back();
//         continue;
//     }

//14.

//15.

//16

//17

//18

//19

//补1
//补2

//完整AC代码
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct Mine {
    long long x, y;
    int r;
    bool vis = false;
};

struct Rocket {
    long long x, y, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Mine> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].r;
    }

    const int W = 20;

    unordered_map<long long, vector<int>> grid;
    auto encode = [&](int gx, int gy) -> long long {
        return ((long long)gx << 32) ^ (gy & 0xffffffffLL);
        };

    for (int i = 0; i < n; ++i) {
        int gx = a[i].x / W;
        int gy = a[i].y / W;
        grid[encode(gx, gy)].push_back(i);
    }

    vector<Rocket> rockets(m);
    for (int i = 0; i < m; ++i) {
        cin >> rockets[i].x >> rockets[i].y >> rockets[i].r;
    }

    queue<int> q;
    int ans = 0;

    auto explode = [&](long long x, long long y, long long r) {
        int gxL = (x - r) / W;
        int gxR = (x + r) / W;
        int gyL = (y - r) / W;
        int gyR = (y + r) / W;

        for (int gx = gxL; gx <= gxR; ++gx) {
            for (int gy = gyL; gy <= gyR; ++gy) {
                auto it = grid.find(encode(gx, gy));//补1：it的记录是为了不让下面继续用encode来算key，计算机会又算一遍哈希值
                                                    //补2：it是find函数通过encode(gx,gy)这个key找到在map上的一整个小整体！
                if (it == grid.end()) continue;

                auto& vec = it->second;
                for (int k = (int)vec.size() - 1; k >= 0; --k) {
                    int id = vec[k];//14.k是遍历下标！不是对应的雷编号！！

                    if (a[id].vis) {
                        vec[k] = vec.back();//15.把元素末尾拉过来，删除的具体步骤
                        vec.pop_back();
                        continue;
                    }

                    long long dx = a[id].x - x;
                    long long dy = a[id].y - y;
                    if (dx * dx + dy * dy <= r * r) {
                        a[id].vis = true;
                        q.push(id);     //16.把编号id的雷记录下来，以便下次运行explosion；状态都不用改变的，因为直接删掉了
                        ++ans;
                        vec[k] = vec.back();
                        vec.pop_back();
                    }
                }

                if (vec.empty()) {      //17.unordered_map的地图记录删除
                    grid.erase(it);
                }
                //if (grid[encode(i, j)].empty()) 这样写是错的，会插入新的key
                //{
                //    grid[encode(i, j)].pop_back();这样写是错的，他不是删除key，他是删除对应key中vector最后一个元素
                //}
                
                //也可以写成这样：
                //if (it->second.empty()) {
                //    grid.erase(it);
                //}

                /*if (it->second.empty())
                {
                    grid.erase(encode(i, j));这个版本可以是可以，但是会再算一次哈希值
                }*/
            }
        }
        };

    for (auto& rok : rockets) {
        explode(rok.x, rok.y, rok.r);
    }

    while (!q.empty()) {           //18.queue不为空的条件写法
        int u = q.front(); q.pop();//19.如何queue实现使用和用后删除，queue删去的是第一个元素！函数成员调用要加()
        explode(a[u].x, a[u].y, a[u].r);
    }

    cout << ans << '\n';
    return 0;
}

