#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e4 + 1;

struct Line {
    ll l, r;
    bool operator<(Line &rhs) {
        return r < rhs.r;
    }
} a[N];
ll n;

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) cin >> a[i].l >> a[i].r;
    sort(a + 1, a + n + 1);
    
    ll ans = 1, r = a[1].r;
    for(ll i = 1; i <= n; i++) {
        if(a[i].l > r) {
            ans++;
            r = a[i].r;
        }
    }
    cout << ans << endl;
    return 0;
}
