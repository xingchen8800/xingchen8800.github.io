#include <bits/stdc++.h>
using namespace std;

int a[4];
bool vis[4] = {false};
int bestH = -1, bestMi = -1;

bool cmp(int h1, int m1, int h2, int m2) {
    if(h1 > h2) return true;
    else if(h1 == h2)
        if(m1 > m2) return true;
    return false;
}

void dfs(int hr, int mi, int s) {
    if(s > 4) {
        if(cmp(hr, mi, bestH, bestMi)) {
            bestH = hr, bestMi = mi;
        }
        return;
    }
    for(int i = 0; i < 4; i++) {
        if(vis[i]) continue;
        if(s <= 2) {
            if(hr * 10 + a[i] <= 23) {
                vis[i] = true;
                dfs(hr * 10 + a[i], mi, s + 1);
                vis[i] = false;
            }
        } else {
            if(mi * 10 + a[i] <= 59) {
                vis[i] = true;
                dfs(hr, mi * 10 + a[i], s + 1);
                vis[i] = false;
            }
        }
    }
}

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    
    
    for(int i = 0; i < 4; i++) cin >> a[i];

    dfs(0, 0, 1);

    if(~bestH && ~bestMi) {
        cout << (bestH < 10 ? "0" : "") << bestH << ":" << (bestMi < 10 ? "0" : "") << bestMi << endl;
    } else cout << "Muddle";
    return 0;
}