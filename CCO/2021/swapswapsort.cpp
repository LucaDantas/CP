#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int B = 100, maxn = 1e5+10;

vector<int> pos[maxn];

int a[maxn], id[maxn], cnt;

long long resp[maxn/B+10][maxn];

struct BIT {
    int bit[maxn];
    void upd(int x) {
        for(; x > 0; x-=x&-x)
            ++bit[x];
    }
    int query(int x) {
        int ans = 0;
        for(; x < maxn; x+=x&-x)
            ans += bit[x];
        return ans;
    }
} bit;

long long inversoes(int n) {
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += bit.query(a[i]+1);
        bit.upd(a[i]);
    }
    return ans;
}

int32_t main() {
    int n, k, q; scanf("%lld %lld %lld", &n, &k, &q);
    for(int i = 1; i <= n; i++)
        scanf("%lld", a+i), pos[a[i]].push_back(i);
    for(int cor = 1; cor <= k; cor++) {
        if(pos[cor].size() >= B) {
            id[cor] = ++cnt;
            int qtd = 0;
            for(int i = n; i >= 1; i--) {
                if(a[i] == cor)
                    ++qtd;
                else
                    resp[cnt][a[i]] += qtd;
            }
        }
    }
    long long ans = inversoes(n);
    vector<int> perm(k);
    iota(perm.begin(), perm.end(), 1);
    while(q--) {
        auto get = [&](int x, int y) -> long long {
            if(pos[x].size() >= B)
                return resp[id[x]][y];
            if(pos[y].size() >= B)
                return 1ll * pos[x].size() * pos[y].size() - resp[id[y]][x];
            long long aq = 0;
            for(int i = 0, ptr = 0; i < (int)(pos[y].size()); i++) {
                for(; ptr < (int)(pos[x].size()) && pos[x][ptr] < pos[y][i]; ptr++);
                aq += pos[x].size() - ptr;
            }
            return aq;
        };
        int index; scanf("%lld", &index); --index;
        ans -= get(perm[index], perm[index+1]);
        swap(perm[index], perm[index+1]);
        ans += get(perm[index], perm[index+1]);
        printf("%lld\n", ans);
    }
}
