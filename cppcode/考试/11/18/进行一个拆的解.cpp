#include <iostream>
using namespace std;

const int N = 1e5 + 1;
int n, a[N];

//两步判断 [1, mid] 是否是 [mid+1, n] 的子序列
bool check(int offset = 0) {
    int mid = (n - 1) / 2;
    bool flag = true; 
    for(int i = 1; i <= mid; i++) {
        if(a[i] != a[i + mid + offset]) flag = false;
    }
    return flag;
} 

//两步判断 [mid + 1, n] 是否是 [1, mid] 的子序列
bool check1(int offset = 0) {
    bool flag = true;
    int mid = (n + 1) / 2;
    for(int i = mid + 1; i <= n; i++) { 
        if(a[i] != a[i - mid + offset]) flag = false;
    }
    return flag;
}

void Solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    if(n % 2) {
        bool f1 = check(0) || check(1);         //左区间是右区间的子区间（向下取整）
        bool f2 = check1(0) || check1(1);       //右区间是左区间的子区间（向上取整）
        bool flag = f1 && f2;
        if(!flag) cout << "YES\n";
        else cout << "NO\n";
    } else {
        int mid = n / 2;
        bool flag = true;
        for(int i = 1; i <= mid; i++) {
            if(a[i] != a[i + mid]) flag = false;
        }
        if(!flag) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) Solve();
    return 0;
}