---
title: CSP-S日常测试(240907)
date: 2024-09-07 21:56:48
tags: C++
categories:
    - [考试,CSP,S]
---

# [路边的水沟](https://www.luogu.com.cn/problem/P2265)

## 题目背景
某市有一个巨大的水沟网络，可以近似看成一个 $n \times m$ 的矩形网格，网格的每个格点都安装了闸门，我们将从水沟网络右下角的闸门到左上角的闸门的一条路径称为水流。

## 题目描述
现给定水沟网的长和宽，求该水沟网中所有只包含向左和向上移动的水流数量。

## 输入格式
输入共 $1$ 行，包含两个整数 $n$ 和 $m$。

## 输出格式
输出一个数字 $ans$，即水流的数量。由于答案可能很大，请输出答案对 $10^9 + 7$ 取模的结果。

## 样例 #1

### 样例输入 #1
```
3 5
```

### 样例输出 #1
```
56
```

## 提示
对于 $30%$ 的数据，$1 \leq m,n \leq 10$ 。

对于 $50%$ 的数据，$1 \leq m,n \leq 10^3$。

对于 $80%$ 的数据，$1 \leq m,n \leq 5 \times 10^4$。

对于 $100%$ 的数据，$1 \leq m,n \leq 10^6$。

## 答案
{% folding green::答案 %}
题目翻译：在$n \times m$的网格中，求$(n,m) \rightarrow (1,1)$的路线条数。

没有思路，先尝试暴力搜索（$30pts$）。

```c++
int ans = 0;
void Dfs(int x, int y) {
    if(x == n && y == m) ans++;
    if(x < n) Dfs(x + 1, y);
    if(y < m) Dfs(x, y + 1);
}

//int main() {
//...
//  Dfs(0,0);
//...
//}
```

上最简单的优化：记忆化，时间复杂度$\mathbf{O}(n^2)$。（$50pts$）

```c++
long long dp[1001][1001];
int Dfs(int x, int y) {
    if(x == n && y == m) return 1;
    if(dp[x][y] != 0) return dp[x][y];
    long long ans = 0;
    if(x < n) ans += Dfs(x + 1, y);
    if(y < m) ans += Dfs(x, y + 1);
    ans %= (1e9 + 7);
    return dp[x][y] = ans;
}
```

再进一步，我们可以将水的流向看成一个“操作序列”，每一位都存储着一个命令：“向上”或“向右”。

<video controls src="/videos/cspstest240907-1.mp4" title="图解"></video>

将路径平移到边上，可以发现，“向右”操作的次数就是 $m$，“向上”操作的次数就是 $n$，“操作序列”的长度是 $n+m$。

现在，问题转化成了求“向上”操作在“操作序列”中的组合数，即：$C^n_{n+m}$

但是，题目要求求 $C^m_{n+m} \mod (10^9 + 7)$ 呀，直接算 $C^m_{n+m}$ 显然爆`long long`。如果把 $C^m_{n+m}$ 展开成 $\frac{(n+m)!}{n!m!}$，由于是除法，还是爆`long long`，怎么办呢？

下面引入 __逆元__：对于 $a$ 和 $p$（$a$ 和 $p$ 互素），若 $a \cdot b \mod p ≡ 1 (\mod p)$ ，则称 $b$ 为 $a \mod p$的逆元。

那这个逆元有什么用呢？试想一下求 $\frac{a}{b} \mod p$ ，如果你知道 $b \mod p$ 的逆元是 $c$，那么就可以转变成 $\frac{a}{b} \mod p = a \cdot c \mod p = (a \mod p)(c \mod p) \mod p$

根据 __费马小定理__：对于 $a$ 和素数 $p$ ，满足$a^{p-1} \mod p ≡ 1$

接着因为 $a^{p - 1} = a^{p - 2} \cdot a$，所以有 $a^{p-2} \cdot a \mod p ≡ 1 (\mod p)$对比逆元的定义可得，$a^{p-2}$ 是 $a$ 的逆元。

代入原问题，就是：$\frac{(n+m)!}{n!m!} = (m+1)! \cdot \cdots \cdot (n+m) \cdot {n!}^{10^9+5} \mod {10^9+7}$

注意，要用到快速幂。

```c++
#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

typedef unsigned long long ull;

ull FastPow(ull a, ull b) {
    ull ret = 1;
    while(b) {
        if(b & 1) ret = (ret * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ret;
}

int main() {
    freopen("drain.in", "r", stdin);
    freopen("drain.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    
    int fenzi = 1, fenmu = 1;   //分子和分母，约分后为：(m+1)*...*(n+m)/n!
    for(int i = m + 1; i <= n + m; i++) fenzi = (fenzi * i) % mod;  //分子是(n+m)!
    for(int i = 2; i <= n; i++) fenmu = (fenmu * i) % mod;          //分母是n!m!
    
    cout << fenzi * FastPow(fenmu, mod - 2) % mod << endl;

    return 0;
}
```

{% endfolding %}