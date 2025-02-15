#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, c;
const ll N = 20001;
ll num[N], code[20];

int main() {
    cin >> n;
    for(ll i = 1; i <= n; i++) cin >> num[i];
    cin >> c;
    for(ll i = 1; i <= c; i++) cin >> code[i];

    sort(code + 1, code + c + 1);
    
    ll cnt = 0;
    vector<ll> ans, nums;
    for(ll l = 1; l <= n - 3; l++) {
        nums.clear();
        nums.push_back(num[l]);
        nums.push_back(num[l + 1]);
        nums.push_back(num[l + 2]);
        sort(nums.begin(), nums.end());
        bool flag = true; ll d = nums[0] - code[1];
        for(ll j = 2; j <= c; j++) {
            if(nums[j-1] != d) {
                flag = false;
                break;
            }
        }
        if(flag) {
            cnt++;
            ans.push_back(l);
        }
    }
    cout << cnt << endl;
    for(auto i : ans) {
        cout << i << endl;
    }
    return 0;
}