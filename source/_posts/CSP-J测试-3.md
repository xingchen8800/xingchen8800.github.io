---
title: CSP-J日常测试(241005mor)
date: 2024-10-05 11:00:00

tags: 
    - C++
    - CSP入门组
---

# 一、胶水（glue）

## 题目描述：
小丁是一个调皮捣蛋的小孩，老师平时在黑板上写字需要用到粉笔，小丁有了一个捣蛋的想
法。

他准备用胶水将这些粉笔粘在一起。每支粉笔的长短不同，有一定的重量，如果将两支粉笔
粘在一起，将合并成一支新的粉笔，重量是这两支粉笔的重量之和。为了保证粉笔粘贴牢固，
粘贴两支粉笔所需要的胶水量等于与两支粉笔的重量乘积，每次合并，小丁只能合并位置相
邻的两支粉笔，并将合并出的新粉笔放在原来的位置。
现在，小丁想用最少的胶水将所有粉笔粘在一起，请帮助小丁计算最少需要多少胶水。

## 输入格式：
输入文件名：`glue.in`
第一行，一个整数 $n$ ，表示初始时的粉笔数量。
第二行包含 $n$ 个整数，$W_1,W_2 \cdots W_n$，依次表示每根粉笔的重量。

## 输出格式：
输出文件名：`glue.out`
输出一个整数，表示小丁使用的最少胶水量。

## 样例

### 样例输入 #1
```
3
3 4 5
```

### 样例输出 #1
```
47
```

### 输入样例 2：
```
8
1 5 2 6 3 7 4 8
```

### 输出样例 2：
```
546
```

## 说明

### 【数据范围】
 $100\%$ 的数据保证：$1 \leq n \leq 100000; 1 \leq Wi \leq 1000$。

## 题解

~~坑人啊，无论怎么沾都是最小~~

本题是 __模拟题__，模拟的是沾胶水的过程。可以先设置一个队列，内部存储每个粉笔的重量，每次让两根粉笔合并并记录胶水量即可。

```c++
#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
const int N = 100001;
ull n, ans = 0;
queue<ull> w;

int main() {
    freopen("glue.in", "r", stdin);
    freopen("glue.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        w.push(x);
    }
    while(w.size() > 1) {   //当队列中的粉笔数量>1(可合并)
        ull x = w.front();      //取出两根粉笔
        w.pop();
        ull y = w.front();
        w.pop();
        w.push(x + y);          //模拟合并操作
        ans += (x * y);
    } 
    cout << ans << endl;
    return 0;
}
```

# 二、智质数（prime）

## 题目描述
智质博士最近发现了一种数字，叫做“智质数”。

“智质数”是指，如果一个数字本身是质数，而且将最低位删除后得到的数字还是质数、再把最低位删除后得到的数字仍是质数……如此往复，直到得到一个一位数，仍是质数，那么我们就称它是“智质数”。

例如：数字 $739$，$739$ 本身是质数，删掉最低位后是 $73$，$73$ 还是质数；再删掉最低位后是 $7$，还是质数。

智质博士想请你帮忙计算一下，一定范围内的所有“智质数”。

## 输入格式
输入文件名：`prime.in` 一行，两个整数 $n$ 和 $m$，表示求“智质数”的范围。

## 输出格式
输出文件名：`prime.out` 一行，多个用空格隔开的整数，分别表示 $n$ 到 $m$ 之间（包括 $n$ 和 $m$）所有的“智质数”

## 样例

### 样例输入 #1
```
1 30
```

### 样例输出 #1
```
2 3 5 7 23 29
```

### 样例输入 #2
```
100 500
```

### 样例输出 #2
```
233 239 293 311 313 317 373 379
```

## 说明


- 对于 $50\%$ 的数据，$1 \leq n \leq m \leq 100$。
- 对于 $100\%$ 的数据，$1 \leq n \leq m \leq 10000$。

## 题解

