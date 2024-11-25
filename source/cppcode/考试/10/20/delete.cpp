#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("delete.in", "r", stdin);
    freopen("delete.out", "w", stdout);
    
    string s;
    cin >> s;
    for(int i = 0; i < s.length() - 3; i++) {
        if(s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 'd' && s[i + 3] == 'e') {
            s[i] = s[i + 1] = s[i + 2] = s[i + 3] = ' ';
        }
    }
    for(int i = 0; i < s.length(); i++) {
        if(s[i] != ' ') cout << s[i];
    }
    cout << endl;
    return 0;
}