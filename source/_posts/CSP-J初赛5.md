---
title: CSP-J初赛5
date: 2024-08-26 09:07:51
categories:
    - [数据结构,线性表,队列]
    - [STL,队列]
tags: C++
---

# 队列

{% notel default fa-pen 定义 %}
队列是一种 __先进先出__ 的数据结构，也是一种特殊的 __线性表__，只能在队首进行删除操作，队尾进行进行插入操作。
{% endnotel %}

## 术语

### 队首
进行删除的一端叫做队首。

### 队尾
进行插入的一端叫做队尾。

### 入队
队列插入元素叫做入队，新加入的则为新的队尾。

### 出队
队列删除元素叫做出队，删除后的元素为新的队首。

### 元素个数
队列内从队首到队尾（含）的元素个数。

## 常用接口

### 声明
```c++
#include <queue>    //#include <bits/stdc++.h>
using namespace std;

queue<TypeName> Q; //TypeName填如int、double、string或者自定义结构体之类的数据类型（包括指针）
```

### 基本操作
```c++
q.push(x);      //x入队
q.pop();        //队首出队
```

### Getter
```c++
size_t size = q.size();     //获取大小
TypeName x = q.front();     //获取队首元素
TypeName y = q.back();      //获取队尾元素
bool empty = q.empty();     //获取队列是否为空(bool empty = q.size() == 0)
```

# 动态数组

{% notel default fa-pen 介绍 %}
动态数组(`vector<>`)本质是就是一个顺序表，它的长度是动态的，采用连续的存储空间，可以存储任意数据类型。
{% endnotel %}

## 使用

### 初始化
```c++
#include <vector>   //#include <bits/stdc++.h>
//初始化空vector
vector<TypeName> ArrayName;    
//vector<int> a;

//初始化n个val组成的vector
vector<TypeName> ArrayName(n, val);
//vector<int> b(10, 100);

//初始化存储begin到end区间元素的vector
vector<TypeName> ArrayName(begin, end);
// vector<char> c(str.begin(), str.end());

//复制初始化
vector<TypeName> ArrayName(AnotherVector);
// vector<char> d(c);s
```

### 遍历

#### 1.下标遍历
```c++
vector<int> array(20, 3);
for(int i = 0; i <= array.size(); i++) {
    cout << array[i] << " ";
}
```

#### 2.迭代器遍历
```c++
vector<int> array(20, 3);
for(vector<int>::iterator i = array.begin(); i != array.end(); i++) {
    cout << (*i) << " ";
}
```

#### 3.反向迭代器遍历
```c++
vector<int> array(20, 3);
for(vector<int>::reverse_iterator i = array.rbegin(); i != array.rend(); i++) {
    cout << (*i) << " ";
}
```

#### 4.for(:)型遍历
对于定义了迭代器`begin()`和`end()`的数据类型都可以`for(...:...)`
```c++
vector<int> array(20, 3);
for(auto i : array) {   //i的类型是int&
    cout << i << " ";
}
```

### 常用接口

#### Getter
```c++
v.begin();      //获取首元素的迭代器
v.end();        //获取尾元素后一位的迭代器
v.rbegin();     //获取尾元素后一位的反向迭代器
v.rend();       //获取首元素的迭代器
v.size();       //获取v的元素个数
v.capacity();   //获取v的容量（不等于元素个数）
v.at(2);        //获取v[2]
v.front();      //获取v[0]
v.back();       //获取最后一个元素
```

#### 操作
```c++
v.push_back(x);                         //尾插x
v.pop_back();                           //删除尾元素
v.resize(n);                            //更改v的大小为n
v.resize(n,m);                          //更改v的大小为n并以m填充新元素	
v.insert(v.begin() + 2,-1);             //将 -1 插入到v[2]的位置 原v[2]及后面的元素 全部后移一个位置
v.insert(v.begin() + 2,3,-2);           //v[2]位置 插入 3 个 -2
v.erase(v.end() - 1);                   //删除迭代器所指元素  删除最后一个元素
v.erase(v.begin() + 1,v.end() - 1);     //删除指定范围内的所有元素
v.clear();                              //清空动态数组 
```