由于本题 $100\%$ 的数据都保证 $1 \leq n \leq m \leq 10000$，可以使用 $\mathbf{O}(n)$ 时间复杂度的 __枚举__ 算法。

枚举 $[n,m]$ 的所有数，判断是不是并输出即可。判断只需要不断删除最低位进行质数判断即可，由于质数判断次数过多，考虑 __素数筛法__ （~~其实我不太会，写得不标准~~）。

```c++
#include <bits/stdc++.h>
using namespace std;

bool isPrime[10001] = {};
void Shai() {                   //埃氏筛法
    //热知识，假如对int类型的数组用memset()填充0x3f（2byte），每个元素是0x3f3f3f3f（8byte）
    memset(isPrime, true, sizeof isPrime);  //初始化，假设所有数都是质数（这里写法不标准，但由于非0就是true，所以不会错）
    isPrime[0] = isPrime[1] = false;    //0，1不是质数
    isPrime[2] = true;                  //2是质数
    for(int i = 2; i <= 10000; i++) {   //[2,10000]区间
        if(isPrime[i])                  //如果i是质数
            for(int bei = 2; i * bei <= 10000; bei++) { //在[2,10000]区间内将i的倍数标记为非质数
                isPrime[i * bei] = false;
            }
    }
}

//检查i是否为“智质数”
bool check(int i) {
    while(i) {
        if(!isPrime[i]) return false;
        i /= 10;        //删去最低位
    }
    return true;
}

int main() {
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    int l, r;
    cin >> l >> r;
    Shai();
    for(int i = l; i <= r; i++) {   //枚举
        if(check(i)) cout << i << " ";
    }
    return 0;
}
```
# 三、 峰谷数（num）

## 题目描述：
数学家馒小头最近在研究数字的进制关系，他发现了一种神奇的数字关系，用两个不同的数字交替出现如 $1212121$，他命名这种数字为峰谷数。

在峰谷数的基础上他又定义了一个概念“双重峰谷数”，即在两种进制下都是峰谷数的数字，例如十进制中的 $191919$，它在十进制下是一个峰谷数，当转为 $11$ 进制后为 $121212$ 也是一个峰谷数，所以十进制下的 $191919$ 就是一个双重峰谷数。当然他觉得，只有一位的数也是峰谷数，例如 $1$，$2$ 这种。

类似的也可以找到三重或者四重的峰谷数，例如 $300_{(10)}=606_{(7)}=363_{(9)}=454_{(8)}=1A1_{(13)}$ 就是一个四重峰谷数，你需要帮助馒小头在指定的范围内找到双重、三重、四重
的峰谷数。

## 输入格式：
输入文件名：`num.in` 

一行，共五个空格隔开的整数，$l,r,L,R,k$。其中 $[l,r]$ 表示需要考虑的进制范围，$[L,R]$ 表示需要考虑的数字范围，$k$ 表示要找的峰谷数的重数。

## 输出格式：
输出文件名：`num.out`

按照十进制的形式从大到小输出指定范围内的 $k$ 重峰谷数，每个数字一行。

## 样例

### 样例输入 #1
```
10 11 190000 960000 2
```
### 样例输出 #1
```
191919
383838
575757
767676
959595
```
### 样例输入 #2
```
2 10 1000 100000 2
```
### 样例输出 #2
```
1300
1365
1950
2050
2730
5252
9595
10922
21845
87381
```
## 【说明】：
对于 $100\%$ 的数据，$2 \leq l \leq r \leq 32,1 \leq L \leq R \leq 10^7,2 \leq k \leq 4$。

## 题解

