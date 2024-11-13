#include <bits/stdc++.h>
using namespace std;

class Frac {
private: 
    long long a, b;   //a/b
public:
    Frac() : a(0), b(1) { }
    Frac(long long x, long long y) : a(x), b(y) { }
    Frac(const Frac &x) { this->a = x.a; this->b = x.b; }

    long long gcd(long long x, long long y) {
        return y == 0 ? x : gcd(y, x % y);
    }
    long long lcm(long long x, long long y) {
        return x / gcd(x, y) * y;
    }
    void Simple() {
        if(!a) {
            b = 1;
            return ;
        }
        long long x = gcd(a, b);
        a /= x, b /= x;
    }
    long long A() { return a; }
    long long B() { return b; }

    Frac operator*(const Frac &x) {
        Frac newFrac(this->a * x.a, this->b * x.b);
        newFrac.Simple();
        return newFrac;
    }
    Frac& operator+=(Frac x) {
        long long l = lcm(this->B(), x.B());
        long long newA = this->a * (l / this->b) + x.a * (l / x.b);
        long long newB = l;
        long long g = gcd(newA, newB);
        this->a = newA / g;
        this->b = newB / g;
        return *this;
    }

    friend ostream& operator<<(ostream& out, Frac &x) {
        out << x.A() << "/" << x.B();
        return out; 
    }
};

Frac f[1001][1001];
char mp[1001][1001];

int main() {
    long long n, m;
    cin >> n >> m;
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= i; j++) {
            cin >> mp[i][j];
        }
    }
    f[1][1] = Frac(1, 1);

    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= i; j++) {
            if(mp[i][j] == '*') {
                f[i + 1][j] += f[i][j] * Frac(1, 2);
                f[i + 1][j + 1] += f[i][j] * Frac(1, 2);
            } else {
                if(i + 2 <= n + 1) f[i + 2][j + 1] += f[i][j];
            }
        }
    }

    f[n+1][m+1].Simple();
    cout << f[n+1][m+1];
    return 0;
}