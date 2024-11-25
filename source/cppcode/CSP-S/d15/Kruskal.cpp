#include <bits/stdc++.h>
using namespace std;

//边结构体
const int N = 5001, M = 200001;
struct Edge {
    int u, v, w, nxt;
} edge[M];
bool Cmp(Edge a, Edge b) { return a.w < b.w; }  //按边权升序排列

//并查集
int fa[N];
int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}
void Merge(int x, int y) {
    int fx = Find(x);
    int fy = Find(y);
    fa[fx] = fy;
}

int n, m;
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    sort(edge + 1, edge + m + 1, Cmp);

    for(int i = 1; i <= n; i++) {
        fa[i] = i;          //让每个点构成单点集合
    }
    int edgeCnt = 0, wSum = 0;
    for(int i = 1; i <= m; i++) {
        if(Find(edge[i].u) != Find(edge[i].v)) {//两点不连通
            edgeCnt++, wSum += edge[i].w;       //累加
            Merge(edge[i].u, edge[i].v);        //合并（连通了）
        }
        if(edgeCnt == n - 1) break;             //终止条件
    }
    if(edgeCnt == n - 1) cout << wSum << endl;
    else cout << "orz" << endl;
    return 0;
}
