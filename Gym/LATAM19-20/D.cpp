#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

using ll = long long;

struct Vector {
    int x, y;
    Vector(int x, int y) : x(x), y(y) {}
    Vector operator+(const Vector& o) { return Vector(x + o.x, y + o.y); }
    Vector operator-(const Vector& o) { return Vector(x - o.x, y - o.y); }
    ll operator/(const Vector& o) const { return 1ll * x * o.y - 1ll * y * o.x; }
    Vector inv() { return Vector(-y, x); }
    int get_plane() const { return y > 0 || (y == 0 && x > 0); }
    bool operator<(const Vector& o) const {
        if(get_plane() != o.get_plane())
            return get_plane() > o.get_plane();
        return (*this) / o > 0;
    }
    void db() {
        printf("%d %d\n", x, y);
    }
};

array<int,3> stars[maxn];

int main() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++)
        for(int& x : stars[i])
            scanf("%d", &x);
    vector<Vector> opa;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) if(stars[i][2] > stars[j][2]) {
            Vector p1(stars[i][0], stars[i][1]), p2(stars[j][0], stars[j][1]);
            opa.push_back((p2-p1).inv());
        }
    }
    int qtd = (int)(opa.size());
    sort(opa.begin(), opa.end());
    opa.insert(opa.end(), opa.begin(), opa.end()); // repito todo mundo
    bool ok = 0;
    for(int i = 0, ptr = 0; i < qtd; i++) {
        for(; ptr < 2*qtd && opa[i]/opa[ptr] >= 0; ptr++);
        ok |= ptr == 2*qtd;
    }
    puts(ok || !qtd ? "Y" : "N");
}
