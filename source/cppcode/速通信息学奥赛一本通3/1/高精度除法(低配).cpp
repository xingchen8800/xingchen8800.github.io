#include <bits/stdc++.h>
using namespace std;

int a[101], b, c[101];

int main() {
    string s;
    cin >> s >> b;
    int lena = s.size();
    for(int i = 0; i < lena; i++) {
        a[i + 1] = (s[i] - '0');
    }
    int x = 0;
    for(int i = 1; i <= lena; i++) {
        c[i] = (x * 10 + a[i]) / b;
        x = (x * 10 + a[i])  % b;
    }
    int len = 1;
    while(c[len] == 0 && len < lena) len++;
    for(int i = len; i <= lena; i++) cout<<c[i];
    cout << endl;
    return 0;
}