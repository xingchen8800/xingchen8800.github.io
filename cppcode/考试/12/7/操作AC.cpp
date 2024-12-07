#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2e5 + 1, MOD = 10007;

ll n, m, k;
ll o[N], x[N], y[N], cf[N], ans[N], cnt[N];
int main() {
    cin >> n >> m >> k;
    while(k--) {
        int c;
        cin >> c;
        cf[c]++, cf[c-1]--;
    }
    for(ll i = m; i >= 1; i--) {
        cnt[i] = (cnt[i+1] + cf[i]) % MOD;
        if(o[i] == 2) {
            cf[y[i]] += cnt[i];
            cf[x[i]-1] -= cnt[i];
        }
    }
    for(ll i = m; i >= 1; i--) {
        if(o[i] == 1) 
            ans[x[i]] = (ans[x[i]] + cnt[i] * y[i]) % MOD;
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    return 0;
}