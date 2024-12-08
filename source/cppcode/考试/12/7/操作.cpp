#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2e5 + 1;
ll n, m, k, a[N], _c[N];
struct Cmd {
    int typ;
    ll l, r;//x,y
} c[N];

void Run(Cmd &cmd) {
    if(cmd.typ == 1) {
        a[cmd.l] += cmd.r;
        return ;
    }
    for(int i = cmd.l; i <= cmd.r; i++) {
        Run(c[i]);
    }
}

int main() {
    cin >> n >> m >> k;
    for(int i = 1; i <= k; i++) cin >> _c[i];

    int t, l, r;
    for(int i = 1; i <= m; i++) {
        cin >> t >> l >> r;
        c[i] = {t, l, r};
    }
    for(int i = 1; i <= k; i++) {
        Run(c[_c[i]]);
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] % 10007 << " ";
    }
    cout << endl;
    return 0;
}