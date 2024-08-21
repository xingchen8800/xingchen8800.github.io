---
title: CSP-J：动态规划
categories:
    - [CSP,CSP-J,课程]
    - [CSP,CSP-S,非课程]
    - [算法,动态规划,背包问题]
    - [《算法竞赛》,第五章]
date: 2024-08-18 20:31:30
---

# 背包问题

## 入门-0/1背包问题(CSP-J难度)

### 问题描述
{% note red fa-pen %}
给定 $n$ 个物品和大小为 $C$ 的背包。对于第 $i$ 个物品，它占用的大小是 $c_i$，价值是 $w_i$，可以选择装入或者不装入背包。求背包中最多能装下价值多少的物品
{% endnote %}

### 简单分析
设 $x_i$ 表示物品 $i$ 的放入情况，则当 $x_i=0$ 时不装入背包，反之则装入背包。则有如下定义：

__约束条件__：
$$
\sum^{n}_{i=1}c_i \cdot x_i \leq C, x_i=0或1
$$

__目标函数__：
$$
\operatorname{max} \sum^{n}_{i=1}w_i \cdot x_i
$$

### DP的状态设计
定义一个 $N+1$ 行 $C+1$ 列的二维数组 `dp[][]`。其中，`dp[i][j]`表示把前 $i$ 个物品（通过某种最优规划）装入大小为 $j$ 的背包后价值的最大值。这样一来，每个`dp[i][j]`就是一个大小为 $j$，物品数为 $i$ 的子背包，`dp[N][C]`就是问题的解。

### DP的状态转移方程设计
1. 先考虑最简单的情况，背包放不下第 $i$ 个新物品：则背包中物品的总价值不变
```c++
dp[i][j] = dp[i - 1][j];
```
2. 当背包能装进第 $i$ 个新物品时，又有两种情况：
    1. __我装__：

        既然装了，背包的大小 $j$ 就要相应地减去物品的大小 $c_i$，同时总价值 `dp[i - 1][j - c[i]]` 要加上物品的价值 $w_i$。
        ```c++
        dp[i][j] = dp[i - 1][j - c[i]] + w[i];  //因为装了，所以应从物品数量为i - 1，背包大小为j - c[i]的子背包转移，即：dp[i][j]从dp[i - 1][j - c[i]]状态转移而来
        ```
    2. __我不装__：

        既然不装，背包的大小自然地不用变，仍为 $j$，总价值也不变，仍为 `dp[i - 1][j]`。
        ```c++
        dp[i][j] = dp[i - 1][j];    //因为不装，所以总价值就是删去了第i个物品且背包大小为j的总价值，dp[i][j]从dp[i - 1][j]状态转移而来
        ```
  究竟装不装呢，求最大值，步步最优等于全局最优。
  ```c++
  dp[i][j] = max(dp[i - 1][j - c[i]] + w[i], dp[i - 1][j]);
  ```

故状态转移方程为：
$$
dp[i][j]= \begin{cases} dp[i - 1][j], j < c_i & \text{放不下} \\\\ \operatorname{max}({dp[i - 1][j - c_i] + w_i}, {dp[i - 1][j]}), j \geq c_i & \text{放得下} \end{cases}
$$

```c++
if(j < c[i]) dp[i][j] = dp[i - 1][j];
else dp[i][j] = max(dp[i - 1][j - c[i]] + w[i], dp[i - 1][j]);
```

### 代码编写
```c++
#include <bits/stdc++.h>
using namespace std;

int N = 1001;
int dp[N][N];
int w[N], c[N];

int Solve(int i, int j) {   //求dp[i][j]，从上往下
    if(dp[i][j] != 0) return dp[i][j];  //记忆化
    if(!i) return 0;    //没有了搜什么搜
    
    int result;
    if(c[i] < j) result = Solve(i - 1, j);    //装不了
    else result = max(Solve(i - 1, j - c[i]) + w[i], Solve(i - 1, j));    //装得下

    return dp[i][j] = result;   //记忆化
}

int main() {
    int n, C;
    
    cin >> n >> C;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];

    memset(dp, 0, sizeof dp);
    cout << Solve(n, C);
    return 0;
}
```

### 提高拔尖（Warning：省选+，非CSP-J内容）

#### [USACO18OPEN] Talent Show G

##### 题目描述

Farmer John 要带着他的 $n$ 头奶牛，方便起见编号为 $1\ldots n$，到农业展览会上去，参加每年的达牛秀！他的第 $i$ 头奶牛重量为 $w_i$，才艺水平为 $t_i$，两者都是整数。

在到达时，Farmer John 就被今年达牛秀的新规则吓到了：

（一）参加比赛的一组奶牛必须总重量至少为 $W$（这是为了确保是强大的队伍在比赛，而不仅是强大的某头奶牛），并且。

（二）总才艺值与总重量的比值最大的一组获得胜利。

FJ 注意到他的所有奶牛的总重量不小于 $W$，所以他能够派出符合规则（一）的队伍。帮助他确定这样的队伍中能够达到的最佳的才艺与重量的比值。

##### 输入格式

第一行是两个整数，分别表示牛的个数 $n$ 和总重量限制 $W$。

第 $2$ 到 $(n+1)$ 行，每行两个整数，第 $(i + 1)$ 行的整数表示第 $i$ 头奶牛的重量 $w_i$ 和才艺水平 $t_i$。

##### 输出格式

请求出 Farmer 用一组总重量最少为 $W$ 的奶牛最大可能达到的总才艺值与总重量的比值。

如果你的答案是 $A$，输出 $1000A$ 向下取整的值，以使得输出是整数（当问题中的数不是一个整数的时候，向下取整操作在向下舍入到整数的时候去除所有小数部分）。

