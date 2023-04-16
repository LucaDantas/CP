#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;

struct Pt {
    int x, y;
    Pt(int _x, int _y) : x(_x), y(_y) {}
    Pt() {}
    Pt operator+(Pt a) { return Pt(x+a.x, y+a.y); }
    Pt operator-(Pt a) { return Pt(x-a.x, y-a.y); }
    long long operator/(Pt a) {
        return 1ll * x * a.y - 1ll * y * a.x;
    }
} pt[maxn];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int x, y; scanf("%d %d", &x, &y);
        pt[i] = Pt(x, y);
    }
    puts((n&1) ? "Beatrice" : "Alberto"); fflush(stdout);
    vector<int> vivos(n); iota(vivos.begin(), vivos.end(), 1);
    for(int round = n; round >= 3; round--) {
        if(round&1) {
            int q; scanf("%d", &q);
            vivos.erase(find(vivos.begin(), vivos.end(), q));
        } else {
            int eu = -1;
            long long ans = 0x3f3f3f3f3f3f3f3f;
            for(int i = 0; i < (int)(vivos.size()); i++) {
                Pt aq = pt[vivos[i]], prox = pt[vivos[(i+1) % vivos.size()]], ant = pt[vivos[(i - 1 + vivos.size()) % vivos.size()]];
                long long area = abs((prox-aq) / (ant-aq));
                if(area < ans)
                    ans = area, eu = vivos[i];
            }
            vivos.erase(find(vivos.begin(), vivos.end(), eu));
            printf("%d\n", eu); fflush(stdout);
        }
    }
}
