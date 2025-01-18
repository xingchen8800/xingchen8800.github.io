---
title: Balanced Team
date: 2025-01-04 20:15:10
tags:
    - C++
    - 搜索
    - 剪枝
    - 全排列
---

## 题目描述

FJ有 $12$ 头奶牛，每头奶牛都有一个技能值 $s[i]$（$1 \leq s[i] \leq 1000000$）。FJ要将他们分成 $4$ 组，每组 $3$ 头奶牛。每组奶牛的技能值等于该组内 $3$ 头奶牛的技能值之和。FJ希望技能值最大分组和技能值最小的分组之间的差距尽量的小。请计算这个最小值。

## 输入格式

共 $12$ 行，每行一个正整数，表示一头奶牛的技能值。

## 输出格式

一个整数，表示技能值最大的分组和技能值最小分组的技能值差值的最小值。

## 输入输出样例

### 输入样例1

```plaintext
1
2
3
4
5
6
7
8
9
10
11
12
```

### 输出样例1

```plaintext
1
```

### 样例说明

按照：$\{12，1， 7\}$，$\{9， 8， 3\}$， $\{10， 5， 4\}$ 和 $\{11, 2, 6\}$ 的方式分组，最大值为 $20$，最小值为 $19$，差值为 $1$。

## 题解

### 题目分析

首先，我们考虑如何枚举每种分组：我们可以通过全排列的方式，每 $3$ 个一组来分组。

其次，我们考虑如何优化：由于 $n=12$，所以 $O(n!)$ 的搜索 $100\%$ 超时。

我们有两种优化的思路：

1. 组内去重：由于题目只是要求分组，所以无论如何改变组内元素的顺序，组的意义不变，例如 $\{1,2,3\}$ 和 $\{1,3,2\}$ 的意义是相同的。那么，我们可以让组内元素统一 __升序__ 排序。
2. 组间去重：如果两组间调换位置，那么最终的结果不变，例如 $\{1,2,3\},\{4,5,6\}$ 和 $\{4,5,6\},\{1,2,3\}$ 的意义相同。故可以让组头统一按 __升序__ 排序。

最后，由于两个升序规则，第一头牛只能选 $1$ 号，可以先固定。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 15, INF = 1e18;

ll s[N], plan[N], ans = LLONG_MAX, vis[N] = {false};

ll Calc() {
    ll mins = LLONG_MAX, maxs = LLONG_MIN, sum = 0;
    for(ll i = 1; i <= 12; i++) {
        sum += s[plan[i]];
        if(i % 3 == 0) {
            mins = min(mins, sum);
            maxs = max(maxs, sum);
            sum = 0;
        }
    }
    return maxs - mins;
}

void dfs(ll cur) {
    if(cur > 12) {
        ans = min(ans, Calc());
        return;
    }
    for(ll i = (cur % 3 == 1 ? plan[cur - 3] : plan[cur - 1]) + 1; i <= 12; i++) {
        if(vis[i]) continue;
        plan[cur] = i;
        vis[i] = true;
        dfs(cur + 1);
        vis[i] = false;
    }
}

int main() {
    for(ll i = 1; i <= 12; i++) cin >> s[i];
    plan[1] = 1; vis[1] = true;
    dfs(2);
    cout << ans << endl; 
    return 0;
}
```
