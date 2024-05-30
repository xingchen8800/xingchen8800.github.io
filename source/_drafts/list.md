---
title: 链表
tags:
categories:
- 《算法竞赛》
- [数据结构,链表]
---

# T1. [约瑟夫问题](https://www.luogu.com.cn/problem/P1996)

## 题目描述

$n$ 个人围成一圈，从第一个人开始报数,数到 $m$ 的人出列，再由下一个人重新从 $1$ 开始报数，数到 $m$ 的人再出圈，依次类推，直到所有的人都出圈，请输出依次出圈人的编号。

**注意：本题和《深入浅出-基础篇》上例题的表述稍有不同。书上表述是给出淘汰 $n-1$ 名小朋友，而该题是全部出圈。**

## 输入格式

输入两个整数 $n,m$。

## 输出格式

输出一行 $n$ 个整数，按顺序输出每个出圈人的编号。

## 样例 #1

### 样例输入 #1

```
10 3
```

### 样例输出 #1

```
3 6 9 2 7 1 8 5 10 4
```

## 提示

$1 \le m, n \le 100$

## 题解
用 __链表__ 模拟一个圈，每数m个数就输出一次，然后删除那个节点即可.

### 代码A-动态链表
```c++
#include <iostream>
using namespace std;

struct Node {   //定义节点结构体
    int data;   //数据（本题存储编号）
    Node *nxt;  //下一个元素（本题不需要向前遍历）
};

int n, m;
Node *head; //链表的头（最后一个节点）
Node *p;    //临时节点，给链表添加数据时使用
Node *now;  //当前节点，数数时使用
Node *prev; //当前节点的上一个节点，删除节点时使用

int main() {
    //输入
    cin >> n >> m;
    //初始化（建立链表）
    head = new Node;    //为头申请空间
    head->data = 1;     //头的编号是1
    head->nxt = nullptr;//暂时没有下一位
    now = head;         //从头开始
    //添加节点
    for(int i = 2; i <= n; i++) {
        p = new Node;   //临时节点申请空间
        now->nxt = p;   //临时节点进入链表
        now = p;        //更新当前节点
    }
    now->nxt = head;    //链表成环
    //数数(solution)
    now = head, prev = head;    //从头开始数
    while((n--) > 1) {  //链表不空就循环
        for(int i = 1; i < m; i++) {    //从1数到m - 1
            prev = now;     //更新上一位
            now = now->nxt; //更新当前位为下一位
        }
        cout << now->data << " " << endl;
        prev->nxt = now->nxt;   //将上个节点的下一位更新为当前节点的下一位(删除当前节点)
        delete now; //释放内存
        now = prev->nxt;    //从下一个继续
    }
    cout << now->data << " ";   //最后一个没有输出完
    delete now; //释放内存(太标准了)
    return 0;
}
```

### 代码B-静态链表
```c++
#include <iostream>
using namespace std;

struct Node{
    int id, nxt_id;
} nodes[101];

int n, m;

int main() {
    //输入
    cin >> n >> m;
    //初始化
    nodes[0].nxt_id = 1;    //第一个节点的值为1
    for(int i = 1; i <= n; i++) {
        nodes[i].id = i;            //第i个节点的值为i
        nodes[i].nxt_id = i + 1;    
    }
    nodes[n].nxt_id = 1;    //成环
    //数数
    int now = 1, prev = 1;
    while((n--) > 1) {
        for(int i = 1; i < m; i++) {
            prev = now;
            now = nodes[now].nxt_id;
        }
        cout << nodes[now].id << " ";
        nodes[prev].nxt_id = nodes[now].nxt_id;
        now = nodes[prev].nxt_id;
    }
    cout << nodes[now].id << " ";
    return 0;
}
```

### 代码C-双向链表
```c++
#include <iostream>
using namespace std;

struct Node{
    int id, nxt_id, pre_id;
} nodes[101];

int n, m;

int main() {
    //输入
    cin >> n >> m;
    //初始化
    nodes[0].nxt_id = 1;    //第一个节点的值为1
    for(int i = 1; i <= n; i++) {
        nodes[i].id = i;            //第i个节点的值为i
        nodes[i].nxt_id = i + 1;
        nodes[i].pre_id = i - 1;    
    }
    nodes[n].nxt_id = 1;
    nodes[1].pre_id = n;    //成环
    //数数
    int now = 1;
    while((n--) > 1) {
        for(int i = 1; i < m; i++) {
            now = nodes[now].nxt_id;
        }
        cout << nodes[now].id << " ";
        int prev = nodes[now].pre_id;               //记录上一位
        int next = nodes[now].nxt_id;               //记录下一位
        nodes[prev].nxt_id = nodes[now].nxt_id;     
        nodes[next].pre_id = nodes[now].pre_id;     //删除now
        now = next;                                 //更新now
    }
    cout << nodes[now].id << " ";
    return 0;
}
```

### 代码D-一维数组代替链表
```c++
#include <iostream>
using namespace std;

int nodes[101];
int n, m;

int main() {
    //输入
    cin >> n >> m;
    //初始化
    for(int i = 1; i <= n - 1; i++)
        nodes[i] = i + 1;       //nodes[i]就是下个节点
    nodes[n] = 1;    //成环
    //数数
    int now = 1, prev = 1;
    while((n--) > 1) {
        for(int i = 1; i < m; i++) {
            prev = now;
            now = nodes[now];
        }
        cout << now << " ";
        nodes[prev] = nodes[now];
        now = nodes[prev];
    }
    cout << now << " ";
    return 0;
}
```

