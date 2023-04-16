
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 4e3+10;

map<int,int> id, id2; // pra poder colocar os caras no grafo sem ter q criar um negocio gigante
int cnt, back[maxn]; // codigo -> valor namoral

int get(int val) { return id.count(val) ? id[val] : (back[++cnt] = val, id[val] = cnt); }

int n, a[maxn];

int match[maxn], pai[maxn]; // salvo quem eh o melhor pra expandir
bool mark[maxn], mark2[maxn];

int dfs(int u) {
    mark[u] = 1;

    if(u > n)
        return !match[u] ? back[u] : dfs(match[u]);

    if(mark2[id2[a[u]]])
        return 0x3f3f3f3f;
    mark2[id2[a[u]]] = 1;

    int ans = 0x3f3f3f3f;
    for(int val = a[u]; ; val += a[u]) {
        int v = get(val);
        if(mark[v]) continue;
        int aq = dfs(v);
        if(aq < ans)
            ans = aq, pai[u] = v;
        if(!match[v]) break;
    }

    return ans;
}

void go(int u) {
    if(u > n)
        return (void)(!match[u] || (go(match[u]), 1));
    go(pai[u]);
    match[u] = pai[u];
    match[pai[u]] = u;
}

int main() {
    scanf("%d", &n); cnt = n;
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i), id2[a[i]] = i;
    for(int i = 1; i <= n; i++) {
        memset(mark, 0, sizeof mark);
        memset(mark2, 0, sizeof mark2);
        dfs(i);
        go(i);
    }
    long long ans = 0;
    for(int i = n+1; i <= cnt; i++)
        ans += match[i] ? back[i] : 0;
    printf("%lld\n", ans);
}
