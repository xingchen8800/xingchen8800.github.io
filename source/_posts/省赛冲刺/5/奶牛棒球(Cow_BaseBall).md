---
title: Cow Baseball
date: 2025-01-04 18:55:30
tags:
    - C++
    - 枚举(优化)
    - 二分答案
---

## 题目描述

FJ的 $N$ 头奶牛（$3 \leq N \leq 1000$）站成了一行，她们正在为即将到来的奶牛传球大赛练习传球。FJ会从中选出三头牛 $X$，$Y$，$Z$（$X$ 的位置 $<Y$ 的位置 $<Z$ 的位置）来练习传球，要求 $Y$ 到 $Z$ 的距离要大于等于 $X$ 到 $Y$ 的距离，同时小于等于 $X$ 到 $Y$ 距离的两倍。

FJ想知道有多少种不同的组合（三头牛中只要有一头不相同，就认为是不同的组合）满足他的要求。

## 输入格式

第 $1$ 行：一个整数 $N$，表示奶牛的数量。

接下来 $N$ 行：每行一个整数，其中第 $i+1$ 行的整数 $p_i$，表示第 $i$ 头牛的位置。（每头牛的位置都不相同 $0 \leq p_i \leq 100000000$）。

## 输出格式

一行：一个整数，表示FJ要求的奶牛组合数量。

## 输入输出样例

### 输入样例1

```plaintext
5
3
1
10
7
4
```

### 输出样例1

```plaintext
4
```

## 说明

【样例说明】

$4$ 组满足条件的奶牛的位置分别是：$1-3-7，1-4-7，4-7-10，1-4-10$

## 题解

### 暴力方法

$O(n^3)$ 的 $TLE$ 写法。

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 1001;
ll n, a[N];

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    
    ll ans = 0;
    for(ll x = 1; x <= n; x++) {
        for(ll y = x + 1; y <= n; y++) {
            for(ll z = y + 1; z <= n; z++) {
                ll d1 = a[y] - a[x];
                ll d2 = a[z] - a[y];
                if(d2 >= d1 && d2 <= 2 * d1) ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

### 二分法优化

注意到：暴力法中枚举了所有符合条件的 $k$。我们是不是可以直接找到 $k$ 的范围呢？

$$
dis_{X,Y} \leq dis_{Y,Z} \leq 2dis_{X,Y}
$$

$$
a_y - a_x \leq a_z - a_y \leq 2a_y - 2a_x
$$

不妨设 $a_y - a_x = dis$，有：

$$
dis \leq a_z - a_y \leq 2dis
$$

$$
a_y + dis \leq a_z \leq a_y + 2dis
$$

显然：经过排序的数组可以通过二分查找上下界来确定 $k$ 的范围。

$O(n^2 \log{n})$

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 1001;
ll n, a[N];

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    
    ll ans = 0;
    for(ll x = 1; x <= n; x++) {
        for(ll y = x + 1; y <= n; y++) {
            ll dis = a[y] - a[x];
            ll mind = a[y] + dis, maxd = a[y] + 2 * dis;
            ans += upper_bound(a + 1, a + n + 1, maxd) - 
                   lower_bound(a + 1, a + n + 1, mind);
        }
    }
    cout << ans << endl;
    return 0;
}
```
