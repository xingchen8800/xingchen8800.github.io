#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll N = 1e6 + 1;
ll d[N], arr[N];
ll n, k, a, b;

int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        d[i] = arr[i] - arr[i - 1];
    }
    for(int i = 1; i <= k; i++) {
        cin >> a >> b;
        d[a]++, d[b + 1]--;
    }
    for(int i = 2; i <= n; i++) {
        d[i] += d[i - 1];
    }
    sort(d + 1, d + n + 1);
    cout << d[(n + 1) / 2] << endl;
    return 0;
}