### 暴力枚举（0pt）
枚举 $[L,R]$ 中的所有数，判断。
```c++
#include <bits/stdc++.h>
using namespace std;

//判断num是否是峰谷数
bool isNum(stack<int> &num) {
    if(num.size() == 1) return true;
    int a = num.top(); num.pop();
    int b = num.top(); num.pop();
    if(a == b) return false;
    while(num.size()) {
        if(a == num.top()) {
            num.pop();
            if(num.empty()) break;
            if(b == num.top()) {
                num.pop();
            } else return false;
        } else return false;
    }
    return true;
}

bool check(int num, int l, int r, int k) {
    int _c = 0;
    for(int jinzhi = l; jinzhi <= r; jinzhi++) {
        int _num = num;
        stack<int> chnum;
        while(_num) {
            chnum.push(_num % jinzhi);
            _num /= jinzhi;
        }   //进制转换
        _c += isNum(chnum);
    }
    return _c == k;
}

int main() {
    freopen("num.in", "r", stdin);
    freopen("num.out", "w", stdout);
    int l, r, L, R, k;
    cin >> l >> r >> L >> R >> k;
    
    for(long long i = L; i <= R; i++) {
        if(check(i, l, r, k)) cout << i << "\n";
    }

    return 0;
}
```

### 构造法（100pts）
既然枚举不行，那就以分别取 $[l,r]$ 中的每个数$i$，以进制 $i$ 构造形如 $\overline{ABABAB}\ldots$ 的数，只需判断其是否为 $k$ 重峰谷数即可。

```c++
#include <bits/stdc++.h>
using namespace std;

int l, r, L, R, k;
int cnt[10000001];

int main() {
    freopen("num.in", "r", stdin);
    freopen("num.out", "w", stdout);
    cin >> l >> r >> L >> R >> k;
    for(int i = l; i <= r; i++) {   //i进制 ABABABAB...
        for(int j = 1; j < i; j++) {    //数字A
            for(int k = 0; k < i; k++) {    //数字B
                if(j == k) continue;        //A!=B
                long long num = 0, t = 0;   
                while(num <= R) {
                    if(t % 2 == 0) num = num * i + j;   //每次在num的末位追加i或j
                    else num = num * i + k;
                    t++;
                    if(num <= R) cnt[num]++;            //用桶记录num的峰谷数重数
                }
            }
        }
    }
    for(int i = L; i <= R; i++) {
        if(cnt[i] == k) cout << i << endl;
    }
    return 0;
}
```

# 四、臭皮匠（cobbler）

## 题目描述：
中国有句古话“三个臭皮匠顶个诸葛亮”，现在给定 $n$ 个臭皮匠的战力值 $A_i$，以及诸葛亮的战力值 $T$ ，请你找到最接近诸葛亮的三个战力和，即三个人的战力和与诸葛亮的战力越接近越好，输出这三个人的战力和。

## 输入格式：
输入文件名：`cobbler.in`


- 第一行：输入两个整数：$n$ 和 $T$，分别表示臭皮匠的人数以及诸葛亮的战力值。
- 第二行：输入 $n$ 个空格分隔的整数，表示每个臭皮匠的战力值。

## 输出格式：
输出文件名：`cobbler.out`

输出只有一行：一个整数，为最接近诸葛亮战力的三数之和。

## 样例

### 输入样例 1：
```
4 1
-1 -4 1 2
```
### 输出样例 1：
```
2
```
### 输入样例 2：
```
3 1
0 0 0
```
### 输出样例 2：
```
0
```
## 说明：

### 样例 1 解释：
选择 $-1、1、2$ 得到的和为：$-1+1+2 = 2$ ，此为最接近 $1$ 的三数之和。

### 数据范围：


- 对于 $50\%$ 的数据：$1 \leq n \leq 100，-10^4 \leq T,Ai \leq 10^4$；
- 对于 $100\%$ 的数据：$1 \leq n \leq 1000，-10^4 \leq T,Ai \leq 10^4$；

对于所有的数据保证，与 $T$ 最接近的三数之和，答案唯一。

