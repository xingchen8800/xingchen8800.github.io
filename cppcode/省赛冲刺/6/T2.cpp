#include <bits/stdc++.h>
using namespace std;
#define ll long long

string bin, tri;

ll bin2dec(string s) {
    ll ret = 0;
    for(ll i = s.size() - 1; i >= 0; i--) {
        ret += (s[i] - '0') * pow(2, s.size() - i - 1);
    }
    return ret;
}

ll tri2dec(string s) {
    ll ret = 0;
    for(ll i = s.size() - 1; i >= 0; i--) {
        ret += (s[i] - '0') * pow(3, s.size() - i - 1);
    }
    return ret;
}


int main() {
    cin >> bin >> tri;
    for(ll i = 0; i < bin.size(); i++) {
        for(ll j = 0; j < tri.size(); j++) {
            string tmp1 = bin, tmp2 = tri;
            tmp1[i] = (bin[i] == '0' ? '1' : '0');
            tmp2[i] = (tri[j] == '0' ? '1' : '0');
            if(bin2dec(tmp1) == tri2dec(tmp2)) {
                cout << bin2dec(tmp1) << endl;
                return 0;
            }
        }
    }
    return 0;
}