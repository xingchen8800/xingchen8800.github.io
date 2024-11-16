#include <bits/stdc++.h>
using namespace std;

int a[101], b[101], c[101];

//a>=b?
bool cmp(int *a, int *b, int len) {
    if(a[len] > 0) return true; //a[len]还有数，即lena > lenb
    for(int i = len - 1; i >= 0; i--) {
        if(a[i] > b[i]) return true;
        else if(a[i] < b[i]) return false;
    }
    return true;
}

void Jian(int *a, int *b, int *c, int lenb) {
    int len = 0;
    while(len < lenb) {
        if(a[len] < b[len]) {
            a[len] += 10; a[len + 1]--;
        }
        c[len] = a[len] - b[len];
        len++;
    }
}

int main() {
    string s, s1;
    cin >> s >> s1;
    if(s1 == "0") {
        cout << "Nan\n";
        return 0;
    }
    int lena = s.size(), lenb = s1.size(), len = lena - lenb;
    for(int i = 0; i < lena; i++) {
        a[lena - i - 1] = (s[i] - '0');
    }
    for(int i = 0; i < lenb; i++) {
        b[lenb - i - 1] = (s1[i] - '0');
    }
    for(int i = lena - lenb; i >= 0; i--) {
        while(cmp(a + i, b, lenb)) {
            c[i]++;
            Jian(a + i, b, a + i, lenb);
        }
    }

    while(len > 0 && c[len] == 0) len--;
    while(lena > 0 && a[lena] == 0) lena--;

    for(int i = len; i >= 0; i--) cout << c[i];
    if(len < 0) cout << "0";
    if(lena > 1 || a[0] > 0) {
        cout << "......";
        for(int i = lena; i >= 0; i--) cout << a[i];
    }
    cout << endl;
    return 0;
}  