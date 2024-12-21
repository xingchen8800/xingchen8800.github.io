#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e4 + 5;

struct VIP {
    ll l, r, c;
    bool operator<(VIP &rhs) {
        return r < rhs.r;
    }
} a[N];
bool wasUsed[N] = {0};
ll n;

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) cin >> a[i].l >> a[i].r >> a[i].c;
    sort(a + 1, a + n + 1);
    
    ll ans = 0;
    for(ll i = 1; i <= n; i++) {
        ll cnt = 0;
        for(ll j = a[i].l; j <= a[i].r; j++) {
            if(wasUsed[j]) cnt++;
        }
        for(ll j = a[i].r; j >= a[i].l; j--) {
            if(cnt >= a[i].c) break;
            if(!wasUsed[j]) {
                wasUsed[j] = true;
                cnt++; ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
