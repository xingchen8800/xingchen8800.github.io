#include <bits/stdc++.h>
using namespace std;

#define ll long long
map<string, ll> m;
ll n;

bool Bigger(string &lhs, string &rhs) {
    if(lhs.size() != rhs.size()) return lhs.size() > rhs.size();
    return lhs > rhs;
}

pair<ll, char> Get1stNum(string &s) {
    cout << s << endl;
    ll ret = 0, i = 0;
    char c = '\0';
    for(; i < s.size(); i++) {
        if(isdigit(s[i])) ret = ret * 10 + ret;
        else {
            c = s[i];
            break;
        }
        if(i > 0 && ret == 0) return {-1, '\0'};
    }
    for(ll j = 0; j <= i; j++) {
        if(isdigit(s[i])) s.erase(s.begin());
    }
    return {ret, c};
}

bool IsInvaild(string ip) {
    for(int i = 1; i <= 4; i++) {
        pair<ll, char> ret = Get1stNum(ip);
        cout << ret.first << " " << ret.second << endl;
        if(ret.first == -1 || ret.first > 255 || (i == 4 ? ret.second != ':' : ret.second != '.')) return false;
    }
    cout << "a" << endl;
    pair<ll, char> res = Get1stNum(ip);
    if(res.first > 65535 || res.second != '\0' ) return false;
    return true;
}

int main() {
    cin >> n;
    string s;
    for(int i = 1; i <= n; i++) {
        cin >> s;
        if(s == "Client") {
            cin >> s;
            cout << IsInvaild(s) << endl;
        } else {
            cin >> s;
            cout << IsInvaild(s) << endl;
        }
    }
    return 0;
}