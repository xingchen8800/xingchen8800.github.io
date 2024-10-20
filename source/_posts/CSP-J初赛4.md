---
title: CSP-J初赛第四天
date: 2024-08-23 09:13:16
categories:
    - [数据结构,线性表,顺序表]
    - [数据结构,线性表,栈]
    - [STL,字符串]
    - [STL,栈]
tags: 
    - C++
    - CSP入门组
---

# STL数据结构

## string型字符串

1. 定义：存储字符串的 __容器__， 对字符数组进行 __封装__
2. 构造方法
    
    1. 空的构造函数 
        ```c++
        string::string();   //构造一个空的string型对象

        string a;   //调用string::string()
        ```
    2. 字符型数组常量构造
        ```c++
        string::string(const char *str);
        string::string(char *str);

        string a("abc");    //调用第一个
        char str[] = "abc";
        string b(str);      //调用第二个
        ```
    3. 字符串复制构造
        ```c++
        string::string(string& str);

        string b = "abc";
        string a(b);    //a = "abc";
        ```
    4. 截取构造
        ```c++
        string::string(const char *str, size_t s);
        string::string(char *str, size_t s);
        string::string(string str, size_t s);

        //在str中截取s位复制给新对象
        string a("abc", 2); //a = "ab"
        ```
    5. 截段构造
        ```c++
        string::string(const char *str, int i, int j);
        string::string(char *str, int i, int j);
        string::string(string str, int i, int j);

        //在str中截取[i,j]复制给新对象
        string a("abc", 1, 2);  //a = "bc"
        ```
    6. 字符复制构造
        ```c++
        string::string(int num, const char& c);
        //将str初始化为num个c
        ```

3. 输入
    1. 单词输入（无空格）：
        ```c++
        cin >> str;
        ```
    2. 单行输入（无`\n`）：
        ```c++
        getline(cin, str);
        ```

4. 输出
    1. 直接输出：
        ```c++
        cout << str;
        ```
    2. 循环输出：
        ```c++
        for(int i = 0; i < str.length()/*.size()*/; i++) {
            cout << str[i];
        }
        ```
5. 常用成员函数（定义缩减版，可能有误，[大全](https://zh.cppreference.com/w/cpp/string/basic_string)）
    1. 获取长度
        ```c++
        size_t string::size();
        size_t string::length();
        ```
        其中，认为`size()`和`length()`的返回值一样
    2. 获取迭代器始终
        ```c++
        string::iterator string::begin();  //返回指向首元素地址的迭代器
        string::iterator string::end();    //返回指向最后一个元素的下一位的迭代器
        ```
    3. 追加
        ```c++
        string& string::append(int a, char& c); //追加a个c
        string& string::append(string& str);     //追加str
        string& string::append(string& str, int index, int n);   //追加str中从index开始的n个字符
        
        string& string::operator+(string& str);     //str1 = str2 + str2
        string& string::operator+=(string& str);    //str1 += str2

        string& string::push_back(char &c);     //追加一个c
        ```
    4. 插入
        ```c++
        string& string::insert(iterator& iter, char c);   //在iter位置插入c
        string& string::insert(int pos, string str);    //在pos位置插入str
        ```
    5. 转换
        ```c++
        const char* string::c_str();    //返回C风格字符数组
        ```
    6. 判空
        ```c++
        bool string::empty();   //返回是否为空
        ```
    7. 截取
        ```c++
        basic_string substr( 
            size_type pos = 0,
            size_type count = npos //当count == npos时，从pos开始截取到尾[pos,end())；当count != npos时，截取[pos, pos+count)
        ) const;
        ```
    8. 查找
        ```c++
        size_type find( const basic_string& str, size_type pos = 0 ) const; //pos=0，在[begin,end)区间找str；!=0时在[pos,end)区间找
        size_type find( const char* str, size_type pos = 0 ) const; //pos=0，在[begin,end)区间找str；!=0时在[pos,end)区间找
        size_type rfind( const basic_string& str, size_type pos = npos ) const; //同find()，但是从右往左找（rightfind）
        size_type rfind( const char* str, size_type pos = npos ) const;
        ```

## [stack<value_type>栈]()

1. 定义：栈是一种 __FILO（先进后出）__ 的数据结构，只允许在 *固定的一端* 进行插入和删除。进行插入和删除的一段叫做 __栈顶__，另一端叫栈底。

2. 操作
    1. __压栈__：在栈顶插入元素。
        ```c++
        void push(value_type&& value);  //将value压栈
        ```
    2. __出栈__：在栈顶删除元素，让栈顶下的一个元素成为新的栈顶。
        ```c++
        void pop();
        ```
    3. 获得栈顶元素。
        ```c++
        reference top();
        const_reference top() const;
        ```
    4. 容量
        ```c++
        size_type size() const; //获得栈大小
        bool empty() const; //检查是否为空
        ```
    5. 交换
        ```c++
        void swap( stack& other ) noexcept; //交换两个栈的元素
        ```

### 例题1（十进制转二进制）

```c++
#include <bits/stdc++.h>
using namespace std;

#define DEBUG(format, ...) printf("[DEBUG]" format "\n", __VA_ARGS__)
#pragma GCC optimize(3)

stack<int> s;
int a;

void GetBinaryValue(int dec) {
    if(dec == 0) {
        s.push(0);
        return;
    }
    while(dec) {
        s.push(dec % 2);
        dec /= 2;
    }
}

int main() {
	cin >> a;
    GetBinaryValue(a);
    
    while(s.size()) {
        cout << s.top();
       	s.pop();
    }
    return 0;
}
```

### 例题2（只有+和*的表达式求解）
```c++
#include <bits/stdc++.h>
using namespace std;

#define DEBUG(format, ...) printf("[DEBUG]" format "\n", __VA_ARGS__)
#pragma GCC optimize(3)

stack<int> st;

int main() {
    ios::sync_with_stdio(false);
    char opt;
    int a, b;
    cin >> a;
    st.push(a % 10000);
    while(cin >> opt >> b) {
        if(opt == '*') {
        	a = st.top();
            st.pop();
            st.push(a * b % 10000);
        } else st.push(b);
    }
        
    int ans = 0;
    while(st.size()) {
        ans += st.top();
        ans %= 10000;
        st.pop();
    }
    cout << ans;
    return 0;
}
```