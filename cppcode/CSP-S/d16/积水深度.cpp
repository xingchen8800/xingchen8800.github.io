#include <bits/stdc++.h>
using namespace std;

const int N = 1001, M = 1001;

int n, m, a[N][M], node[N][M];
int cnt = 0;   //点数
int tot = 0;   //l的索引
int mv[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

//链式前向星
struct Edge {
    int u, v, w, nxt;
} l[N*M*2], l1[N*M*2];  
//l1存储最小生成树用，l记录边
int h[N*M], tot1 = 0;   //l1的索引

//求最小生成树时的初次建图
void Link(int u, int v, int w) {
    l[++tot] = {u, v, w };  //最小生成树没有邻接边的遍历需要
}

//最小生成树存图
bool Cmp(Edge a, Edge b) {  //最小生成树的排序
    return a.w < b.w;
}
void AddEdge(int u, int v, int w) {
    l1[++tot1] = {u, v, w, h[u]}; h[u] = tot1;
}

//并查集
int fa[N*N];
int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
void Merge(int x, int y) { fa[Find(x)] = Find(y); }

//Kruskal
int Kruskal() {
    sort(l + 1, l + tot + 1, Cmp);
    int nodeCnt = 0, wSum = 0;
    for(int i = 1; i <= tot; i++) {
        if(Find(l[i].u) != Find(l[i].v)) {//两点不连通
            nodeCnt++, wSum += l[i].w;       //累加
            Merge(l[i].u, l[i].v);        //合并（连通了）
            //存最小生成树
            AddEdge(l[i].u, l[i].v, l[i].w);
            AddEdge(l[i].v, l[i].u, l[i].w);
        }
        if(nodeCnt == cnt - 1) {
            break;             //终止条件
        }
    }
    return wSum;
}

//深搜计算水深
int height[N] = {};
void Dfs(int u, int father) {
    for(int i = h[u]; i; i = l1[i].nxt) {
        int v = l1[i].v;
        if(v == father) continue;   //又通过反向边返回了
        height[v] = max(height[u], l1[i].w); //计算权值最大的边
        Dfs(v, u);
    }
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            node[i][j] = ++cnt; //给点编号
            fa[cnt] = cnt;      //并查集初始化
        }
    }
    //将虚拟点(cnt+1)与外围点连边
    for(int i = 1; i <= m; i++) {       //每列第一行
        Link(cnt + 1, node[1][i], max(0, a[1][i]));
        Link(cnt + 1, node[n][i], max(0, a[n][i]));
    }
    for(int i = 1; i <= n; i++) {       //每行第一列
        Link(cnt + 1, node[i][1], max(0, a[i][1]));
        Link(cnt + 1, node[i][m], max(0, a[i][m]));
    }

    //每个点向四周连边
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            for(int k = 0; k < 4; k++) {
                int x = i + mv[k][0];
                int y = j + mv[k][1];
                if(x < 1 || x > n) continue;
                if(y < 1 || y > m) continue;
                Link(node[i][j], node[x][y], max(a[i][j], a[x][y]));
            }
        }
    }
    Kruskal();
    //遍历最小生成树，找到每个节点的路径最大值
    Dfs(cnt + 1, cnt + 1);  //从虚拟节点开始找
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(height[node[i][j]] <= a[i][j]) { //不能存水
                cout << "0 ";
            } else cout << height[node[i][j]] - a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}