#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 50001;
ll n, kind = 0;
struct Line {
    ll id, x;
} c[N];
map<ll, ll> m, m1;

bool Cmp(Line &a, Line &b) {
    return a.x < b.x;
}

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) {
        cin >> c[i].x >> c[i].id;
        if(++m1[c[i].id] == 1) {
            kind++;
        }
    }
    sort(c + 1, c + n + 1, Cmp);
    ll l = 1, r = 1, kinds = 0, ans = LLONG_MAX;
    for(; r <= n; r++) {
        if(++m[c[r].id] == 1) kinds++;
        while(l < r && m[c[l].id] > 1) {
            m[c[l].id]--;
            l++;
        }
        if(kinds == kind) {
            ans = min(ans, c[r].x - c[l].x);
        } 
    }
    cout << ans << " " << kind << endl;
    return 0;
}