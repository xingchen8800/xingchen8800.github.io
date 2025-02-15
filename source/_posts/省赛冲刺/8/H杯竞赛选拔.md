---
title: H杯竞赛选拔
date: 2025-02-08 18:15:35
tags:
    - C++
---

## 题目描述

某大学计算机系准备组织学生参加 $H$ 杯竞赛，比赛由 $2$ 人组队的形式参赛。某大学计算机系刚好有 $2$ 个班，每个班有 $N$ 名学生，系主任 $A$ 博士希望每支队伍的 $2$ 个人来自不同的班级。这样的话总共有 $N^2$ 种不同的组队方案。为了让选拔更加的客观公正，$A$ 博士组织了一次编程比赛。现在$A$ 博士拿到了每个学生的分数 $S_{i,j}$（ $0 \leq S_{i,j} \leq 10^8$ ）。他想知道总分排名前N的分组方案中每个分组的得分（相同得分也占用不同的名次）。

## 输入格式

第1行：一个整数 $N$（ $1 \leq N \leq 10^5$ )；

第2行：$N$ 个空格分隔的整数，表示 $1$ 班 $N$ 个学生的分数。

第3行：$N$ 个空格分隔的整数，表示 $2$ 班 $N$ 个学生的分数。

## 输出格式

一行：$N$ 个空格分隔的整数，表示总分排名前 $N$ 位的分组的总分，按照从大到小的顺序输出。

## 输入输出样例

### 输入样例1

```plaintext
3
1 2 3
1 2 3
```

### 输出样例1

```plaintext
6 5 5
```

## 题解

令 $1$ 班各人的分数组成 $\{a_n\}$，$2$ 班的组成 $\{b_n\}$

题目要求我们选择总分最大的方案，无论从贪心的角度还是从别的什么角度，都应该先想到对 $\{a_n\}$ 和 $\{b_n\}$ 从小到大排序。

然后，我们尝试暴力硬解，自然会想到排出所有的方案：

<!-- ![图1](/images/省赛冲刺/8/1.png) -->

$$
\begin{matrix} 
a_1+b_1 & a_1+b_2 & \cdots & a_1+b_n \\
a_2+b_1 & a_2+b_2 & \cdots & a_2+b_n \\
\vdots     & \vdots      & \ddots & \vdots \\
a_n+b_1 & a_n+b_2 & \cdots & a_n+b_n
 \\ \end{matrix}
$$

由于$\{a_n\}$ 和 $\{b_n\}$ 已经有序，所以每行从左到右单调递减，每列从上到下单调递减。

我们可以用一个优先队列来维护一个区域，使最大值落在这个区域中。

$$
\begin{matrix} 
\color{green}{a_1+b_1} & a_1+b_2 & \cdots & a_1+b_n \\
\color{green}{a_2+b_1} & a_2+b_2 & \cdots & a_2+b_n \\
\color{green}{\vdots}     & \vdots      & \ddots & \vdots \\
\color{green}{a_n+b_1} & a_n+b_2 & \cdots & a_n+b_n \\
\end{matrix}
$$

因为“每列从上到下单调递减”，所以初始的区域是绿色部分。

因为 $a_1+b_1$ 最大，所以 $a_1+b_1$ 为答案的一部分，可以踢出这个区域。

因为“每行从左到右单调递减”，所以应该选择 $a_1+b_1$ 的右侧第一个 $a_1+b_2$ 加入区域：

$$
\begin{matrix} 
{a_1+b_1} & \color{green}{a_1+b_2} & \cdots & a_1+b_n \\
\color{green}{a_2+b_1} & a_2+b_2 & \cdots & a_2+b_n \\
\color{green}{\vdots}     & \vdots      & \ddots & \vdots \\
\color{green}{a_n+b_1} & a_n+b_2 & \cdots & a_n+b_n \\
\end{matrix}
$$

推理至此，我们考虑每次踢出区域中的最大值并将其加入答案，然后将其的右侧第一个加入区域。作 $n$ 次这种操作即可。

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 100001;
ll a[N], b[N], n;

struct triplet {
    ll val, i, j;
    bool operator<(const triplet &rhs) const {
        return val < rhs.val;
    }
};
priority_queue<triplet, vector<triplet>> pq;

ll res[N];

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) cin >> a[i];
    for(ll i = 1; i <= n; i++) cin >> b[i];
    sort(a + 1, a + n + 1, greater<ll>());
    sort(b + 1, b + n + 1, greater<ll>());

    for(ll i = 1; i <= n; i++) pq.push({a[i] + b[1], i, 1});

    for(ll i = 1; i <= n; i++) {
        auto t = pq.top(); pq.pop();
        res[i] = t.val;
        if(t.j + 1 <= n) 
            pq.push({a[t.i] + b[t.j + 1], t.i, t.j + 1});
    }
    
    for(ll i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    return 0;
}
```