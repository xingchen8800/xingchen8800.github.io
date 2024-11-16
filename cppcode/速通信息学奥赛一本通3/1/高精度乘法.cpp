#include <bits/stdc++.h>
using namespace std;

int a[101], b[101], c[101];

int main() {
    string s, s1;
    cin >> s >> s1;
    int lena = s.size(), lenb = s1.size();
    for(int i = 0; i < lena; i++) {
        a[lena - i] = (s[i] - '0');
    }
    for(int i = 0; i < lenb; i++) {
        b[lenb - i] = (s1[i] - '0');
    }
    int len = 0;
    for(int i = 1; i <= lena; i++) {
        int x = 0;
        for(int j = 1; j <= lenb; j++) {
            c[i+j-1] = a[i] * b[j] + x;
            x = c[i+j-1] / 10;
            c[i+j-1] %= 10;
        }
        c[i+lenb] = x;
    }
    len = lena + lenb;
    while(len > 1 && c[len] == 0) len--;
    for(int i = len; i >= 1; i--) cout<<c[i];
    cout << endl;
    return 0;
}