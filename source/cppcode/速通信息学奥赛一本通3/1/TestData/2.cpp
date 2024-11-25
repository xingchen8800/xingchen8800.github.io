#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1001, M = 1001, INF = 0x3f3f3f3f;
int node[N][M];
struct Edge {
    int u, v, w, nxt;
} l[N * M * 10];
int h[N * M], cnt = 0;
int S, T, tot = 0;

void AddEdge(int u, int v, int w) {
    l[++cnt] = {u, v, w, h[u]}; h[u] = cnt; 
}

int dis[N * M], vis[N * M]/*, _cnt[N * M]*/;
// bool SPFA(int s) {
//     memset(dis, 0x3f, sizeof dis);
//     queue<int> q;
//     q.push(s);
//     dis[s] = 0;
//     vis[s] = 1;
//     while(q.size()) {
//         int u = q.front(); q.pop(); vis[u] = false;
//         for(int i = h[u], v, w; i; i = l[i].nxt) {
//             v = l[i].v; w = l[i].w;
//             if(dis[v] > dis[u] + w) {
//                 dis[v] = dis[u] + w;
                
//                 if(vis[v]) continue;
                
//                 vis[v] = true;
//                 q.push(v);
//                 _cnt[v]++;
//                 if(_cnt[v] > tot) return false;
//             }
//         }
//     }
//     return true;
// }
void Dijsktra(int s) {
    //初始化
    memset(dis, 0x3f, sizeof dis);
    memset(vis, false, sizeof vis);
    
    //s入队
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > q; //优先队列免去了在dis中找最小值的操作
    dis[s] = 0;
    q.push({0, s});
    
    //bfs
    while(q.size()) {
        pair<int, int> _pair = q.top(); q.pop(); //取出队首
        int u = _pair.second;   //获取节点
        if(!vis[u]) {
            vis[u] = true;
            int v, w;  //邻接点和权值
            //遍历邻接点
            for(int i = h[u]; i; i = l[i].nxt) {
                v = l[i].v;  //邻接点
                w = l[i].w;  //权值
                if(!vis[v] && dis[v] > dis[u] + w) {    //松弛
                    dis[v] = dis[u] + w;
                    q.push({dis[v], v});
                }
            }
        }
    }
}
#undef int

int main() {
    freopen("network18.in", "r", stdin);
    freopen("network18.ans", "w", stdout);
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
            if(i == 1) {
                AddEdge(node[i][j], T, w);
                AddEdge(T, node[i][j], w);
            } else if(i == n) {
                AddEdge(node[i - 1][j], S, w);
                AddEdge(S, node[i - 1][j], w);
            } else {
                AddEdge(node[i - 1][j], node[i][j], w);
                AddEdge(node[i][j], node[i - 1][j], w);
            }
        }
    }
    for(int i = 1; i <= n - 1; i++) {
        for(int j = 1; j <= m; j++) {
            int w; cin >> w;
            if(j == 1) {
                AddEdge(node[i][j], S, w);
                AddEdge(S, node[i][j], w);
            } else if(j == m) {
                AddEdge(node[i][j - 1], T, w);
                AddEdge(T, node[i][j - 1], w);
            } else {
                AddEdge(node[i][j - 1], node[i][j], w);
                AddEdge(node[i][j], node[i][j - 1], w);
            }
        }
    }
    Dijsktra(S);
    cout << dis[T] << endl;
    return 0;
}
