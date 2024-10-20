---
title: CSP-J日常测试(241004aft)
date: 2024-10-04 16:32:12
tags: C++
categories: 
    - [CSP,J,课程]
    - [考试,CSP,J]
excerpt: 相遇、加减法、立方体、日期计算、最强花园
tags: 
    - C++
    - CSP入门组
---

{% note green fa-info %}
本次测试题限制用时 $1000 \rm{ms}$，内存 $256 \rm{MB}$ （第五题 $512 \rm{MB}$）
{% endnote %}

# 一、相遇（meet）

## 题目描述
科科和乐乐相约爬山，初始时科科在距山脚 $x \rm{km}$ 位置，乐乐在距山脚 $y \rm{km}$ 位置，他们约定先集合再一起出发去爬山；科科和乐乐的移动速度相同均为$1 \rm{km/h}$ ，每次移动耗费的能量也相同。

因为体力下降等原因，越往后耗费的能量越多，具体来说：移动第$1 \rm{km}$ 需要花费 $1 \rm{kj}$ 能量，移动第 $2 \rm{km}$ 需要花费 $2 \rm{kj}$能量，移动第 $3 \rm{km}$ 需要花费 $3 \rm{kj}$能量，依次类推。

比如科科先前进 $1 \rm{km}$，再后退 $1 \rm{km}$，再前进 $1 \rm{km}$，带来的能量消耗是：$1+2+3=6 \rm{kj}$。

请问科科与乐乐集合所需花费的最少总能量是多少kj？

## 输入格式
输入文件名：`meet.in`

输入两个空格分隔的整数 $x$ 和 $y$，含义如题所述。

## 输出格式
输出文件名：`meet.out`

输出一个整数，表示科科与乐乐相遇集合所需花费的最少总能量。

## 样例

### 样例输入 #1
```
3 4
```

### 样例输出 #1
```
1
```

### 样例输入 #2
```
101 99
```

### 样例输出 #2
```
2
```

## 说明

### 样例#1说明

只需要科科或者乐乐移动 $1 \rm{km}$即可，耗费的能量为 $1 \rm{kj}$。

### 数据范围

对于 $50\%$ 的数据范围：$1 \leq x,y \leq 10^3$；

对于 $100\%$ 的数据范围：$1 \leq x,y \leq 10^7$。

## 题解
{% folding green::题解 %}

~~纯纯水题~~

先求出科科和乐乐的距离 $|x-y|$，然后再将距离平分给科科和乐乐：
- 当$|x-y|$可以整除$2$时，科科和乐乐各走 $\frac{|x-y|}{2}$ ，消耗：$2 \times \sum^{\frac{|x-y|}{2}}_{i=1}{i}$
- 当$|x-y|$不可以整除$2$时，科科和乐乐各走 $⌊\frac{|x-y|}{2}⌋$ 和  $\frac{|x-y|+1}{2}$，消耗：$\sum^{⌊\frac{|x-y|}{2}⌋}_{i=1}{i} + \sum^{\frac{|x-y|+1}{2}}_{i=1}{i}$

考虑如何计算$\sum$：由于所有的 $i$ 构成了一个公差为 $1$ 的等差数列，套用等差数列的求和公式：$S_i = n \cdot a_1 + \frac{n(n-1) \cdot d}{2}$，有 $S_i = \frac{n(n+1)}{2}$，即：$\sum^{⌊\frac{|x-y|}{2}⌋}_{i=1}{i} = \frac{⌊\frac{|x-y|}{2}⌋ \cdot \frac{|x-y|-1}{2}}{2}$

正解：
```c++
#include <bits/stdc++.h>
using namespace std;

long long kj = 0, x, y;

long long GetRangeSum(long long from, long long to) {
    if(from > to) return 0ll;
    long long sum = to * (to + 1) / 2 - (from - 1) * from / 2;
    return sum;
}

int main() {
    freopen("meet.in", "r", stdin);
    freopen("meet.out", "w", stdout);
    cin >> x >> y;
    long long a = llabs(x - y);

    if(a % 2 == 0) {
        kj = GetRangeSum(1, a / 2) * 2;
    } else {
        kj = GetRangeSum(1, a / 2) + GetRangeSum(1, a / 2 + 1);
    }
    cout << kj << endl;
    return 0;
}
```

{% endfolding %}

# 二、加减法（jjf）

## 题目描述
给定 $x$ 进制下的两个非负整数 $a$ 和 $b$ ，以及一个操作符`op`，当`op`为’+’时计算 $a+b$ ；当op为’-’时计算 $a-b$ 。

