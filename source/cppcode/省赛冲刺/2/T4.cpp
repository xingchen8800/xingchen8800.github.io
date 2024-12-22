#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e4 + 1;

struct Line {
    double l, r;
    bool operator<(Line &rhs) {
        return r < rhs.r;
    }
} a[N];
ll n, l;

int main() {
    cin >> n >> l;
    for(ll i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        double dis = sqrt(l * l - y * y);
        a[i] = {max((double)x - dis, 0.0), (double)x + dis};
    }
    sort(a + 1, a + n + 1);
    
    ll ans = 1;
    double r = a[1].r;
    for(ll i = 1; i <= n; i++) {
        if(a[i].l > r) {
            ans++;
            r = a[i].r;
        }
    }
    cout << ans << endl;
    return 0;
}
