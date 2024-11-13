#include <bits/stdc++.h>
using namespace std;

const int N = 5001, M = 200001, INF = 0x3f3f3f3f;
int g[N][N];
int n, m, ans = 0;

int dis[N]; bool vis[N];
void Prim() {
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[1] = 0;
    for(int i = 1; i <= n; i++) {
        int k, minn = INF;  //找出一个k点，使其到既有边集的距离最近
        for(int j = 1; j <= n; j++) {
            if(!vis[j] && dis[j] < minn) {
                k = j;
                minn = dis[j];
            }
        }
        vis[k] = 1;         //标记
        ans += minn;        //权值累加
        for(int j = 1; j <= n; j++) {
            if(!vis[j] && dis[j] > g[k][j]) {
                dis[j] = g[k][j];       //更新dis[j]
            }
        }
    }
}

int main() {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);  //用邻接矩阵别忘了初始化
    for(int i = 1; i <= n; i++) g[i][i] = 0;
    for(int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = w;
    }
    Prim();
    cout << ans << endl;
    return 0;
}