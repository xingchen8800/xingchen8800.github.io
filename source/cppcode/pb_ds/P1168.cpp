#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

const int N = 100001;
__gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>> tree;

int main() {
    int n;
    cin >> n;
    for(int i = 1, x; i <= n; i++) {
        cin >> x;
        tree.insert(x);
    }
    for(int i = 1; 2 * i - 1 <= n; i++) {
        cout << (*tree.find(i)) << endl;
    }
    return 0;
}