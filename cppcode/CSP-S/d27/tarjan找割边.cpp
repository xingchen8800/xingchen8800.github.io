#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

struct Node {
    int v, nxt;
} ed[N << 1];
int cnt = 0, h[N] = {};

void AddEdge(int u, int v) {
    ed[cnt++] = {v, h[u]}; h[u] = cnt;
}
void Link(int u, int v) {
    AddEdge(u,v); AddEdge(v,u);
}

int dfn[N], low[N], num = 0;
void Tarjan(int u, int fa) {
    dfn[u] = low[u] = ++num;    //时间戳
    //遍历邻边
    for(int i = h[u]; i; i = ed[i].nxt) {
        int v = ed[i].v;
        if(!dfn[v]) {
            //若某次搜索到了没有被搜索过的点
            Tarjan(v, u);                   //进行搜索，获取dfn[v]和low[v]
            //进入回溯
            low[u] = min(low[u], low[v]);   //如果v可以走到祖先节点，那么u可以通过v到达祖先节点
            if(dfn[u] < low[v]) {
                cout << u << "-->" << v << endl;
            }
        } else if(v != fa) {
            //若在某次搜索中碰到了之前搜过的点（且非父节点）
            //那么显然找到了一条不经过父节点却能走到其祖先节点的路径
            //要将low[u]的值更新
            low[u] = min(dfn[v], low[u]);
        }
    }
}

int n, m;
int main() {
    cin >> n >> m;
    for(int i = 1,u,v; i <= m; i++) {
        cin >> u >> v;
        Link(u, v);
    }
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) Tarjan(i, 0);
    }
    for(int i = 1; i <= n; i++) cout << i << " " << dfn[i] << " " << low[i] << endl;
    return 0;
}