#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
const int N = 5001, M = 200001;

struct Edge {
    int v, w;
};
vector<Edge> g[N];  //邻接表存图

int n, m;

struct Cmp {
    bool operator()(Edge a, Edge b) {
        return a.w > b.w;
    }
};

int vis[N];
int Prim() {
    memset(vis, 0, sizeof vis);
    priority_queue<Edge, vector<Edge>, Cmp> q;
    int cnt = 0, ans = 0;
    q.push({1, 0}); //第一个点，距离为0
    while(!q.empty()) { //没有包含所有点
        auto k = q.top(); q.pop();
        if(vis[k.v]) continue;      //已在既有图集中
        
        vis[k.v] = 1;               //标记
        ans += k.w;                 //累加权值
        cnt++;
        
        for(auto i : g[k.v]) {//遍历邻边
            if(!vis[i.v]) {         //遍历邻接点
                q.push({i.v, i.w});
            }
        }
    }
    if(cnt == n) return ans;
    else return -1;
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    int ans = Prim();
    if(ans == -1) cout << "orz";
    else cout << ans << endl;
    return 0;
}