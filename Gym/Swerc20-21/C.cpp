#include<bits/stdc++.h>
using namespace std;

const int N = 1001;
const int le = N + 1;
const int to = N + 2;
const int ri = N + 3;
const int bo = N + 4;

int n;
int xx, yy;
vector<double> x(N), y(N);


double euc_dist(int a, int b) {
    double xd = abs(x[a] - x[b]);
    double yd = abs(y[a] - y[b]);
    return sqrt(abs(xd*xd + yd*yd));
}

struct e{
    int a, b;
    double dist;
    e (int aa, int bb) : a(aa), b(bb) {
        if (a == le) dist = x[b];
        if (a == to) dist = yy - y[b];
        if (a == ri) dist = xx - x[b];
        if (a == bo) dist = y[b];
        if (a < N) dist = euc_dist(a, b) / 2;
    } 
};

struct dsu {
    int n;
    vector<int> p;

    dsu(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }

    inline int get(int cur) {
        return (cur == p[cur] ? cur : p[cur] = get(p[cur]));
    }

    inline void unite(int x, int y) {
        x = get(x);
        y = get(y);
        p[y] = x;
    }
};

int main() {
    cin >> xx >> yy;
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    vector<e> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            edges.push_back(e(i, j));
        }
        for (int j = N + 1; j <= N + 4; j++) {
            edges.push_back(e(j, i));
        }
    }

    sort(edges.begin(), edges.end(), [&](e e1, e e2) {
        return (e1.dist < e2.dist);
    });

    dsu d(N + 6);

    double ans = 0;

    int curInd = 0;

    while (d.get(to) != d.get(bo) && d.get(to) != d.get(ri) && d.get(ri) != d.get(le) && d.get(le) != d.get(bo)) {
        d.unite(edges[curInd].a, edges[curInd].b);
        ans = edges[curInd].dist;
        curInd++;
    }
    cout << fixed << setprecision(17);
    cout << ans << '\n';
}