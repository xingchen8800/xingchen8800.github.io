#include <bits/stdc++.h>
using namespace std;

const int N = 50001, M = 50001;

struct Edge {
    int u, v, w, nxt;
} l[M << 2];
int h[N], cnt = 0;
void Link(int u, int v, int w) {
    l[++cnt] = {u, v, w, h[u]}; h[u] = cnt;
}

int n, m;   //n点、m次询问

//深搜求dep和dis
int dep[N], jump[N][31], dis[N];
void Dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;   //记录深度
    jump[u][0] = fa;        //初始化jump数组
    for(int i = h[u], v, w; i; i = l[i].nxt) {
        v = l[i].v; w = l[i].w;
        if(v == fa) continue;   //不能原路返回
        dis[v] = dis[u] + w;
        Dfs(v, u);
    }
}
//递推求jump
void GetJump() {
    for(int i = 1; i <= 30; i++) {
        for(int j = 1; j <= n; j++) {
            jump[j][i] = jump[jump[j][i-1]][i-1];
        }
    }
}

//倍增求lca
int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v); //保证u在v下   
    //将u上跳到v的高度
    for(int i = 30; i >= 0; i--) {
        if(dep[u] - (1 << i) >= dep[v]) {
            u = jump[u][i];
        }
    }
    if(u == v) return u;    //特判
    //跳到lca下
    for(int i = 30; i >= 0; i--) {
        if(jump[u][i] != jump[v][i]) {
            u = jump[u][i];
            v = jump[v][i];
        }
    }
    return jump[u][0];      //u或v的父节点是lca
}

//求两点间的距离
int GetDis(int u, int v) {
        int a = LCA(u, v);
        return dis[u] - dis[a] + dis[v] - dis[a];
}

int main() {
    cin >> n;
    for(int i = 1, u, v, w; i < n; i++) {   //树有n-1条边
        cin >> u >> v >> w;
        Link(u + 1, v + 1, w); Link(v + 1, u + 1, w);   //城市编号向后偏移，空出0号虚拟节点
    }
    Dfs(1, 0);  //0号节点其实不存在，只是虚拟的
    GetJump();
    cin >> m;
    for(int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        u++, v++, w++;
        int dis1 = GetDis(u, v);
        int dis2 = GetDis(v, w);
        int dis3 = GetDis(u, w);
        cout << (dis1 + dis2 + dis3) / 2 << endl;
    }
    return 0;
}