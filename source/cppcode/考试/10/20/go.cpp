#include <bits/stdc++.h>
using namespace std;
int x[10001], y[10001];
int main() {
    freopen("go.in", "r", stdin);
    freopen("go.out", "w", stdout);

    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    sort(x + 1, x + n + 1);
    sort(y + 1, y + n + 1);

    for(int i = 1; i <= n; i++) {
        x[i] -= i;
    }
    sort(x + 1, x + n + 1);
    int mx = x[(n + 1) / 2];
    int my = y[(n + 1) / 2];
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += abs(x[i] - mx) + abs(y[i] - my);
    }

    cout << ans;
    return 0;
}