## 题解
纯纯 ~~抄袭[Leetcode三数之和](https://leetcode.cn/problems/3sum/description/)~~。

翻译：在 $n$ 个数的序列中找到 $3$ 个数使它们的和最 __接近__ $T$。这种题目当然用双指针来做啦：


1. 将数组以升序排序
2. 固定一个数 $i$，用双指针在 $[i+1,n]$ 区间内作 [__反向扫描__](https://xingchen8800.github.io/2024/07/02/尺取法（双指针）/)。$j$ 右移条件：$a_i + a_j + a_k < T$，$k$ 左移条件：$a_i + a_j + a_k > T$。

```c++
#include <bits/stdc++.h>
using namespace std;

int n, T;
int a[3003];

int main() {
    freopen("cobbler.in", "r", stdin);
    freopen("cobbler.out", "w", stdout);
    scanf("%d", &n); scanf("%d", &T);
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);
    
    sort(a + 1, a + n + 1);
    long long _min = 0x3f3f3f3f, ans = 0;
    for(int i = 1; i <= n; i++) {
        int j = i + 1, k = n;
        while(j < k) {
            if(abs(a[i] + a[j] + a[k] - T) < _min) {    //更新最小差距
                _min = abs(a[i] + a[j] + a[k] - T);
                ans = a[i] + a[j] + a[k];
            }
            if(a[i] + a[j] + a[k] > T) k--;             //k左移
            else if(a[i] + a[j] + a[k] < T) j++;        //j右移
            else break;
        }
        if(ans == T) break;
    }
    cout << ans << endl;
    return 0;
}
```


# 五、 旅行(travel）

## 题目描述：
小A非常喜欢旅行，他想去泰国、新加坡、印度尼西亚，想尝尝咖喱、肉骨茶以及印尼九层塔，想晒太阳、放烟花，参加泳池趴。但是假期有限，还有一堆事情要完成，所以他只能选择一个地方去旅行。所以他开始规划他的旅行了，小A计划坐火车去旅行，首先他先想办法到邻近的几个城市，然后从城市坐火车去。另外小A想花最短的时间选择一个想去的地方去旅行这样能够省很多的时间。接下来给出城市之间的线路信息，请你帮助策划一下这趟旅行。

## 输入格式：
输入文件名: `travel.in`

数据包含多组数据，对于每组数据：


- 第一行，用空格隔开的三个整数 $m,s,d$ ,$m$ 表示城市之间有 $m$ 趟列车, $s$ 表示跟小A家相邻的有 $s$ 个城市，$d$ 表示小A有 $d$ 个想去的城市
- 接下来 $m$ 行，每行描述一个车次信息，是用空格隔开的三个整数 $u,v,w$ 表示城市 $u,v$ 之间有一趟车，车程 $w$ 小时($u$ 和 $v$ 之间有可能存在多种车次)。
- 接下来一行，是用空格隔开的 $s$ 个整数，表示跟小A家相邻的 $s$ 个城市的编号
- 接下来一行，是用空格隔开的 $d$ 个整数，表示小A想去的城市的编号。

## 输出格式：
输出文件名：`travel.out`

对于每组数据，输出一行，一个整数表示小A能够到达一个他想去的城市的最短花费时间。

## 样例

### 样例输入 #1
```
6 2 3
1 3 5
1 4 7
2 8 12
3 8 4
4 9 12
9 10 2
1 2
8 9 10
```
### 样例输出 #1
```
9
```

## 说明

### 【数据规模与约定】
对于 $100\%$ 的数据，总的测试组数 $≤10$。城市的总数量 $≤1000$，$u,v,w$  都是 $1000$ 以内的正整数。

## 题解
~~提高组的简单题到普及组串门了~~

翻译：有 $s$ 个源点、$d$ 个终点，输入 $m$ 条边（$E(u,v,w)$），求 $s$ 个源点到 $d$ 个终点的所有路径中最短的。

很明显是 __最短路径问题__

{% notel default fa-link 链接%}


- 最短路径1（Floyed和Dijsktra）： [传送门](https://xingchen8800.github.io/2024/08/27/d13/)
- 最短路径2（Bellman和SPFA）： [传送门](https://xingchen8800.github.io/2024/08/28/d14/)
{% endnotel %}

首选 __Dijsktra__ 和 __SPFA__。但是有 $s$ 个源点，该怎么办呢？很简单，运用 __网络流__ 学到的 __虚拟源点__，将 $s$ 个真源点连接到一个虚拟源点上。

![虚拟源点(图)](https://cdn.luogu.com.cn/upload/image_hosting/2e7z5xxa.png)

对于多个汇点的问题，我们不需要担心，因为以虚拟源点为源点跑一次最短路就可以获得`dis[所有点]`。

### Dijsktra做法
```c++
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w, nxt;
};
array<Edge, 1001> edge;

int head[1001], cnt = 1;

void AddEdge(int u, int v, int w) {
    edge[cnt] = {u, v, w, head[u]};
    head[u] = cnt++;
}

//优先队列 + Dijsktra
int dis[1001] = {};
bool vis[1001] = {};
void Dijsktra(int s) {
    //初始化
    memset(dis, 0x3f, sizeof dis);
    memset(vis, false, sizeof vis);
    
    //s入队
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > q; //优先队列免去了在dis中找最小值的操作
    dis[s] = 0;
    q.push({0, s});
    
    //bfs
    while(q.size()) {
        pair<int, int> h = q.top(); q.pop(); //取出队首
        int u = h.second;   //获取节点
        if(!vis[u]) {
            vis[u] = true;
            int v, w;  //邻接点和权值
            //遍历邻接点
            for(int i = head[u]; ~i; i = edge[i].nxt) {
                v = edge[i].v;  //邻接点
                w = edge[i].w;  //权值
                if(!vis[v] && dis[v] > dis[u] + w) {    //松弛
                    dis[v] = dis[u] + w;
                    q.push({dis[v], v});
                }
            }
        }
    }
}

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);

    int m, s, d;
    while(cin >> m >> s >> d) {
        edge.fill({0, 0, 0, -1});
        memset(head, -1, sizeof head);

        for(int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            AddEdge(u, v, w); AddEdge(v, u, w); //无向图
        }
        for(int i = 1; i <= s; i++) {
            int x; cin >> x;
            AddEdge(0, x, 0);   //从0（虚拟源点）到x连接权值为0的单向边
        }
        Dijsktra(0);
        
        int minDis = 114514;
        for(int i = 1; i <= d; i++) {
            int x; cin >> x;
            minDis = min(minDis, dis[x]);
        }
        cout << minDis << endl;
        return 0;
    }
}
```

### SPFA做法
```c++
#include <bits/stdc++.h>
using namespace std;

int m, s, d;
int S[1001], D[1001];

//链式前向星
struct Edge {
    int u, v, w, nxt;
} edge[1001];
int head[1001], cnt = 1;

void AddEdge(int u, int v, int w) {
    edge[cnt] = {u, v, w, head[u]};
    head[u] = cnt++;
}

long long dis[1001] = {}, vis[1001] = {};
void SPFA(int s) {
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    vis[s] = true;
    while(q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int ed = head[u]; ~ed ; ed = edge[ed].nxt) { //遍历邻接点
            if(dis[u] + edge[ed].w < dis[edge[ed].v]) { 
                int v = edge[ed].v, w = edge[ed].w;
                dis[v] = dis[u] + w;                    //松弛 
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
}

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    while(cin >> m >> s >> d) {
        memset(edge, 0, sizeof edge);
        memset(head, -1, sizeof head);
        for(int i = 1; i <= m; i++) {
            int u, v, w;
            scanf("%d", &u);
            scanf("%d", &v);
            scanf("%d", &w);
            AddEdge(u, v, w);
            AddEdge(v, u, w);
        }
        for(int i = 1; i <= s; i++) {
            scanf("%d", &S[i]);
            AddEdge(0, S[i], 0);
        }
        SPFA(0);
        long long _min = 0x3f3f3f3f;
        for(int i = 1; i <= d; i++) {
            scanf("%d", &D[i]);
            _min = min(_min, dis[D[i]]);
        }
        cout << _min << endl;
    }
    return 0;
}
```