## 输入格式
输入文件：`jjf.in`

输入多组数据，每组数据占一行，依次为$x、a、b、$`op`，空格隔开，含义如题目描述。

## 输出格式
输出文件：`jjf.out`

输出多行，对应每组数据的计算结果，结果仍用对应的进制表示。

## 样例

### 样例输入 #1
```
2 110 11 +
2 110 11 -
10 13 13 -
16 ABCDEF FEBCDA +
16 ABCDEF FEBCDA -
```

### 样例输出 #1
```
1001
11
0
1AA8AC9
-52EEEB
```

## 说明

### 数据规模与约定：

对于 $30\%$ 的数据：$2 \leq x \leq 10$ ，$a$ 和 $b$ 不超过 $10$ 位数。

对于 $100\%$ 的数据：$2 \leq x \leq 20$， $a$ 和 $b$ 不超过 $100$ 位数。数据的组数不超过 $100$ 组。对于整数的每一位数码，$10$ 及 $10$ 以上的数码用大写字母表示。且 $a$ 和 $b$ 都不含前导 $0$。

## 题解
{% folding green::题解 %}

高精度计算，套模板。
```c++
#include <bits/stdc++.h>
using namespace std;

int x;
string num1, num2;
char op;
long long _num1[101], _num2[101], _res[101];

//对应表
char table[20] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'};

//是否是字母
bool isAlpha(char c) {
    return (c >= 'A') && (c <= 'Z');
}

int main() {
    freopen("jjf.in", "r", stdin);
    freopen("jjf.out", "w", stdout);
    while(cin >> x >> num1 >> num2 >> op) {
        //清空
        memset(_num1, 0, sizeof _num1);
        memset(_num2, 0, sizeof _num2);
        memset(_res, 0, sizeof _res);

        long long len1 = num1.size(), len2 = num2.size();
        //负数判断
        bool isFu = false;
        long long len = 0;
        //加法
        if(op == '+') {
            for(long long i = len1 - 1; i >= 0; i--) {
                if(isAlpha(num1[i])) _num1[len1 - i - 1] = (int)(num1[i] - 'A') + 10;
                else _num1[len1 - i - 1] = (int)(num1[i] - '0');
            }
            for(long long i = len2 - 1; i >= 0; i--) {
                if(isAlpha(num2[i])) _num2[len2 - i - 1] = (int)(num2[i] - 'A') + 10;
                else _num2[len2 - i - 1] = (int)(num2[i] - '0');
            }
            long long jin = 0;
            while((len < len1) || (len < len2)) {
                _res[len] = _num1[len] + _num2[len] + jin;
                jin = _res[len] / x;
                _res[len] %= x;
                len++;
            }
            if(jin != 0)  _res[len++] = jin;
            while((len > 0) && _res[len - 1] == 0) len--;
        } else {    //减法
            if(num1 < num2) {
                swap(num1, num2);
                isFu = true;
            }
            for(long long i = len1 - 1; i >= 0; i--) {
                if(isAlpha(num1[i])) _num1[len1 - i - 1] = (int)(num1[i] - 'A') + 10;
                else _num1[len1 - i - 1] = (int)(num1[i] - '0'); 
            }
            for(long long i = len2 - 1; i >= 0; i--) {
                if(isAlpha(num2[i])) _num2[len2 - i - 1] = (int)(num2[i] - 'A') + 10;
                else _num2[len2 - i - 1] = (int)(num2[i] - '0'); 
            }
            while((len < len1) || (len < len2)) {
                if(_num1[len] < _num2[len]) {
                    _num1[len] += x;
                    _num1[len + 1]--;
                }
                _res[len] = _num1[len] - _num2[len];
                len++;
            }
            while((len > 1) && _res[len - 1] == 0) len--;
        }
        if(isFu) cout << '-';
        for(int i = len - 1; i >= 0; i--) {
            cout << table[_res[i]];
        }
        cout << endl;
    }
    return 0;
}
```

{% endfolding %}

# 三、立方体（cube）

## 题目描述
如下图所示，是 $2 \times 3$ 的立方体排列方阵。每个立方体上标注的数字就是这个立方体的高度。所有立方体的底面都是边长相同正方形。根据排列的位置和立方体的高度，很容易就可以计算出整个立体图形暴露在外面的表面积。注意计算表面积的时候，相邻的立方体侧面重合的部分是没有暴露在外面的，而每个立方体的上下底面一定是暴露在外面的。

