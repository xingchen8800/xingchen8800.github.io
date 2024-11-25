#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1001, M = 1001, INF = 0x3f3f3f3f;
int node[N][M]; //面的编号

//链式前向星模板
struct Edge {
    int u, v, w, nxt;
} l[N * M * 4];
int h[N * M], cnt = 0;
int S, T, tot = 0;

void AddEdge(int u, int v, int w) {
    l[++cnt] = {u, v, w, h[u]}; h[u] = cnt; 
}

//SPFA模板
int dis[N * M], vis[N * M], _cnt[N * M];
bool SPFA(int s) {
    memset(dis, 0x3f, sizeof dis);
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    vis[s] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); vis[u] = false;
        for(int i = h[u], v, w; i; i = l[i].nxt) {
            v = l[i].v; w = l[i].w;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                
                if(vis[v]) continue;
                
                vis[v] = true;
                q.push(v);
                _cnt[v]++;
                if(_cnt[v] > tot) return false;
            }
        }
    }
    return true;
}

#undef int

int main() {
    int code; cin >> code;
    char s[20]; sprintf(s, "network%d.in", code);
    char s1[20]; sprintf(s1, "network%d.ans", code);
    freopen(s, "r", stdin);
    freopen(s1, "w", stdout);
    memset(l, 0, sizeof l);
    memset(h, 0, sizeof h);
    memset(vis, 0, sizeof vis);
    memset(_cnt, 0, sizeof _cnt);
    memset(node, 0, sizeof node);
    cnt = 0, tot = 0;
    int n, m; cin >> n >> m;
    //建图
    for(int i = 1; i <= n - 1; i++) {
        for(int j = 1; j <= m - 1; j++) {
            node[i][j] = ++tot;
        }
    } 
    S = ++tot, T = ++tot;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m - 1; j++) {
            int w; cin >> w;
            if(i == 1) {                        //上层最外侧，与超级汇点连接
                AddEdge(node[i][j], T, w);
                AddEdge(T, node[i][j], w);
            } else if(i == n) {                 //下层最外侧，与超级源点连接
                AddEdge(node[i - 1][j], S, w);
                AddEdge(S, node[i - 1][j], w);
            } else {                            //中间层，将左右边转成上下边，作为对偶图的连边
                AddEdge(node[i - 1][j], node[i][j], w);
                AddEdge(node[i][j], node[i - 1][j], w);
            }
        }
    }
    for(int i = 1; i <= n - 1; i++) {
        for(int j = 1; j <= m; j++) {
            int w; cin >> w;
            if(j == 1) {                        //左侧最外侧，与超级源点连接
                AddEdge(node[i][j], S, w);
                AddEdge(S, node[i][j], w);
            } else if(j == m) {                 //右侧最外侧，与超级汇点连接
                AddEdge(node[i][j - 1], T, w);
                AddEdge(T, node[i][j - 1], w);
            } else {                            //中间层，将上下边转成左右边，作为对偶图连边
                AddEdge(node[i][j - 1], node[i][j], w);
                AddEdge(node[i][j], node[i][j - 1], w);
            }
        }
    }
    SPFA(S);            //对偶图最短路=平面图最大流=最小割
    cout << dis[T] << endl;

    return 0;
}