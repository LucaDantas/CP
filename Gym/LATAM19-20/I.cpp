#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2010, mod = 1e9+7;

int dp[maxn], in[maxn];
bool mark[maxn];

vector<int> g[maxn];

int main() {
    int n, l; scanf("%d %d", &n, &l);
    for(int i = 1; i <= l; i++) {
        int k; scanf("%d", &k);
        g[i].resize(k);
        for(int& x : g[i])
            scanf("%d", &x), ++in[x];
    }
    queue<int> q;
    for(int i = 1; i <= l; i++)
        if(!in[i]) q.push(i);
    dp[1] = 1, mark[1] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int v : g[u]) {
            dp[v] += dp[u], dp[v] %= mod;
            mark[v] |= mark[u];
            if(!(--in[v]))
                q.push(v);
        }
    }
    int a1 = 0, a2 = 0;
    for(int i = l+1; i <= n; i++)
        a1 += dp[i], a1 %= mod, a2 += mark[i];
    printf("%d %d\n", a1, a2);
}
