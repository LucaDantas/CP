#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 1e4+10;

vector<int> caras[maxn];

int qtd(ll vel) {
    priority_queue<int> ativos;
    ll soma = 0;
    int ans = 0;
    for(int i = 1; i < maxn; i++) {
        soma += vel;
        soma = min(soma, inf);
        for(int x : caras[i])
            soma -= x, ativos.push(x);
        while(soma < 0)
            soma += ativos.top(), ativos.pop(), ans++;
    }
    return ans;
}

int main() {
    int n, k; scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        int l, d; scanf("%d %d", &l, &d);
        caras[d].push_back(l);
    }
    ll l = 1, r = inf, ans = 0;
    while(l <= r) {
        ll m = (l+r)>>1;
        if(qtd(m) <= k)
            ans = m, r = m-1;
        else
            l = m+1;
    }
    printf("%lld\n", ans);
}
