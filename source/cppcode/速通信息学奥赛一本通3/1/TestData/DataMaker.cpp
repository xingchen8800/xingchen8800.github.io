#include <bits/stdc++.h>
using namespace std;
int main() {
    string code; cin >> code;
    string s; s+="network" ; s += code; s+=".in";
    freopen(s.c_str(), "w", stdout);
    int nlimit, mlimit, waU, wbU, waH, wbH;
    cin >> nlimit >> mlimit >> waU >> wbU >> waH >> wbH;
    srand((unsigned int)time(NULL));
    int m, n;
    // if(nlimit == 2) n = 2;
    // else if(nlimit == 3) n = 3;
    // else n = 1 + rand() % (nlimit - 1);
    
    m = mlimit, n = nlimit;

    // if(mlimit == 2) m = 2;
    // else if(mlimit == 3) m = 3;
    // else m =  1 + rand() % (mlimit - 1);

    cout << n << " " << m << endl;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m - 1; j++) {
            cout << waU + rand() % (int)(waH - waU) << " ";
        }
        cout << endl;
    }
    for(int i = 1; i <= n - 1; i++) {
        for(int j = 1; j <= m; j++) {
            cout << wbU + rand() % (int)(wbH - wbU) << " ";
        }
        cout << endl;
    }
    return 0;
}