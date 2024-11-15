#include <bits/stdc++.h>
using namespace std;
const long long N = 2e3 + 1;
#define INF 0x3f3f3f3f

long long g[N][N];
long long n, c[N][N];

long long dis[N]; bool vis[N];
long long Prim() {
    long long ans = 0;
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[1] = 0;
    for(long long i = 0; i <= n; i++) {
        long long k, minn = INF;  //找出一个k点，使其到既有边集的距离最近
        for(long long j = 0; j <= n; j++) {
            if(!vis[j] && dis[j] < minn) {
                k = j;
                minn = dis[j];
            }
        }
        vis[k] = 1;         //标记
        ans += minn;        //权值累加
        for(long long j = 0; j <= n; j++) {
            if(!vis[j] && dis[j] > g[k][j]) {
                dis[j] = g[k][j];       //更新dis[j]
            }
        }
    }
    return ans;
}

int main() {
    cin >> n;
    memset(g, 0x3f, sizeof g);
    for(long long i = 1; i <= n; i++) {
        for(long long j = i; j <= n; j++) {
            cin >> c[i][j];
            g[i-1][j] = g[j][i-1] = c[i][j];
        }
    }
    cout << Prim();
    return 0;
}