![示意图](https://cdn.luogu.com.cn/upload/image_hosting/4xrj5haw.png)

## 输入格式
输入文件：`cube.in`

第一行输入三个正整数 $m、n、w$，分别表示立方体的行数、列数、底边宽度。

接下来 $m$ 行，每行 $n$ 个正整数，表示每个立方体的高度。

## 输出格式
输出文件：`cube.out`

输出一行一个整数，即整个立体图形的表面积。

## 样例

### 样例输入 #1
```
2 3 4
7 6 2
5 4 5
```

### 样例输出 #1
```
440
```

### 样例输入 #2
```
3 2 3
5 7
4 6
5 2
```

### 样例输出 #2
```
294
```

## 说明

### 数据规模与约定：

对于 $30\%$ 的数据：输入的每个整数在 $[1,10]$ 范围内。

对于 $100\%$ 的数据：输入的每个整数在 $[1,1000]$ 范围内。

## 题解

{% folding green::题解 %}
以样例 #1为例，

![样例#1图](https://cdn.luogu.com.cn/upload/image_hosting/fqyvia5g.png)

黄色的为当前遍历到的长方体，橙色为相邻的长方体，可以发现：


- 对于 $5$，$7$ 比 $5$ 高 $2$，表面积贡献 $2w$
- 对于 $6$，$7$ 比 $6$ 高 $1$，表面积贡献 $w$

以此类推，对于每个长方体，遍历与它相邻的长方体，当遍历到的立方体比它矮时，计算贡献。

```c++
#include <iostream>
#include <cstdio>
using namespace std;
long long sum = 0;
int m, n, w;
int h[1010][1010];

int main() {
    freopen("cube.in", "r", stdin);
    freopen("cube.out", "w", stdout);
    cin >> m >> n >> w;
    sum += n * m * w * w * 2;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> h[i][j];
        }
    }
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(h[i + 1][j] < h[i][j]) sum += (h[i][j] - h[i + 1][j]) * w;   //右
            if(h[i - 1][j] < h[i][j]) sum += (h[i][j] - h[i - 1][j]) * w;   //左
            if(h[i][j + 1] < h[i][j]) sum += (h[i][j] - h[i][j + 1]) * w;   //上
            if(h[i][j - 1] < h[i][j]) sum += (h[i][j] - h[i][j - 1]) * w;   //下
        }
    }
   
    cout << sum << endl;
    return 0;
}
```
{% endfolding %}

# 四、日期计算（cal）

## 题目描述
有一类节日的日期并不是固定的，而是以“$a$ 月的第 $b$ 个星期 $c$”的形式定下来的，比如说母亲节就定为每年的五月的第二个星期日。

现在，给你 $a,b,c$ 和 $y_1,y_2$，希望你输出从公元 $y_1$ 年到公元 $y_2$ 年间的每年的 $a$ 月的第 $b$ 个星期 $c$ 的日期。

为了方便你推算，已知 $1850$ 年 $1$ 月 $1$ 日是星期二。

## 输入格式
输入文件名：`cal.in`

输入包含恰好一行，有五个整数 $a,b,c,y_1,y_2$。

其中 $c=1,2,\cdots,6,7$分别表示星期一、二、...... 、六、日。

## 输出格式
输出文件名：`cal.out`

对于 $y_1$ 和 $y_2$ 之间的每一个年份，包括 $y_1$ 和 $y_2$，按照年份从小到大的顺序输出一行。

如果该年的 $a$ 月第 $b$ 个星期 $c$ 确实存在，则以 `yyyy/mm/dd` 的格式输出，即输出四位数的年份，两位数的月份，两位数的日期，中间用斜杠`/`分隔，数不足时前补零。

如果该年的 $a$ 月第 $b$ 个星期 $c$ 并不存在，则输出 `none`。

## 样例

### 样例输入 #1
```
5 2 7 2014 2015
```

### 样例输出 #1
```
2014/05/11
2015/05/10
```

## 说明

### 【数据范围】

对于 $100\%$ 的数据：
$$
1 \leq a \leq 12，1 \leq b \leq 5，1 \leq c \leq 7，1850 \leq y_1,y_2 \leq 2050
$$

## 题解
{% folding green::题解 %}
纯纯模拟题。

模拟什么呢？模拟翻日历。

计算第 $i$ 年 $a$ 月 $1$ 日的天数，然后计算第 $i$ 年 $a$ 月的第一个星期 $c$，往后推 $b$ 周，判断是否超出第 $i$ 年 $a$ 月的天数。

```c++
#include <iostream>
using namespace std;

int a, b, c, y1, y2;
unsigned long long days;
int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isRun(int x) {
    return (x % 400 == 0) || ((x % 4 == 0) && (x % 100 != 0));
}

unsigned long long GetDay(int year) {
    unsigned long long result = 0;
    for(int i = 1850; i < year; i++) {
        result += 365 + isRun(i);
    }
    for(int i = 1; i < a; i++) {
        if(i == 2) result += isRun(year);
        result += month[i];
    }
    return result;
}

int main() {
    freopen("cal.in", "r", stdin);
    freopen("cal.out", "w", stdout);
    cin >> a >> b >> c >> y1 >> y2;

    for(int i = y1; i <= y2; i++) {
        unsigned long long toA_1 = GetDay(i);   //从1850/1/1到i/a/1
        unsigned long long weekDay = (2 + toA_1) % 7; //i/a/1是星期weekDay。
        unsigned long long toA_1stC = (c - weekDay + 7) % 7 + 1;    //i/a第一个星期c的日期
        toA_1stC += (b - 1) * 7;    //往后推b-1个星期
        unsigned long long daysInA = month[a] + (a == 2 && isRun(i));   //i/a的总天数
        if(daysInA >= toA_1stC) {
            printf("%04d/%02d/%02lld\n", i, a, toA_1stC);
        } else cout << "none\n";
    }
    return 0;
}
```
{% endfolding %}

# 五、最强花园(garden) 

## 题目描述
科丁博士最近在挑战世界吉尼斯记录，打造一个最强花园。他是这样设计他的花园的，一开始他种植了 $n$ 棵向日葵，第 $i$ 棵向日葵的原始高度是 $h_i$ ，并且每棵向日葵每天都在生长，第 $i$ 棵向日葵每天的生长高度是 $a_i$。科丁博士每天都在检测着这 $n$ 棵向日葵的高度，他希望这些向日葵某一天能够达到一个理想状态，这个理想状态就是对于某棵向日葵 $i$，刚好有 $t_i$ 棵向日葵比它高，每棵向日葵都有这样的一个期望值 $t_i$，这 $n$ 棵向日葵的期望值构成了一个 $t$ 序列，$t$ 序列的值各不相同，且刚好是 $0$ 到 $n-1$ 中的这 $n$ 个数。请你帮助科丁博士找到达到这个理想状态的最少需要多少天

## 输入格式
输入文件名:`garden.in`

第一行，一个整数T，表示测试数据组数。($1 \leq T \leq 10$)

对于每组数据：

第一行，一个整数 $n$ ，表示一开始科丁博士种植的向日葵的数量

第二行，用空格隔开的 $n$ 个整数，依次表示第i棵向日葵的初始高度 $h_i$

第三行，用空格隔开的 $n$ 个整数，依次表示第i棵向日葵每天的生长高度 $a_i$

第四行，用空格隔开的 $n$ 个整数，依次表示第i棵向日葵的期望值 $t_i$

## 输出格式
输出文件名：`garden.out`

对于每组数据输出一行，一个整数表示最少多少天后，这个花园中的向日葵能够达到科丁博士的理想状态，如果无法达到理想状态则输出 $-1$

## 样例

### 样例输入 #1
```
1
5
4 10 12 7 1
3 1 1 4 5
2 4 3 1 0
```

### 样例输出 #1
```
7
```

### 样例输入 #2
```
3
1
10
1
0
2
7 7
8 8
0 1
2
7 3
8 9
1 0
```

### 样例输出 #2
```
0
-1
5
```

## 说明
### 【样例说明】：

#### 输入样例1：

一共有 $5$ 棵向日葵，$7$ 天后，这些向日葵的高度依次是 $25,17,19,35,36$，达到了理想状态，输出 $7$。



#### 输入样例2：

一共 $3$ 组数据

第 $1$ 组，$1$ 棵向日葵，一定能够达到理想状态输出 $0$。

第 $2$ 组，$2$ 棵向日葵，初始高度一样，生长速度也一样，永远无法达到理想状态，输出 $-1$

第 $3$ 组，$2$ 棵向日葵，$5$ 天后，向日葵的高度依次是 $47,48$，达到了理想状态，输出 $5$



### 【数据规模与约定】：

样例1~3：$n \leq 2$

样例4~5：$n≤50$，$h_i$ 以及 $a_i$ 的值都是 $≤10^3$ 的正整数

样例6~8：$n≤1000$，$h_i$ 以及 $a_i$ 的值都是 $≤10^9$ 的正整数

样例9~13：$1≤n<=2 \times 10^5$(数据保证 $T$ 组数据 $n$ 的总和$≤2 \times 10^5$), $h_i$ 以及 $a_i$ 的值都是 $≤10^9$ 的正整数

