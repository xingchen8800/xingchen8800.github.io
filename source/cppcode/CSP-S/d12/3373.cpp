#include <bits/stdc++.h>
using namespace std;

const long long N = 100001;
long long MOD;
struct Node {
    long long l, r, s, a, m;
} t[N << 4];
long long a[N], n, q;

void Build(long long c, long long l, long long r) {
    t[c] = {l, r, 0, 0, 1};
    if(l == r) {
        t[c].s = a[l] % MOD;
        return;
    }
    long long mid = (l + r) / 2;
    Build(c*2, l, mid);
    Build(c*2+1, mid + 1, r);
    t[c].s = (t[c*2].s + t[c*2+1].s) % MOD;
}


void Push(long long c) {
    long long add = t[c].a, mul = t[c].m;
    // 更新直属区间和
    t[c << 1].s = ((t[c << 1].s * mul + (t[c << 1].r - t[c << 1].l + 1) * add) % MOD + MOD) % MOD; // 先乘后加
    t[c << 1 | 1].s = ((t[c << 1 | 1].s * mul + (t[c << 1 | 1].r - t[c << 1 | 1].l + 1) * add) % MOD + MOD) % MOD; // 先乘后加
    // 更新懒标记
    t[c << 1].a = (t[c << 1].a * mul + add) % MOD; // 先乘后加
    t[c << 1 | 1].a = (t[c << 1 | 1].a * mul + add) % MOD; // 先乘后加
    t[c << 1].m = (t[c << 1].m * mul) % MOD; // 更新乘法懒标记
    t[c << 1 | 1].m = (t[c << 1 | 1].m * mul) % MOD; // 更新乘法懒标记
    // 懒标记置空
    t[c].a = 0; 
    t[c].m = 1; // 重置懒标记
}

void Add(long long c, long long l, long long r, long long k) {
    if(t[c].l >= l && t[c].r <= r) {
        t[c].s = (t[c].s + (t[c].r - t[c].l + 1) * k) % MOD;
        t[c].a = (t[c].a + k) % MOD;
        return ;
    }
    Push(c);

    long long mid = (t[c].l + t[c].r) / 2;
    if(l <= mid) Add(c*2, l, r, k);
    if(r > mid) Add(c*2+1, l, r, k);
    t[c].s = (t[c*2].s + t[c*2+1].s) % MOD;
}

void Mul(long long c, long long l, long long r, long long k) {
    if(t[c].l >= l && t[c].r <= r) {
        t[c].s = (t[c].s * k) % MOD;
        t[c].m = (t[c].m * k) % MOD;
        t[c].a = (t[c].a * k) % MOD;
        return ;
    }
    Push(c);

    long long mid = (t[c].l + t[c].r) / 2;
    if(l <= mid) Mul(c*2, l, r, k);
    if(r > mid) Mul(c*2+1, l, r, k);
    t[c].s = (t[c*2].s + t[c*2+1].s) % MOD;
}

long long Query(long long c, long long l, long long r) {
    if(t[c].l >= l && t[c].r <= r) {
        return t[c].s % MOD;
    }
    Push(c);

    long long mid = (t[c].l + t[c].r) / 2, ret = 0;
    if(l <= mid) ret = (ret + Query(c*2, l, r)) % MOD;
    if(r > mid) ret = (ret + Query(c*2+1, l, r)) % MOD;
    return ret % MOD;
}

int main() {
    cin >> n >> q >> MOD;
    for(long long i = 1; i <= n; i++) cin >> a[i];
    Build(1, 1, n);
    while(q--) {
        long long x, y, z, d;
        cin >> x >> y >> z;
        if(x == 1) {
            cin >> d;
            Mul(1, y, z, d);
        } else if(x == 2) {
            cin >> d;
            Add(1, y, z, d);
        } else if(x == 3) cout << Query(1, y, z) << endl;
    }
    return 0;
}