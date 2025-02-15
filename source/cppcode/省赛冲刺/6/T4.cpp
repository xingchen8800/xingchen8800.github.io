#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll N = 60, M = 60;
ll n, m, code = 0;
bool b[N][M], vis[N][M];
struct Point {ll x, y;}; 
vector<Point> bd[2];
//获取曼哈顿距离
ll GetDis(ll x, ll y, ll xx, ll yy) {
    return llabs(x - xx) + llabs(y - yy);
}

const ll DX[] = {0, 0, 1, -1}, DY[] = {1, -1, 0, 0};
void bfs(ll x, ll y, ll cd) {
    queue<pair<ll, ll> > q;
    q.push({x, y});
    vis[x][y] = true;
    while(q.size()) {
        auto u = q.front(); q.pop();
        ll x = u.first, y = u.second;
        for(ll i = 0; i < 4; i++) {
            ll xx = x + DX[i]; 
            ll yy = y + DY[i];
            if(xx >= 1 && xx <= n && yy >= 1 && yy <= m) 
            if(!vis[xx][yy] && b[xx][yy]) {
                vis[xx][yy] = true;
                bd[cd].push_back({xx,yy});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for(ll i = 1; i <= n; i++) {
        for(ll j = 1; j <= m; j++) {
            char c;
            cin >> c;
            b[i][j] = (c == 'X');
        }
    }
    for(ll i = 1; i <= n; i++) {
        for(ll j = 1; j <= m; j++) {
            if(b[i][j] && !vis[i][j]) bfs(i,j,code++);
        }
    }
    ll ans = LLONG_MAX;
    for(auto i : bd[0]) {
        for(auto j :bd[1]) {
            ll dis = GetDis(i.x, i.y, j.x, j.y);
            ans = min(ans, dis);
        }
    }
    cout << ans << endl;
    return 0;
}