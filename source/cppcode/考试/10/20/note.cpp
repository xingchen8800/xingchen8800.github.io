#include <iostream>
using namespace std;

int n, t1, t2, t3;
string s, name;

int main() {
    freopen("note.in", "r", stdin);
    freopen("note.out", "w", stdout);

    cin >> n;
    t1 = t2 = t3 = 0;
    for(int i = 1; i <= n; i++){
        cin >> s >> name;
        if(s == "section") {
            t2 = t3 = 0;
            t1++;
            cout << t1 << " " << name;
        } else if(s == "subsection") {
            t3 = 0;
            t2++;
            cout << t1 << '.' << t2 << ' ' << name;
        } else {
            t3++;
            cout << t1 << '.' << t2 << '.' << t3 << ' ' << name;
        }
        cout << endl;
    }
    return 0;
}