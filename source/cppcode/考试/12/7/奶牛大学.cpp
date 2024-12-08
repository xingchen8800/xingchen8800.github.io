//Code for O(n log_n)
// #include <bits/stdc++.h>
// using namespace std;

// const int N = 100001;
// typedef long long ll;

// ll n, c[N];

// int main() {
//     cin >> n;
//     ll maxVal = 0;
//     for(int i = 1; i <= n; i++) {
//         cin >> c[i];
//         maxVal = max(c[i], maxVal);
//     }
//     sort(c + 1, c + n + 1);
//     ll maxMoney = 0, i, ans = 0;
//     for(i = 0; i <= maxVal; i++) {
//         int index = lower_bound(c + 1, c + n + 1, i) - c;
//         ll sum = (n - index + 1) * i;
//         if(sum > maxMoney) {
//             maxMoney = sum;
//             ans = i;
//         }
//     }
//     cout << maxMoney << " " << ans << endl;

//     return 0;
// }

//Code for O(n)
#include <bits/stdc++.h>
using namespace std;

const int N = 100001;
typedef long long ll;

ll n, c[N];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    ll maxM = 0, ans = 0;
    sort(c + 1, c + n + 1);
    for(int i = 1; i <= n; i++) {
        ll sum = (n - i + 1) * c[i];
        if(sum > maxM) {
            maxM = sum;
            ans = c[i];
        }
    }    
    cout << maxM << " " << ans << endl;
    return 0;
}