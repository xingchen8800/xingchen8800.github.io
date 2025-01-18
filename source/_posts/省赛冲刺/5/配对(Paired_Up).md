---
title: Paired Up
date: 2025-01-04 18:04:33
tags:
    - C++
    - 贪心
---

## 题目描述

FJ有 $M$ 头奶牛 ($M <= 10^9$ 且 $M$ 是偶数)。FJ要把这 $M$ 头奶牛分为 $M \div 2$ 组进行挤奶。每组奶牛都可以独立挤奶，也就是说这 $M \div 2$ 组奶牛可以同时开始挤奶。每组奶牛的挤奶时间等于该组两头奶牛产奶量之和。FJ想知道如何安排分组才能让所有分组挤奶完成的最短时间，输出这个最小值。

## 输入格式

第1行：一个空格分隔的整数 $N(1 \leq N \leq 100000)$。

接下来N行：每行两个空格分隔的正整数 $X$ 和 $Y$ ，表示有 $X$ 头牛的产奶量为 $Y$, 所有 $X$ 的总和等于M。

## 输出格式

一行：一个整数，表示所有奶牛产奶完成时间的最小值。

## 输入输出样例

### 输入样例1

```
3
1 8
2 5
1 2
```

### 输出样例1

```
10
```

## 题解

最大值最小化问题。

我们可以用 __最大的配最小的__ 的贪心策略解决。需要注意特判。

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 100001;
ll n, m, sum = 0;
struct Info {
    ll x, y;
}; vector<Info> v;

int main() {
    cin >> n;
    for(ll i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        v.push_back({x, y});
    }
    sort(v.begin(), v.end(), [=](const Info&a, const Info& b) {return a.y < b.y;});
    auto i = v.begin(), j = v.end() - 1;
    ll sum = LLONG_MIN;
    while(i != j) {
        sum = max(j->y + i->y, sum);
        if(i->x == j->x) {i->x = j->x = 0; i++, j--;}
        else if(i->x > j->x) {i->x -= j->x; j->x = 0; j--;}
        else {j->x -= i->x; i->x = 0; i++;}
    }
    //特判，当只剩最后两种牛时，还要再计算一次
    if(i == j) sum = max(j->y + i->y, sum);
    cout << sum << endl;
    return 0;
}
```