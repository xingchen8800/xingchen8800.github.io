#include <bits/stdc++.h>
#define int long long
using namespace std;

//N边 M点
const int N = 201, M = 201, INF = 0x3f3f3f3f;
struct Edge {
    int v, c, nxt;
} l[N * 2];
int h[M], cnt = 1;
int S, T, tot;

void AddEdge(int u, int v, int c) {
    l[++cnt] = {v, c, h[u]}; h[u] = cnt;
    l[++cnt] = {u, 0, h[v]}; h[v] = cnt; 
}

int dis[M], gap[M];
int Stream(int u, int cur) {
    int sum = 0, d;
    if(u == T) return cur;
    for(int i = h[u], v; i; i = l[i].nxt) {
        v = l[i].v;
        if(l[i].c > 0 && dis[v] + 1 == dis[u]) {
            d = Stream(v, min(l[i].c, cur));
            l[i].c -= d, l[i^1].c += d;
            sum += d, cur -= d;
            if(dis[S] == tot || !cur) return sum;
        }
    }
    if(!(--gap[dis[u]])) dis[S] = tot;
    gap[++dis[u]]++;
    return sum;
}

int Sap() {
    int ans = 0;
    memset(dis, 0, sizeof dis);
    memset(gap, 0, sizeof gap);
    gap[0] = tot;
    while(dis[S] < tot) ans += Stream(S, INF);
    return ans;
}

#undef int

int main() {
    int n, m; cin >> n >> m;
    //建图
    for(int i = 1, s, e, c; i <= n; i++) {
        cin >> s >> e >> c;
        AddEdge(s, e, c);
    }
    //定义源点、汇点和总点数
    S = 1, T = m, tot = m;
    cout << Sap();  //ISAP算法出结果
    return 0;
}