请注意当问题的答案恰好是整数 $x$ 时，你的程序可能会由于**浮点数精度误差**问题最后得到一个 $x-\epsilon$ 的答案，向下取整后变为 $x-1$ 导致答案错误。这种情况下你可以在输出答案前给答案加上一个极小的值 $x\gets x+10^{-k}$ 来避免该问题。

##### 样例 #1

###### 样例输入 #1

```
3 15
20 21
10 11
30 31
```

###### 样例输出 #1

```
1066
```

##### 提示

###### 样例解释

在这个例子中，总体来看最佳的才艺与重量的比值应该是仅用一头才艺值为 $11$、重量为 $10$ 的奶牛，但是由于我们需要至少 $15$ 单位的重量，最优解最终为使用这头奶牛加上才艺值为 $21$、重量为 $20$ 的奶牛。这样的话才艺与重量的比值为 $\frac{11+21}{10+20}=\frac{32}{30} = 1.0666\dots$，乘以 $1000$ 向下取整之后得到 $1066$。

###### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 250$，$1 \leq W \leq 1000$，$1 \leq w_i \leq 10^6$，$1 \leq t_i \leq 10^3$。

#### 题目解析
##### 题意
题意很简单，有 $n$ 头牛，每头牛的重量为 $w_i$，才艺值（价值）为 $t_i$，求一队总重量大于 $W$、才艺值与总重量之比最大的牛。

我们设才艺值与总重量之比的最大值为 $R$，每头牛的选择状态为 $x_i$，由题意可知：
$$
R = \sum^{n}_{i=1}{t_i \cdot x_i} : \sum^{n}_{i=1}{w_i \cdot x_i}
$$
即：
$$
\sum^{n}_{i=1}{t_i \cdot x_i} = \sum^{n}_{i=1}{w_i \cdot x_i} \times R
$$

再设一个才艺值与总重量之比 $Z (\sum^{n}_{i=1}{w_i \cdot x_i} \times Z > W, Z < 10^6)$，使得 $Z < R$（不那么优秀）

则有：
$$
\sum^{n}_{i=1}{t_i \cdot x_i} \geq \sum^{n}_{i=1}{w_i \cdot x_i} \times Z
$$
即：
$$
\sum^{n}_{i=1}{t_i \cdot x_i} - \sum^{n}_{i=1}{w_i \cdot x_i} \times Z \geq 0
$$
合并：
$$
\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z}  \geq 0
$$

注意到，当这个式子成立时，说明 $Z$ 可行并有更靠近 $R$ 的 __可能__！

所以我们选择二分 $Z$，对于每个 $Z$ 验证 $\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z}  \geq 0$ 的可能性，不断让 $Z$ 逼近 $R$ 即可。

那么，如何验证  $\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z}  \geq 0$ 的可能性呢？当然是~~我们的正题~~0/1背包。

##### DP的状态转移思路：
设 `dp[a]` 为使用总重量为 $a$ 的牛时 $\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z} \geq 0$ 的最大值。`dp[W]`比较特殊，为了节省空间、方便返回，`dp[W]`存储的是使用总重量大于等于 $W$ 的牛时 $\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z} \geq 0$ 的最大值。（一维滚动数组）

由 $\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z}  \geq 0$ 可知，每头牛的“贡献”为 $(t_i - w_i) \cdot x_i \cdot Z$。

对于 $x_i$，由0和1两种状态，令 $j$ 从 $W$ 递减到 $0$，表示加入奶牛$i$前的总重：

1. $x_i=0$，不选：

    这种状态最简单，`dp[j]`保持不动即可。

2. $x_i=1$，选：
    
    选了，就要看贡献。
    ```c++
    dp[min(j + w[i], W)] = max(dp[min(j + w[i], W)], dp[j] + t[i] - (long long)w[i] * z);   //min(j + w[i], W)是为了将j + w[i]控制再W以内，dp[min(j + w[i], W)]表示加入奶牛i前总重量为min(j + w[i], W)的 $\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z} \geq 0$ 的最大值。dp[j] + t[i] - (long long)w[i] * z则表示加入奶牛i后 $\sum^{n}_{i=1}{(t_i - w_i) \cdot x_i \cdot Z} \geq 0$ 的最大值。
    ```

则构成状态转移代码：
```c++
for(int i = 1; i <= n; i++) {
    for(int j = W; j >= 0; j--) {
        if(dp[j] > 0x3f3f3f3f) { //dp[j]不为负无穷才能状态转移
            dp[min(j + w[i], W)] = max(dp[min(j + w[i], W)], dp[j] + t[i] - long long)w[i] * z;
        }
    }
}
```

##### AC代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 10001;
int n, W, w[251], t[251];
long long dp[N];

bool check(int z) {
    memset(dp, ~0x3f, sizeof dp);
    dp[0] = 0;
    int tmp = dp[W];
    for(int i = 1; i <= n; i++) {
        for(int j = W; j >= 0; j--) { 
            if(dp[j] != tmp) { //dp[j]不为负无穷才能状态转移
                dp[min(j + w[i], W)] = max(dp[min(j + w[i], W)], dp[j] + t[i] - (long long)w[i] * z);
            }
        }
    }
    return dp[W] >= 0;
}

int main() {
    cin >> n >> W;
    for(int i = 1; i <= n; i++) {
        cin >> w[i] >> t[i];
        t[i] *= 1000;
    }
    long long l = 1, r = 1000001, mid;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << l - 1;
    return 0;
}
```

## 变式1-分组背包(CSP-J+难度)
