---
title: CSP-J初赛-3
date: 2024-08-22 09:06:46
categories:
    - [CSP,CSP-J,课程,集训]
    - [数据结构,图,深度优先搜索]
    - [数据结构,图,广度优先搜索]
---

# 深度优先搜索

## 定义
深度优先搜索 从问题的 *初始状态* 出发，根据体重的约束条件按照一定的策略 *有序推进、不断深入* 。对到达的所有目标状态 __一一验证__ ，找到符合条件的解或者找到所有可能的解，再求最优解。

## 回溯
回溯 也是 __试探法__，它从问题的某一状态出发不断“试探”着往前走一步。当一条路走到了尽头，不能在前进的时候，倒退回一步或若干步从另一种可能的状态出发，继续搜索直到所有的路径都试探过。

深度优先搜索包含回溯，或者说回溯法就是深度优先搜索的一种。深度优先搜索就是一条路走到黑。能搜就搜，不能搜就回溯。

{% note yellow fa-pen %}
特点：简单容易实现占用内存比较少能找出解决问题的方案，要多次遍历搜索不同的可能情况标记再取消效率比较低。
{% endnote %}

## 例题

### [1.送快递（简单+/普及-）](https://oj.aicoders.cn/group/3024/training/29731/problem/6935)
#### 描述

快递员为了能高效快速的送达快递，画了一个城市地图，地图由n×n的格子图表示，地图中有些格子可以走，有些不可以走，“.”表示格子可以走，“#”表示格子不能走，现在有个快件需要从左上角$(1,1)$位置送往右下角$(n,n)$位置，行进方式是上下左右4个方向，为了避免白跑一趟，需要你编写程序判断$(1,1)$到达$(n,n)$是否存在一条可行的路线，如果存在输出“YES”否则输出“NO”。

注意：起点和终点均为“.”，走的时候不能走出地图边界以外。

#### 输入描述

输入第一行为 $n(2 \leq n \leq 10)$，表示 $n \times n$ 的方格，接下来有 $n$ 行，每行 $n$ 个符号，“.”表示可以走，“#” 表示不能走，每个符号之间用空格隔开。

#### 输出描述

如果存在路径，输出“YES”，否则输出“NO”。

#### 样例输入 1 
```
3
. . #
# . .
. # .
```

#### 样例输出 1 
```
YES
```

#### 代码
```c++
// ./CSP/J/8/DFS1-6935-Send.cpp
// 注解同./CSP/J/DFS2-1744-Maze.cpp
#include<bits/stdc++.h>
using namespace std;

#pragma GCC optimize(3)

int n;
char t;
bool city[11][11], vis[11][11] = {false}, flag = false;
const int mx[4] = {0, 1, -1, 0};	
const int my[4] = {-1, 0, 0, 1};

void dfs(int x, int y) {
    if(x == n && y == n) { 
        flag = true;
        return;
    }
    
    for(int i = 0; i < 4; i++) {
        int nx = x + mx[i];
        int ny = y + my[i];
        if(city[nx][ny] && nx >= 1 && nx <= n && ny >= 1 && ny <= n && !vis[nx][ny]) {
           	vis[nx][ny] = true;
            dfs(nx, ny);
            vis[nx][ny] = false;
        }
    }
}

int main()	{
    memset(vis, false, sizeof vis);
    vis[1][1] = true;
 	cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%c", &t);
            while(t == ' ' || t == '\n') scanf("%c", &t);
            city[i][j] = (t == '.' ? true : false);
        } 
    }
    dfs(1,1);
    cout << (flag ? "YES" : "NO");
	return 0;
}
```

### [2.迷宫（简单/普及-）](https://oj.aicoders.cn/group/3024/training/29731/problem/1744)

#### 描述

有 1 个 $n \times n$ 的迷宫方格，在方格内“0”表示可以通行，“1”表示是障碍物不能通行，在$(n，n)$位置有一个宝箱。现在有个人在左上角$(1,1)$的位置，他在迷宫内可以向当前位置的上、下、左、右四个方向行走，能不能在迷宫里走到宝箱位置$(n，n)$。

