#include <bits/stdc++.h>
using namespace std;

struct Node {
    int num, idx;
}cnt[256];

vector<vector<int>> info;

void toHex(int x) {
    string s;
    if(x == 0) s = "00";
    else while(x) {
        if(x % 16 <= 9) s += ('0' + (x % 16));
        else s += ('A' + ((x % 16) - 10));
        x /= 16;
    }
    while(s.size() <= 1) s += "0";
    for(int i = s.length() - 1; i >= 0; i--) {
        cout << s[i];
    }
}

int main() {
    // priority_queue<int, vector<int>, less<int> > q;
    freopen("code.in", "r", stdin);
    freopen("code.out", "w", stdout);
    
    for(int i = 0; i < 256; i++) {
        cnt[i].idx = i;
        cnt[i].num = 0;
    }
    
    int n;
    cin >> n;
    
    for(int i = 1; i <= n; i++) {
        vector<int> v;
        string s;
        cin >> s;
        for(int i = 0; i < s.length(); i += 2) {
            int num = stoi(s.substr(i, 2), 0, 16);
            cnt[num].num++;
            v.push_back(num);
        }
        info.push_back(v);
    }
    sort(cnt, cnt + 256, [=](Node & a, Node & b) {
        if(a.num == b.num) return a.idx < b.idx;
        return a.num > b.num;
    });
    for(int i = 0; i < 16; i++) toHex(cnt[i].idx);
    cout << endl;
    for(auto i : info) {
        for(auto j : i) {
            int minDis = INT_MAX, code = 0;
            for(int k = 0; k < 16; k++) {
                if(minDis > abs(j - cnt[k].idx)) {
                    minDis = abs(j - cnt[k].idx);
                    code = k;
                }
            }
            if(code >= 0 && code <= 9) cout << code;
            else cout << (char)('A' + (code - 10));
        }
        cout << endl;
    }
    return 0;
}