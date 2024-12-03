---
title: CSP-J：动态规划
categories:
    - [CSP,CSP-J,课程]
    - [CSP,CSP-S,非课程]
    - [算法,动态规划,背包问题]
    - [《算法竞赛》,第五章]
date: 2024-08-18 20:31:30
tags: 
    - C++
    - CSP入门组
    - CSP提高组
excerpt: 背包问题、序列问题和字符串问题
---

## 1. 背包问题

### 入门-0/1背包问题(CSP-J难度)

#### 问题描述

{% note red fa-pen %}
给定 $n$ 个物品和大小为 $C$ 的背包。对于第 $i$ 个物品，它占用的大小是 $c_i$，价值是 $w_i$，可以选择装入或者不装入背包。求背包中最多能装下价值多少的物品
{% endnote %}

#### 简单分析

设 $x_i$ 表示物品 $i$ 的放入情况，则当 $x_i=0$ 时不装入背包，反之则装入背包。则有如下定义：

__约束条件__：
$$
\sum^{n}_{i=1}c_i \cdot x_i \leq C, x_i=0或1
$$

__目标函数__：
$$
\operatorname{max} \sum^{n}_{i=1}w_i \cdot x_i
$$

#### DP的状态设计

定义一个 $N+1$ 行 $C+1$ 列的二维数组 `dp[][]`。其中，`dp[i][j]`表示把前 $i$ 个物品（通过某种最优规划）装入大小为 $j$ 的背包后价值的最大值。这样一来，每个`dp[i][j]`就是一个大小为 $j$，物品数为 $i$ 的子背包，`dp[N][C]`就是问题的解。

#### DP的状态转移方程设计

1. 先考虑最简单的情况，背包放不下第 $i$ 个新物品：则背包中物品的总价值不变

```c++
dp[i][j] = dp[i - 1][j];
```

1. 当背包能装进第 $i$ 个新物品时，又有两种情况：
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

#### 代码编写

##### 递归版本

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1001, M = 1001;
int dp[N][M];
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

##### 递推版本

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1001, M = 1001;
int dp[N][M];
int w[N], c[N];

int main() {
    int n, C;
    
    cin >> n >> C;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i];

    memset(dp, 0, sizeof dp);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= C; j++) {
            if(j < c[i]) dp[i][j] = dp[i - 1][j];       //装不了
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-c[i]]+w[i]);  //装得下
        }
    }
    cout << dp[n][C];

    return 0;
}
```

### 能力点1-滚动数组优化dp

可以发现，在0/1背包问题中，`dp[][]`数组是 __多维__ 的，但是每次状态转移的时候，只用到了`dp[i-1][...]`的数据， __也就是说，这样造成了极大的空间浪费__。

#### 方法1-自我滚动

怎么解决这种问题呢，其实很简单，因为`dp[i][...]`只跟`dp[i-1][...]`有关，只要将`dp[][]`数组降成一维的`dp[]`即可，状态转移变成：`dp[j] = max(dp[j], dp[j - w[i]])`。

{% note yellow fa-warning %}
__注意__：此时 $j$ 应从大到小循环，因为单维数组中没有明确的 __上一次的__ 和 __这一次的__ 数据区分。当 $j$ 从小到大循环时，某个 $j$ 减去 `c[i]` 时会使 $j$ 可能比 $j-1$ 小，可能“引用” __这一次（修改）的__ 数据，造成答案错误。
{% endnote %}

```c++
memset(dp, 0, sizeof dp);
for(int i = 1; i <= n; i++) {
    for(int j = C; j >= c[i]; j--) {
        dp[j] = max(dp[j], dp[j - c[i]] + w[i]);
    }
}
```

#### 方法2-交替滚动

为了让代码逻辑更清晰，可以将`dp[N][M]`降成`dp[2][M]`，用`old`和`now`变量记录当前的修改位置，其中`dp[old][...]`相当于`dp[i-1][...]`；`dp[now][...]`相当于`dp[i][...]`。

```c++
memset(dp, 0, sizeof dp);
int old = 0, now = 1;
for(int i = 1; i <= n; i++) {
    for(int j = 0; j <= C; j++) {
        if(j < c[i]) dp[now][j] = dp[old][j];       //装不了
        else dp[now][j] = max(dp[old][j], dp[old][j-c[i]]+w[i]);  //装得下
    }
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

##### 知识点

本题运用了 __贡献思想__，即：计算每头牛对于答案的贡献。

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

### 变式1-分组背包(CSP-J+难度)

{% note yellow fa-lightbulb %}
__变式点__：加入 __分组__ 概念，每组只能选一个。
{% endnote %}

{% notel default fa-pen 问题描述 %}
有 $n$ 组物品，每组有 $a_i$ 个物品，每组中只能选一个物品，给定这些物品的重量 $c_{i,k}$ 和价值 $w_{i,k}$ $(k \in [1,a_i])$，求在背包大小为 $C$ 时能装的最大价值。
{% endnotel %}

其实和0/1背包一样，只是：

1. 数组 `c[N]` 和 `w[N]` $\rightarrow$ `c[N][maxK]` 和 `w[N][maxk]`。
2. 循环要增加一层，来枚举每组中的第 $k$ 个物品。
3. `dp[i][j]`的含义：已选 $i$ 个物品，容量剩 $j$ $\rightarrow$ 已选 $i$ 组，容量剩 $j$。

#### 代码实现

本题只提供递推式：

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1001, M = 1001, K = 21;
int dp[N][M];
int a[N], w[N][K], c[N][K];

int main() {
    int n, C;
    
    cin >> n >> C;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= a[i]; j++) {
            cin >> w[i][j] >> c[i][j];
        }
    }

    memset(dp, 0, sizeof dp);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= C; j++) {
            for(int k = 1; k <= a[i]; k++) {
                if(j < c[i][k]) dp[i][j] = dp[i - 1][j];       //装不了
                else dp[i][j] = max(dp[i-1][j], dp[i-1][j-c[i][k]]+w[i][k]);  //装得下
            }
        }
    }
    cout << dp[n][C];

    return 0;
}
```

滚动数组优化版本：

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1001, K = 21;
int dp[N];
int a[N], w[N][K], c[N][K];

int main() {
    int n, C;
    
    cin >> n >> C;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= a[i]; j++) {
            cin >> w[i][j] >> c[i][j];
        }
    }

    memset(dp, 0, sizeof dp);
    for(int i = 1; i <= n; i++) {
        for(int k = 1; k <= a[i]; k++)
            for(int j = C; j >= c[i][k]; j--) {
                dp[j] = max(dp[j], dp[j - c[i][k]] + w[i][k]);
            }
        }
    }
    cout << dp[n][C];

    return 0;
}
```