注意：测试数据保证起点和终点均为“0”，走的过程不能走出迷宫。

#### 输入描述

输入第一行为 $n(2 \leq n \leq 10)$，表示 n×n 的方格，接下来有 n 行，每行 n 个整数， 0 表示可以行走，1 表示不能行走，每个整数之间有个空格。

#### 输出描述

如果可以走到终点，输出“YES”，否则输出“NO”

#### 样例输入 1 
```
3
0 0 1
1 0 0
0 1 0
```
#### 样例输出 1 
```
YES
```

#### 代码
```c++
// ./CSP/J/DFS2-1744-Maze.cpp

#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(3)

int n, t;
int city[11][11];
bool vis[11][11] = {false}, flag = false;
//          下、上、左、右
int mx[4] = {0, 0, -1, 1};	    //x轴移动数组
int my[4] = {1, -1, 0, 0};      //y轴移动数组

inline void dfs(int x, int y) {
    
    if(x == n && y == n) {  //走到右下角
       	flag = true;        //标记找到
        return;             //退出
    }
    
    for(int i = 0; i < 4; i++) {
        //尝试走动
        int nx = x + mx[i];
        int ny = y + my[i];
        if(!city[nx][ny] && nx >= 1 && nx <= n && ny >= 1 && ny <= n && !vis[nx][ny]) { //可以走、不越界（x∈[1,n],y∈[1,n]）、没走过
           	vis[nx][ny] = true; //标记
            dfs(nx, ny);        //搜索
            if(flag) return;    //退出
            vis[nx][ny] = false;//回溯
        }
    }
}

int main()	{
    memset(vis, false, sizeof vis); //很重要的两步，初始化
    vis[1][1] = true;               //↑
 	cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%d", &t);
            city[i][j] = t;
        } 
    }
    dfs(1, 1);
    if(flag) cout << "YES";
    else cout << "NO";
	return 0;
}
```

### [3.N个数的所有情况的全排列（简单+/普及-）](https://oj.aicoders.cn/group/3024/training/29731/problem/TCZX-0302)

#### 描述

输入一个正整数 $N$，输出 $N$ 个数的所有情况的全排列。

#### 输入描述

输入一行一个正整数 $N$。

#### 输出描述

N个数的所有情况的全排列，每行一个序列。

#### 样例输入 1 
```
3
```
#### 样例输出 1 
```
1
12
123
13
132
2
21
213
23
231
3
31
312
32
321
```
#### 提示

数据范围与提示:$1 \leq N \leq 9$

#### 代码
```c++
// ./CSP/J/8/DFS3-T0302-Permutation

#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize(3)

int n;
int a[10];
int vis[10];

void dfs(int x) {                   //当前DFS到第x个数
    for(int i = 1; i < x; i++)      //先输出一种
        printf("%d", a[i]);         //↑
   	if(x != 1) printf("\n");        //可以输出就要加换行
    if(x - 1 == n) {                //x个数搜完了，回溯
        return;                     //↑
    }
    
    for(int i = 1; i <= n; i++) {   //枚举第x位的可能情况[1,n]
        if(!vis[i]) {               //没用过
            vis[i] = true;          //标记
            a[x] = i;               //试着将第x位设为i
            dfs(x + 1);             //搜下一位
            vis[i] = false;         //回溯
        }
    }
}

int main() {
    scanf("%d", &n);
    dfs(1);
    return 0;
}
```

# 广度优先搜索

## 定义
从初始状态出发，不止求一条路，而是再每一步都把附近能走的点全部都搜索完，把每一个位置都标记，将搜索到的点的信息全部进行存储，记录行坐标列坐标花费的步数，直到走完所有点，或者是找到了终点结束，属于扩散式搜索。首先起点入队进行标记，队列不为空的情况下开始进行搜索搜索队首点。当一个点的所有方向搜索完成之后，出队，队首元素更换，以新的队首为搜索点进行新一轮的搜索。搜到的点就入队，搜完一个点就出队。


{% note green fa-pen %}
特点：对解决最短路径或最少时间的问题会比铰有效先找到的路径一定是最短路
{% endnote %}
