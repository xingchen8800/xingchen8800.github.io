#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
} foots[5] = {{0,1},{1,1},{0,0},{1,0}};
const string foot[] = {"FL", "FR", "RL", "RR"};
const string mv[] = {"F", "B", "R", "L"};

//E,S,W,N
ll rotation = 3;
ll lx = LONG_LONG_MAX, ly = LONG_LONG_MAX, hx = LONG_LONG_MIN, hy = LONG_LONG_MIN;

pair<ll,ll> GetMoveValue(ll r) {
    if(r == 0) {
        if(rotation == 0) return {1,0};
        if(rotation == 1) return {0,-1};
        if(rotation == 2) return {-1,0};
        if(rotation == 3) return {0,1};
    } else if(r == 1) {
        if(rotation == 0) return {-1,0};
        if(rotation == 1) return {0,1};
        if(rotation == 2) return {1,0};
        if(rotation == 3) return {0,-1};
    } else if(r == 2) {
        if(rotation == 0) return {0,-1};
        if(rotation == 1) return {-1,0};
        if(rotation == 2) return {0,1};
        if(rotation == 3) return {1,0};
    } else if(r == 3) {
        if(rotation == 0) return {0,1};
        if(rotation == 1) return {1,0};
        if(rotation == 2) return {0,-1};
        if(rotation == 3) return {-1,0};
    }
}

Point Rotate(const Point& basePoint, const Point& p) {
    ll dx = p.x - basePoint.x, dy = p.y - basePoint.y;
    dx = -dx;
    swap(dx, dy);
    return {basePoint.x + dx, basePoint.y + dy};
}

bool check() {
    for(ll i = 0; i < 4; i++) {
        for(ll j = 0; j < 4; j++) {
            if(foots[i].x == foots[j].x && foots[i].y == foots[j].y && i != j) {
                return false;
            }
        }
    }
    return true;
}

void Update() {
    for(ll i = 0; i < 4; i++) {
        hx = max(foots[i].x, hx);
        lx = min(foots[i].x, lx);
        hy = max(foots[i].y, hy);
        ly = min(foots[i].y, ly);
    }
}

int main() {
    ll n; cin >> n;
    for(ll i = 1; i <= n; i++) {
        string cmd; cin >> cmd;
        if(cmd[2] == 'P') {
            for(ll f = 0; f < 4; f++) {
                if(cmd == foot[f] + "P") {
                    for(ll j = 0; j < 4; j++) {
                        if(j != f) {
                            foots[j] = Rotate(foots[f], foots[j]);
                        }
                    }
                }
            }
        } else for(ll f = 0; f < 4; f++) {
            for(ll r = 0; r < 4; r++) {
                if(cmd == foot[f] + mv[r]) {
                    foots[f].x += GetMoveValue(r).first;
                    foots[f].y += GetMoveValue(r).second;
                    if(!check()) {
                        cout << -1 << endl;
                        return 0;
                    }
                    break;
                }
            }
        }
    }
    cout << (hx - lx) * (hy - ly) << endl;
    return 0;
}