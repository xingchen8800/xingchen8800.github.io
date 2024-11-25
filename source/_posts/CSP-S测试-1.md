---
title: CSP-S日常测试(240831)
date: 2024-08-31 21:05:04
categories: 
    - [CSP,S,课程]
    - [考试,CSP,S]
tags: 
    - C++
    - CSP提高组
---

{% note green fa-link %}
本篇代码位于 {% btn 这里::https://github.com/xingchen8800/CSP/tree/main/%E8%80%83%E8%AF%95/240831  %}
{% endnote %}

# 晓悦的数学题

## 文件说明


| 输入 | 输出 | 代码 |
|-|-|-|
| `math.in` | `math.out` | `math.cpp` |

## 题目描述
给定一个自然数 $n$ ，求解 $3^n$ 的个位是多少。具体理解可看样例。

## 输入格式
第一行输入一个自然数 $n$ 。

## 输出格式
输出一个数字代表答案。

## 样例 #1

### 样例输入 #1
```
3
```

### 样例输出 #1
```
7
```
## 样例 #2

### 样例输入 #2
```
2
```

### 样例输出 #2
```
9
```

## 样例 #3

### 样例输入 #3
``` 
0
```

### 样例输出 #3
```
1
```

## 提示

### 规范
对于 $50\%$ 的测试数据： $0 \leq n \leq 15$

对于 $100\%$ 的测试数据：$0 \leq n \leq 2^{31}$

## 答案
{% folding 答案 %}
这是一道[快速幂](https://xingchen8800.github.io/2024/08/31/快速幂/)的题~~（打表也不是不行）~~。题干转换为$3^n \mod 10$。

打表写法：
```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    int n;
    cin >> n;
    n %= 4;
    switch(n) {
        case 0: cout << 1 << endl; break;
        case 1: cout << 3 << endl; break;
        case 2: cout << 9 << endl; break;
        case 3: cout << 7 << endl; break;
    }
    return 0;
    fclose(stdin);
    fclose(stdout);
}
```

正解：
```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    int n;
    cin >> n;
    int ans = 1, a = 3;
    while(n) {
        if(n & 1) ans = (ans * a) % 10;
        a = (a * a) % 10;
        n /= 2;
    }
    cout << ans << endl;
    fclose(stdin);
    fclose(stdout);
}
```

{% endfolding %}

## 测试数据
{% btn regular::点我下载::https://wwps.lanzouj.com/iBkOi28u950f %}

# [异或路径（注：链接的数据范围更大）](https://www.luogu.com.cn/problem/AT_abc271_f)

## 文件说明


| 输入 | 输出 | 代码 |
|-|-|-|
| `xor.in` | `xor.out` | `xor.cpp` |

## 题目描述
给定一个 $n$ 行 $n$ 列的网格，用 $(i,j)$ 表示从顶部开始的第 $i$ 行和从左侧开始的第 $j$ 列的单元格 $(1 \leq i,j \leq n)$。每个单元格 $(i,j)$ 中写有一个非负整数 $a_{i,j}$。

当你位于单元格 $(i,j)$ 时，你可以移动到单元格 $(i + 1, j)$ 或 $(i, j + 1)$ 中的任何一个。但是，你不能移动到网格外面。

求从单元格 $(1,1)$ 开始，通过重复移动到达单元格 $(n,n)$ 的方法中，经过的单元格（包括单元格 $(1,1)$ 和 $(n,n)$ ）上写的整数的异或和为 $0$ 的路径的总数是多少？

## 输入格式
第一行包含一个整数 $n$ ，表示网格的行数和列数。

接下来的 $n$ 行，每行包含 $n$ 个非负整数，表示网格中每个单元格的值。每个整数 $a_{i,j}$ 满足 $1 \leq a_{i,j} \leq 8$。

## 输出格式
输出一个整数代表答案。

## 样例 #1

### 样例输入 #1
```
3
1 5 2
7 0 5
4 2 3
```

### 样例输出 #1
```
2
```

## 样例 #2

### 样例输入 #2
```
2
2 1
1 2
```

### 样例输出 #2
```
0
```

## 样例 #3

### 样例输入 #3
```
10
1 0 1 0 0 1 0 0 0 1
0 0 0 1 0 1 0 1 1 0
1 0 0 0 1 0 1 0 0 0
0 1 0 0 0 1 1 0 0 1
0 0 1 1 0 1 1 0 1 0
1 0 0 0 1 0 0 1 1 0
1 1 1 0 0 0 1 1 0 0
0 1 1 0 0 1 1 0 1 0
1 0 1 1 0 0 0 0 0 0
1 0 1 1 0 0 1 1 1 0
```

### 样例输出 #3
```
24307
```

## 提示

### 数据范围
对于 $ 20\%$ 的测试数据 $2 \leq n \leq 10$.
对于 $ 50\%$ 的测试数据 $2 \leq n \leq 15$.
对于 $ 100\%$ 的测试数据 $2 \leq n \leq 20$.

### 样例1解释
对于网格：
```
1 5 2
7 0 5
4 2 3
```
有以下两种方案使异或和为 $0$ ：
$$
(1,1) \rightarrow (1,2) \rightarrow (1,3) \rightarrow (2,3) \rightarrow (3,3)
$$
$$
(1,1) \rightarrow (2,1) \rightarrow (2,2) \rightarrow (2,3) \rightarrow (3,3)
$$

## 答案
{% folding 答案 %}
这道题有多种做法，最好编码、最易想到的自然是 __搜索__。

先尝试暴搜：

1. 设计一个有三个状态的`dfs()`函数：`int dfs(int x, int y, int xor)`，表示当前位置$(x,y)$，异或和为$xor$（含$(x,y)$），返回值为从$(x,y)$到$(n,n)$的异或和为$0$的路线条数
2. 终止条件：$x=n,y=n$，若$xor=0$，则返回$1$
3. 依次走到$(x+1,y)$和$(x,y+1)$，并将异或和更新代入下一层dfs
4. 记录路线条数
5. `dfs(1, 1, a[1][1])`就是答案

DFS函数：
```c++
//int n, a[21][21];
int dx[2] = {1, 0};
int dy[2] = {0, 1};
bool vis[21][21] = {};
int dfs(int x, int y, int _xor) {
    if(x == n && y == n) {
        if(!_xor) return 1;
        else return 0;
    }

    int ans = 0;
    for(int i = 0; i < 2; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx >= 1 && nx <= n && ny >= 1 && ny <= n) {  //不越界
            if(!vis[nx][ny]) {  //未访问
                vis[nx][ny] = true;
                ans += dfs(dx, dy, _xor ^ a[dx][dy]);
                vis[nx][ny] = false;
            }
        }
    }
    return ans;
}
```

显然超时~~（实测只有$35$pts）~~。最简单的优化方式就是记忆化。即：在暴搜的基础之上加一个`dp[][][]`数组，让`dp[x][y][xor]`存储`dfs(x,y,xor)`，这样就以空间换时间，要用搜过的直接返回`dp[x][y][xor]`无需再搜。

```c++
//int n, a[21][21];
int dx[2] = {1, 0};
int dy[2] = {0, 1};
bool vis[21][21] = {};
int dp[21][21][16] = {};    //由于1 <= a[i][j] <= 8，所以xor结果最大是2^4=16
int dfs(int x, int y, int _xor) {
    if(dp[x][y][_xor] != dp[0][0][0]) return dp[x][y][_xor];    //调用记忆
    if(x == n && y == n) {
        if(!_xor) return 1;
        else return 0;
    }

    int ans = 0;
    for(int i = 0; i < 2; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx >= 1 && nx <= n && ny >= 1 && ny <= n) {  //不越界
            if(!vis[nx][ny]) {  //未访问
                vis[nx][ny] = true;
                ans += dfs(dx, dy, _xor ^ a[dx][dy]);
                vis[nx][ny] = false;
            }
        }
    }
    if(ans == 0) return 0;
    else return dp[x][y][_xor] = ans;   //保存记忆
}

// int main() {
//...
    memset(dp, ~0x3f, sizeof dp);
//...
//}
```

这样就可以AC通过了。

但是还有一种方案——[__折半搜索__](https://xingchen8800.github.io/2024/08/31/折半搜索/)（可以通过洛谷的题目）。

折半搜索的例题中，是将礼物重量的数组折半，这次我们将网格图折半（迫真）：

![（图）沿对角线分开后的样例#1](/images/cspstest240831-1.png)

由异或的性质，可以知道，两个相同的数异或的值为0。由于我们将网格图折半，设$(x,y) (x+y=n+1)$为对角线上一点，则我们需要让$(1,1) \rightarrow (x,y) = (x,y) \rightarrow (n,n)$。

![（图）图示](/images/cspstest240831-2.png)
![（图）合并路线](/images/cspstest240831-3.png)

1. 我们以$(1,1)$为起点，对角线为终点，进行第一次DFS。即每当搜到对角线时，将当前参数组成三元组（x、y坐标，异或和）再`map`中对应的计数器累加。
2. 我们以$(n,n)$为起点，对角线为终点，进行第二次DFS。这次，每当搜到对角线时，将答案加上`map`中三元组对应的计数器即可。

```c++
// ./CSP/考试/240831/xor-折半搜索.cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 21;
int n, a[N][N];

//折半搜索
int ans = 0;
map< pair<pair<long long, long long>,long long>, int> cnt;
void dfs1(int x, int y, int cur) {
    cur ^= a[x][y];
    if(x + y == n + 1) { //在对角线上
        cnt[make_pair(make_pair(x, y), cur)]++;
        return;     //回溯
    }
    dfs1(x + 1, y, cur);    //走法1
    dfs1(x, y + 1, cur);    //走法2
}

void dfs2(int x, int y, int cur) {
    //先判断，防止重复异或
    if(x + y == n + 1) {    //在对角线上
        ans += cnt[make_pair(make_pair(x, y), cur)];
        return;     //回溯
    }
    cur ^= a[x][y];
    dfs2(x - 1, y, cur);    //反走法1
    dfs2(x, y - 1, cur);    //反走法2
}

int main() {
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++) cin >> a[i][j];

    dfs1(1,1, 0);
    dfs2(n,n, 0);
    cout << ans << endl;
    fclose(stdout);
    fclose(stdin);
    return 0;
}
```

{% endfolding %}

## 测试数据
{% btn regular::点我下载::https://wwps.lanzouj.com/ifZ6h28udixa %}

# [子串](https://www.luogu.com.cn/problem/P10995)

## 文件说明


| 输入 | 输出 | 代码 |
|-|-|-|
| `substr.in` | `substr.out` | `substr.cpp` |

## 题目描述

你有一个数列 $a$，**其中 $1\sim n$ 各出现了一次**。

当你任意选一对 $1\le l\le r\le n$，并将 $a_l,a_{l + r}, \dots ,a_r$ 排成一行。

这样，你就得到了 $a$ 的一个子串，记为 $a_{l \sim r}$ ，称 $l$ 为左端点，$r$ 为右端点。

你需要把 $a$ 所有子串按字典序从小到大排序。但是为了避免输出量过大，我会给出 $q$ 个问题，每次给出一个 $k$，求字典序第 $k$ 小的子串左右端点。

---

如果你不知道什么是字典序，看这里：

对于两个数列 $p,q$，称 $p$ 的字典序小于 $q$（记为 $p<q$），当且仅当存在**自然数** $k$ 使 $p,q$ 的前 $k$ 个数相同且 $p_{k+1}<q_{k+1}$。

特别地，若 $p$ 是 $q$ 的前缀且 $p\ne q$，也认为 $p$ 的字典序小于 $q$。

例如：
- $[1,2]<[3,2]$（当 $k=0$）
- $[3,1,100]<[3,2,1]$（当 $k=1$）
- $[3,4]<[3,4,6]$（$p$ 是 $q$ 前缀）

## 输入格式

输入的第一行有两个正整数 $n,q$ 表示序列长度和询问个数。

第二行有 $n$ 个正整数 $a_1,a_2,\ldots,a_n$，表示这个数列。

之后有 $q$ 行，每行有一个正整数 $k$，表示要求的子串的排名。

## 输出格式

对于每个问题，输出一行两个整数 $l,r$，表示字典序第 $k$ 小的子串是 $a_{l\sim r}$。

## 样例 #1

### 样例输入 #1

```
3 6
3 1 2
1
2
3
4
5
6
```

### 样例输出 #1

```
2 2
2 3
3 3
1 1
1 2
1 3
```

## 样例 #2

### 样例输入 #2

```
50 25
42 22 27 8 44 11 14 31 37 10 48 15 12 40 13 4 25 9 19 5 2 18 6 1 32 3 38 33 43 34 46 47 23 35 21 20 45 39 50 7 36 17 24 29 16 30 49 26 28 41
1178
991
755
1094
689
132
671
635
421
659
448
334
327
213
1206
453
1160
583
388
781
150
692
23
1162
62
```

### 样例输出 #2

```
37 48
27 44
3 28
1 46
43 47
20 34
33 37
2 19
15 44
2 43
7 27
6 31
6 24
4 29
32 37
7 32
5 44
19 47
13 47
44 45
23 24
43 50
24 46
5 46
26 30
```

## 提示

**【样例解释 #1】**

数列 $3,1,2$ 共有 $6$ 个子串，从小到大排序的结果为：$[1],[1,2],[2],[3],[3,1],[3,1,2]$。

**【数据范围】**

|测试点编号|$n\le$|$q\le$|特殊性质|
|:-:|:-:|:-:|:-:|
|$1\sim 3$|$200$|$200$||
|$4\sim 7$|$1000$|$3\times 10^5$||
|$8\sim 9$|$3000$|$3\times 10^5$||
|$10\sim 13$|$3\times 10^5$|$10$||
|$14\sim 15$|$3\times 10^5$|$3\times 10^5$|$a_i=i$|
|$16\sim 20$|$3\times 10^5$|$3\times 10^5$||

对于全体数据，保证 $1\le n,q\le 3\times 10^5$，$1\le k\le \dfrac{n(n+1)}{2}$，$a_i$ 中 $1\sim n$ 各有一个，输入皆为整数。

## 答案
{% folding 答案 %}

先考虑暴力做法：将每个可能的子串求出（$\mathbf{O}(n^2)$），并且排序（$\mathbf{O}(nlog_2n)$），输出复杂度为$\mathbf{O}(1)$

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 500001;
int a[N], n;

struct Node {
    string s;
    int l, r;
} substrs[N * 10];

int cnt = 0;

bool cmp(Node &a, Node &b) {
    return a.s < b.s;
}

int main() {
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);
    int q, x;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            string s;
            for(int k = i; k <= j; k++) {
                s += a[k] + '0';
            }
            substrs[cnt++] = (Node){s, i, j};
        }
    }
    sort(substrs, substrs + cnt , cmp);

    while(q--) {
        cin >> x;
        cout << substrs[x - 1].l << " " << substrs[x - 1].r << endl;
    }
    fclose(stdout);
    fclose(stdin);
    return 0;
}
```

***

>搬运自@yummy的题解

进一步思考，我们不求出所有子串，照样可以回答“第 $k$ 个子串是谁”的问题吗？

假设 $a_l=x$，记 $p_x=l$，即“ $x$ 的位置是 $l$ ”，那么 $x$ 开头的子串就有 $n+1−p_x$ 个。

在读入整个 $a$ 后，我们对于所有 $i=1,2,\dots,n$，知道了以 $i$ 开头的子串个数。进而作前缀和，对于所有 $i=1,2,\dots,n$，可知开头 $\leq i$ 的子串个数，记为 $c_i$ 。

对于一个问题，我们查找最小的 $l$ 使得 $k \leq c_l$，这样 $c_{l−1} + 1 \leq k \leq c_l$ ，即 $k$ 在 第$c_{l-1}$ 小和第 $c_l$小之间。左端点的数值就是 $l$ 了，左端点下标是 $p_l$。然后计算 $k - c_{l-1}$ 得到区间长度，计算 $p_l + k − c_{l−1} −1$  就可以求出右端点。

```c++
#include<bits/stdc++.h>
using namespace std;

int n, q, x, p[300005]; //a[l] = x, p[x] = l
long long k, c[300005]; //c[i] = 开头为1~i的子串数量

int main(){
    cin >> n >> q;

	for(int i = 1;i <= n; i++){
		cin >> x;
		p[x] = i; //映射
	}

	for(int i = 1;i <= n; i++)
		c[i] = c[i - 1] + n - p[i] + 1;  //前缀和

	while(q--) {
		cin >> k;   //第k大
		int l = lower_bound(c, c + n + 1, k) - c;   //寻找第一个<=k的元素下表
		cout << p[l] << " " << k - c[l - 1] + p[l] - 1 << endl;
	}
	return 0;
}
```

{% endfolding %}

## 测试数据
{% btn regular::点我下载::https://wwps.lanzouj.com/ie30128ufw9c %}