#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
const int N = 101;

int n, m;
char mp[55][55];
int node[55][55], edge[55][55], cnt = 0;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

void bfs(int i, int j) {
	bool _vis[55][55] = {}; int g[N][N] = {};   //g在这里起记录(i,j)-->(xx,yy)距离的作用
    queue<pair<int, int> > q;
    q.push({i, j});
    _vis[i][j] = true;
    while(!q.empty()) {
        auto p = q.front(); q.pop();
        int x = p.first, y = p.second;
        if(node[x][y]) {
            edge[node[i][j]][node[x][y]] = g[x][y];
        }
        for(int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if(_vis[xx][yy]) continue;
            if(xx < 0 || xx >= n) continue;
            if(yy < 0 || yy >= m) continue;
            if(mp[xx][yy] == '#') continue;;
            q.push({xx, yy});
            _vis[xx][yy] = true;
            g[xx][yy] = g[x][y] + 1;
        }
    }
}

int Prim() {
	int dis[N]; 
    bool vis[N] = {};
    int ans = 0;
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;
    for(int i = 1; i <= cnt; i++) {
        int k, minn = INF;  //找出一个k点，使其到既有边集的距离最近
        for(int j = 1; j <= cnt; j++) {
            if(!vis[j] && dis[j] < minn) {
                k = j;
                minn = dis[j];
            }
        }
        vis[k] = 1;         //标记
        ans += minn;        //权值累加
        for(int j = 1; j <= cnt; j++) {
            if(!vis[j] && dis[j] > edge[k][j]) {
                dis[j] = edge[k][j];       //更新dis[j]
            }
        }
    }
    return ans;
}

int main() {
    cin >> n >> m; getchar(); //吞掉回车
    for(int i = 0; i < n; i++) {
        cin.getline(mp[i], 55);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mp[i][j] == 'A' || mp[i][j] == 'S') {
                node[i][j] = ++cnt;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(node[i][j]) {
                bfs(i, j);
            }
        }
    }
    cout << Prim();
    return 0;
}