---
title: Bessie Slows Down
date: 2025/01/04 19:53:21
tags:
    - C++
    - 模拟
---

## 题目描述

Bessie正在跑步，出发时她以 $1$ 米/秒的速度跑步。然而随着体能的下降，她会不断调整她的跑步速度。第 $1$ 次调整后，Bessie的速度会降为 $\frac{1}{2}$ 米/秒，第 $2$ 次调整后，她的速度降为 $\frac{1}{3}$ 米/秒，以此类推。第 $x$ 次调整速度后，速度降为 $\frac{1}{x+1}$ 米/秒。

有两种事件可以导致Bessie调整速度，事件格式如下：

`T 17`：表示在Bessie出发17秒后做一次速度调整。

`D 10`：表示Bessie出发10米后调整速度。

`T`事件和`D`事件都有多条，Bessie会按照事件发生的先后顺序调整速度，每出现一次事件都会导致Bessie调整一次速度，如果2个事件同时发生，会导致Bessie调整2次速度。

给定 $N$ 个事件（$1 \leq N \leq 10000$），请计算Bessie行走 $1000$ 米所需要的时间，将答案四舍五入取整输出。

## 输入格式

第 $1$ 行：一个整数 $N$，表示事件的数量。

接下来 $N$ 行：每行一个 T x 或者 D y，T x 表示出发 x 秒时做一次速度调整，D y 表示出发 y 米时做一次速度调整。$1 \leq x \leq 10^7$（且数据保证时间都是 $\leq$ 走完1000米的时间的），$1 \leq y \leq 1000$。

## 输出格式

一行：一个整数，表示Bessie走完一千米所需的时间，如果所需时间不是整数，则四舍五入向上取整。

## 输入输出样例

### 输入样例1

```plaintext
2
T 30
D 10
```

### 输出样例1

```plaintext
2970
```

## 题解

### 题目分析

模拟即可。

{% note yellow fa-warning %}
注：`round()`返回的是`double`，可能会输出 __科学计数法__。
{% endnote %}

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 10001;
vector<ll> D,T; 
ll n;
double d = 0.0, t = 0.0;

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) {
        char c; ll x;
        cin >> c >> x;
        if(c == 'D')  D.push_back(x);
        else T.push_back(x);
    }
    D.push_back(1000);
    sort(D.begin(), D.end());
    sort(T.begin(), T.end());
    auto i = D.begin(), j = T.begin();
    ll fmv = 1;
    while(i != D.end() || j != T.end()) {
        bool isT = false;
        if(j != T.end()) isT = ((*j) < t+((*i)-d)*fmv);
        if(isT) {
            d += ((*j)-t) / fmv;
            t = *j;
            j++;
        } else {
            t += ((*i) - d) * fmv;
            d = *i;
            i++;
        }
        fmv++;
    }
    cout << (ll)round(t) << endl;
    return 0;
}
``` 