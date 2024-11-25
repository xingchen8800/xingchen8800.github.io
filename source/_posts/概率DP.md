---
title: 概率DP
date: 2024-11-12 21:51:29
tags: CSP提高组
excerpt: 概率DP
---

# 随机变量

## 引入

如代码：
```c++
int a = 1;
```
此时 $a$ 是一个 __确定变量__，其值是 __可推算的__。

如代码：
```c++
int a;
```
此时 $a$ 是一个 __随机变量__。

## 例子

- 设 $X$ 表示投一次骰子的结果，则 $X$ 是一个 __随机变量__，有 ${1,2,3,4,5,6}$ $6$ 种取值。
- 设 $Y$ 表示投 $10$ 次骰子的点数之和，那么 $Y$ 也是一个 __随机变量__。
- 设 $Z$ 表示一个随机生成的长度为 $5$ 的排列中的逆序对数，则 $Z$ 也是一个 __随机变量__。

# 概率

## [钉子和小球](https://www.luogu.com.cn/problem/P5750)

题面请看链接

设 $f_{i,j}$ 表示小球来到 $(i,j)$ 的概率。

- 当 $(i,j)$ 上有钉子，小球会向两边走：
    - $\frac{f_{i,j}}{2}$ 累加给 $f_{i+1,j}$ （即左下的位置）
    - $\frac{f_{i,j}}{2}$ 累加给 $f_{i+1,j+1}$ （即右下的位置）
- 否则，小球会往下掉：
    - $f_{i,j}$ 全部累加给 $f_{i+2,j+1}$ （即正下方的位置）

{% note red fa-link %}
~~本题难点完全就是封装分数类！~~
{% endnote %}

```c++
#include <bits/stdc++.h>
using namespace std;

class Frac {
private: 
    long long a, b;   //a/b
public:
    Frac() : a(0), b(1) { }
    Frac(long long x, long long y) : a(x), b(y) { }
    Frac(const Frac &x) { this->a = x.a; this->b = x.b; }

    long long gcd(long long x, long long y) {
        return y == 0 ? x : gcd(y, x % y);
    }
    long long lcm(long long x, long long y) {
        return x / gcd(x, y) * y;
    }
    void Simple() {
        if(!a) {
            b = 1;
            return ;
        }
        long long x = gcd(a, b);
        a /= x, b /= x;
    }
    long long A() { return a; }
    long long B() { return b; }

    Frac operator*(const Frac &x) {
        Frac newFrac(this->a * x.a, this->b * x.b);
        newFrac.Simple();
        return newFrac;
    }
    Frac& operator+=(Frac x) {
        long long l = lcm(this->B(), x.B());
        long long newA = this->a * (l / this->b) + x.a * (l / x.b);
        long long newB = l;
        long long g = gcd(newA, newB);
        this->a = newA / g;
        this->b = newB / g;
        return *this;
    }

    friend ostream& operator<<(ostream& out, Frac &x) {
        out << x.A() << "/" << x.B();
        return out; 
    }
};

Frac f[1001][1001];
char mp[1001][1001];

int main() {
    long long n, m;
    cin >> n >> m;
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= i; j++) {
            cin >> mp[i][j];
        }
    }
    f[1][1] = Frac(1, 1);

    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= i; j++) {
            if(mp[i][j] == '*') {
                f[i + 1][j] += f[i][j] * Frac(1, 2);
                f[i + 1][j + 1] += f[i][j] * Frac(1, 2);
            } else {
                if(i + 2 <= n + 1) f[i + 2][j + 1] += f[i][j];
            }
        }
    }

    f[n+1][m+1].Simple();
    cout << f[n+1][m+1];
    return 0;
}
```

# 期望 ($E(X)$)

对于一个随机变量 $X$，我们可以通过列表的方法写出这个随机变量的取值以及该取值的可能性。如下表：

| $X$   | $1$   | $2$   | $3$   | $4$   |
|   -   |   -   |   -   |   -   |   -   |
| $P_i $ | $20\%$ | $40\%$ | $10\%$ | $30\%$ |

__定义： $X$ 的期望 $E(X) = \sum_{i}{P_i \cdot i}$__

例：上表中 $X$ 的期望为： $1 \times 0.2 + 2 \times 0.4 + 3 \times 0.1 + 4 \times 0.3 = 2.5$

{% notel orange fa-book 期望的直观理解 %}
我们可以把随机变量看作是一次开箱，观测到的随机变量的具体值看作开箱的收益，那么期望其实就是在问你：“如果你能开很多次箱，你的平均收益是多少？”
{% endnotel %}

__性质：期望具有线性性。即若 $X,Y$ 为两个随机变量，则：__
$$ 
E(X+Y) = E(X) + E(Y)
$$

{% notel orange fa-book 期望的性质的直观理解 %}
$E(X+Y)$ 就相当于同时开两个箱子，收益自然等于单独开两个箱子之和。
{% endnotel %}