### 代码E-STL list
```c++
#include <iostream>
#include <list>
using namespace std;

int n, m;
list<int> nodes;

int main() {
    //输入
    cin >> n >> m;
    //初始化
    for(int i = 1; i <= n; i++)
        node.push_back(i);
    //数数
    list<int>::iterator it = node.begin();  //迭代器
    while(node.size > 1) {  //链表有数
        for(int i = 1; i <= m; i++) {
            it++;
            if(it == node.end()) it = node.begin(); //手动成环
        }
        cout << *it << " "; //*it就是it的值
        //删除it
        auto nxt = ++it;
        if(nxt == node.end()) nxt = node.begin();
        node.erase(--it);
        it = nxt;
    } 
    cout << *it;
    return 0;
}
```

### 代码F-队列模拟
```c++
#include <iostream>
#include <queue>
using namespace std;
queue<int> q;
int main(){
	int a[101], n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		q.push(1);
	}
	int k = 1;
	while(!q.empty()){
		k++;
		if(k == m){
			cout << q.front() << " ";
			q.pop();
			k = 0;
		}else{
			q.push(q.front());
			q.pop();
		}
	}
	return 0;
}
```

# 课后习题-P1160 [队列安排](https://www.luogu.com.cn/problem/P1160)

## 题目描述

一个学校里老师要将班上 $N$ 个同学排成一列，同学被编号为 $1\sim N$，他采取如下的方法：

1. 先将 $1$ 号同学安排进队列，这时队列中只有他一个人；

2. $2\sim N$ 号同学依次入列，编号为 $i$ 的同学入列方式为：老师指定编号为 $i$ 的同学站在编号为 $1\sim(i-1)$ 中某位同学（即之前已经入列的同学）的左边或右边；

3. 从队列中去掉 $M$ 个同学，其他同学位置顺序不变。

在所有同学按照上述方法队列排列完毕后，老师想知道从左到右所有同学的编号。

## 输入格式

第一行一个整数 $N$，表示了有 $N$ 个同学。

第 $2\sim N$ 行，第 $i$ 行包含两个整数 $k,p$，其中 $k$ 为小于 $i$ 的正整数，$p$ 为 $0$ 或者 $1$。若 $p$ 为 $0$，则表示将 $i$ 号同学插入到 $k$ 号同学的左边，$p$ 为 $1$ 则表示插入到右边。

第 $N+1$ 行为一个整数 $M$，表示去掉的同学数目。

接下来 $M$ 行，每行一个正整数 $x$，表示将 $x$ 号同学从队列中移去，如果 $x$ 号同学已经不在队列中则忽略这一条指令。

## 输出格式

一行，包含最多 $N$ 个空格隔开的整数，表示了队列从左到右所有同学的编号。

## 样例 #1

### 样例输入 #1

```
4
1 0
2 1
1 0
2
3
3
```

### 样例输出 #1

```
2 4 1
```

## 提示

**【样例解释】**

将同学 $2$ 插入至同学 $1$ 左边，此时队列为：

`2 1`

将同学 $3$ 插入至同学 $2$ 右边，此时队列为：

`2 3 1`  

将同学 $4$ 插入至同学 $1$ 左边，此时队列为：

`2 3 4 1`  

将同学 $3$ 从队列中移出，此时队列为：

`2 4 1`  

同学 $3$ 已经不在队列中，忽略最后一条指令

最终队列：

`2 4 1`  

**【数据范围】**

对于 $20\%$ 的数据，$1\leq N\leq 10$。

对于 $40\%$ 的数据，$1\leq N\leq 1000$。

对于 $100\%$ 的数据，$1<M\leq N\leq 10^5$。

## 题解
将N个学生看作一个链表。操作2为在第k位元素的左/右插入一个元素，操作3为删除链表中的第x个元素

### 代码(AC*2 + TLE * 3 = 40pts)
```c++
#include <iostream>
#include <list>
using namespace std;

struct Node {
    int id;
    Node *next, *prev;
};

int n, m;
bool isErased[100001] = {0};

int main() {
    //输入
    cin >> n;
    //init
    Node *now, *_p, *first, *last;
    now = new Node;
    now->id = 1;
    now->next = nullptr;
    now->prev = nullptr;
    first = now;
    last = now;
    //solution
    for(int i = 2; i <= n; i++) {
        int k, p;
        cin >> k >> p;
        Node *_k = first;
        while(_k->next) {
            if(_k->id == k) break;
            _k = _k->next;
        }
        if(p == 0) {
            _p = new Node;
            _p->id = i;
            _p->next = _k;
            _p->prev = _k->prev;
            if(_k->prev) _k->prev->next = _p;
            else first = _p;
            _k->prev = _p;
        } else {
            _p = new Node;
            _p->id = i;
            _p->prev = _k;
            _p->next = _k->next;
            if(_k->next) _k->next->prev = _p;
            else last = _p;
            _k->next = _p;
        }
    }
    cin >> m;
    now = first;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        if(isErased[x]) continue;
        else isErased[x] = true;
        now = first;
        while(now->next){
            if(now->id == x) {
                if (now->prev) {
                    now->prev->next = now->next;
                } else {
                    first = now->next;
                }
                if (now->next) {
                    now->next->prev = now->prev;
                } else {
                    last = now->prev;
                }
                delete now;
                now = first;
                break;
            } 
            now = now->next;
        }
    }
    //output
    now = first;
    while(now) {
        cout << now->id << " ";
        now = now->next;
    }
    return 0;
}
```