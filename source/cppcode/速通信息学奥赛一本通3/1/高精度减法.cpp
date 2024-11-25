#include <bits/stdc++.h>
using namespace std;

int a[101], b[101], c[101];

bool cmp(string a, string b) {
    if(a.size() < b.size()) return false;
    if(a.size() > b.size()) return true;
    return a > b;
}

int main() {
    string s, s1;
    cin >> s >> s1;
    if(!cmp(s, s1)) {
        swap(s, s1);
        cout << "-";
    }
    int lena = s.size(), lenb = s1.size();
    for(int i = 0; i < lena; i++) {
        a[lena - i] = (s[i] - '0');
    }
    for(int i = 0; i < lenb; i++) {
        b[lenb - i] = (s1[i] - '0');
    }
    int len = 1;
    while(len <= lena || len <= lenb) {
        if(a[len] < b[len]) {
            a[len] += 10; a[len + 1]--;
        }
        c[len] = a[len] - b[len];
        len++;
    }
    while(len > 1 && c[len] == 0) len--;
    for(int i = len; i >= 1; i--) cout<<c[i];
    cout << endl;
    return 0;
}