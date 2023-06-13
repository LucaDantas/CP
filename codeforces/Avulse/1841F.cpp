#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 6e5+10;

using ll = long long;

struct Vector {
    ll x, y;
    Vector(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    ll operator% (const Vector& o) const {
        return x * o.y - y * o.x;
    }
    bool half() const { return y<0 || (y == 0 && x < 0); }
    bool operator<(const Vector& o) const {
        if(half() != o.half()) return half() < o.half();
        return (*this)%o > 0;
    }
    void operator+=(const Vector& o) { x += o.x, y += o.y; }
    void operator-=(const Vector& o) { x -= o.x, y -= o.y; }
    long double get() { return (long double)x * x + (long double)y * y; }
} pt[maxn];

int main() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
        a -= b, c -= d;
        if(!a && !c) --i, --n;
        else pt[i] = Vector(a, c);
    }
    sort(pt, pt+n);
    for(int i = n; i < 2*n; i++)
        pt[i] = pt[i-n];
    Vector ans;
    long double val = 0;
    for(int i = 0, ptr = 0; i < n; i++) {
        for(; ptr - i < n && (pt[i]%pt[ptr] > 0 || (pt[i]%pt[ptr]==0 && pt[i].half() == pt[ptr].half())); ++ptr)
            ans += pt[ptr], val = max(ans.get(), val);
        ans -= pt[i];
        val = max(ans.get(), val);
    }
    cout << fixed << setprecision(0) << val << endl;
}