### 变式2-多重背包(CSP-J+难度)

{% note yellow fa-lightbulb %}
__变式点__：加入 __数量__ 概念，每个物品可以选多个。
{% endnote %}

{% notel default fa-pen 问题描述 %}
有 $n$ 种物品，给定这些物品的重量 $c_i$ 、价值 $w_i$ $(i \in [1,n])$ 和数量 $a_i$，求在背包大小为 $C$ 时能装的最大价值。
{% endnotel %}

再以0/1背包的思路思考，只要：

- 添加一层循环枚举每个物品的数量 $k$ 即可。
- 状态转移：$dp_{i,j} = \max(dp_{i-1,j},dp_{i-1,j-c_i}+w_i) \rightarrow dp_{i,j} = \max(dp_{i-1,j},dp_{i-1,j-c_i \cdot k}+ w_i \cdot k)$

#### 代码实现

##### 朴素暴力

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1001;
int dp[N];
int a[N], w[N], c[N];

int main() {
    int n, C;
    
    cin >> n >> C;
    for(int i = 1; i <= n; i++) cin >> w[i] >> c[i] >> a[i];

    memset(dp, 0, sizeof dp);
    for(int i = 1; i <= n; i++) {
        for(int j = c[i]; j <= C; j++) {
            //注意：k<=a[i]和j/c[i]的最小值
            for(int k = 1; k <= min(a[i], j / c[i]); k++) {
                dp[j] = max(dp[j], dp[j - c[i] * k] + w[i] * k);
            }
        }
    }
    cout << dp[n][C];

    return 0;
}
```

##### 二进制优化

注意到，最内层的循环`for(int k = 1; k <= min(a[i], j / c[i]); k++)`是将 $k$ 一个一个地枚举出来，组合出放入背包后的 $a_i$ 种情况。我们可以将 $a_i$ 拆分成二进制形式 $a_i = 2^{0}{b_0}+2^{1}{b_1}+\ldots+2^{n}{b_n}+p$（$p$为一个$1 \leq p < a_i$ 的整数，$b \in \{0,1\}$）。其实就相当于将 $a_i$ 个 $i$ 物品拆分成 $log_2a_i$ 个不同物品（每个物品的重量和价值都乘上 $2^x$），这样就可以通过 $log_2a_i$ 个物品组合出每种情况而使 $k$ 不超过 $a_i$。

例如，对于 $a_i=15$ 的情况，我们可以分成 $\{1,2,4,8\}$ 四个系数的 $i$ 物品，想要选择 $1 \sim 15$ 之间任意多个 $i$ 物品，只需从中挑选若干个组合起来即可。

此时，问题就转换成了0/1背包问题，只要将二进制拆分后的物品放入0/1背包即可。

所以在进行dp之间将`m[]`数组优化：

```c++
//...
int nW[N], nC[N], nN;
//...
//in main:
nN = 0;
for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= a[i]; j *= 2) { //二进制拆分
        a[i] -= j;
        nC[++nN] = j * c[i];
        nW[nN] = j * w[i]; 
    }
    if(a[i]) {  //二进制拆分后还有余数
        nC[++nN] = a[i] * c[i];
        nW[nN] = a[i] * w[i];   
    }
}
```

之后只要0/1背包即可：

```c++
for(int i = 1; i <= nN; i++) {
    for(int j = C; j >= nC[i]; j--) {
        dp[j] = max(dp[j], dp[j - nC[i]] + nW[i]);
    }
}
```

## 2.序列问题

### 1、最长公共子序列(LCS)

{% notel default fa-pen 问题描述 %}
给定序列 $X,Y$，求 $X,Y$ 的最长公共子序列。（注意：不一定连续！）
{% endnotel %}

1. 状态设计：`dp[i][j]`表示在 $X$ 中以第 $i$ 位为结尾、在 $Y$ 中以第 $j$ 位为结尾的LCS
2. 状态转移：
    - 当`X[i]==Y[j]`时，说明LCS可以延长一位，即：`dp[i][j] = dp[i-1][j-1]+1`
    - 否则，上个公共子序列到 $i - 1$ 结束，则LCS从 $X,Y$中的上一位分别继承，为 `dp[i-1][j]` 和 `dp[i][j-1]`的最大值，即：`dp[i][j] = max(dp[i-1][j], dp[i][j-1])`
3. 代码设计：

```c++
//n 为 X 长度， m 为 Y 长度
for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
        if(X[i] == Y[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
        else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
}
```

### 2、最长递增子序列(LIS)

{% notel default fa-pen 问题描述 %}
给定序列 $X$，求 $X$ 的最长递增子序列。（注意：不一定连续！）
{% endnotel %}

1. 状态设计：`dp[i]` 表示第 $i$ 位为结尾的LIS
2. 状态转移：可以发现，当$a_j < a_i$ 时，对于 $1 \leq j < i$，$dp_i = max{dp_j} + 1$，即从尾部追加。

```c++
for(int i = 1; i <= n; i++) {
    int maxj = 0;
    for(int j = 1; j < i; j++) {
        if(dp[maxj] < dp[j] && dp[j] < dp[i]) maxj = j;
    }
    dp[i] = dp[maxj] + 1;
}
```

### 3、最小划分

{% notel default fa-pen 问题描述 %}
给定集合 $S$，将它分成 $S_1$ 和 $S_2$ 两部分，使 $S_1$ 中的数字和与 $S_2$ 中的数字和之差的绝对值最小。
{% endnotel %}

我们可以对问题进行转换，可以发现：当差值为 $0$ 时，一定最优。我们只需要计算出大集合的数据之和 $s$，构建一个容量为 $s \div 2$(差值为 $0$) 的0/1背包，将集合中的每个数字看作物品，进行0/1背包求解得到 $r$。此时，$|r-(s-r)|$ 即为答案。

```c++
//...
const int N = 10001;
int dp[N][N], c[N];
//...
//in main:
//输入
int n, s = 0;
cin >> n;
for(int i = 1; i <= n; i++) {
    cin >> c[i];
    s += c[i];
}
for(int i = 1; i <= n; i++) {
    for(int j = c[i]; j <= s / 2; j++) {   //价值和体积相等
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + c[i]);
    }
}
cout << abs(dp[n][s/2] - (r - dp[n][s/2])) << endl;
```

## 3. 字符串变换（编辑距离）

{% notel default fa-pen 问题描述 %}
给定字符串 $a,b$，求通过 __插入、替换、删除__ 三种操作要对 $a$ 进行多少次操作使之与 $b$ 相同。
{% endnotel %}

1. 状态设计： `dp[i][j]` 表示将 $a_1 \sim a_i$ 变换成 $b_1 \sim b_j$ 需要多少次，`dp[lena][lenb]`即为答案。
2. 状态转移：
    - 当 $a_i = b_i$ 时，本位不需要变换，$dp_{i,j} = dp_{i-1,j-1}$
    - 否则，分别进行 __插入、替换、删除__，取操作数的最小值：$dp_{i,j} = \min(dp_{i-1,j}, dp_{i,j-1}, dp_{i-1,j-1})+1$。（`dp[i-1][j]+1`表删除，`dp[i][j-1]+1`表示插入，`dp[i-1][j-1]+1`表示替换，详见“注”）。

注：

- 插入操作：`liv` $\to$ `live`，相当于使 $a_{1 \sim i}$（变换后长度 $-$） 与 $b_{1 \sim j-1}$ 相等，再在 $a_{j}$ 上插入 $b_{j}$，此时 $a_{1 \sim i}$ 与 $b_{1 \sim j}$ 相等，步数为 $dp_{i,j-1} + 1$
- 替换操作：`livc` $\to$ `live`，相当于使 $a_{1 \sim i-1}$ 与 $b_{1 \sim j-1}$ 相等，再在两 __子串__ 末尾同时插入 $b_{j}$，步数为 $dp_{i-1,j-1} + 1$
- 删除操作：`lived` $\to$ `live`，相当于使 $a_{1 \sim i-1}$（变换后长度 $+$） 与 $b_{1 \sim j}$ 相等，将 $a_{j+1}$ 删去，步数为 $dp_{i-1,j} + 1$ 。

```c++
for(int i = 0; i < a.size(); i++) {
    for(int j = 0; j < b.size(); j++) {
        int realI = i + 1, realJ = j + 1;
        if(a[realI] == b[realJ]) dp[realI][realJ] = dp[realI - 1][realJ - 1];
        else dp[realI][realJ] = min(dp[realI - 1][realJ], dp[realI][realJ - 1], dp[realI - 1][realJ - 1]) + 1;
    }
}
```