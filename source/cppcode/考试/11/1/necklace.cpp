#include <bits/stdc++.h>
using namespace std;

int n, a[100001], v[100001];
int sum = 0;

const int MOD = 1e9 + 7;

int fastPow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    for(int i = 1; i <= n; i++) cin >> v[i];

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        long long val = fastPow(2, sum - a[i]) * (fastPow(v[i] + 1, a[i] - 1 + MOD) % MOD);
        ans = (ans + val) % MOD;
    }    
    cout << ans << endl;
    return 0;
}