#include <bits/stdc++.h>
using namespace std;

#define inv(n) power(n, mod-2)

int mod, n;
constexpr int maxn = 2010;

vector<int> g[maxn];

int power(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans = (int)(1ll * ans * b % mod);
        b = (int)(1ll * b * b % mod);
        e >>= 1;
    }
    return ans;
}

inline void mult(int& a, int b) { a = (int)(1ll * a * b % mod); }
inline void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }
inline void sub(int& a, int b) { a -= b; if(a < 0) a += mod; }
int product(int a, int b) { mult(a, b); return a; }

int f[maxn], invf[maxn];

void calc() {
    f[0] = invf[0] = f[1] = invf[1] = 1;
    for(int i = 2; i < maxn; i++)
        f[i] = product(i, f[i-1]), invf[i] = inv(f[i]);
}

int choose(int a, int b) { return product(f[a], product(invf[a-b], invf[b])); }

int ans[maxn], dp[maxn][maxn], S[maxn][maxn], prod[maxn], pref[maxn]; // pref is the prefix sum in j of { prod_child(S_j) / S_j_v }, used as an auxiliary every time when combining nodes

// tava tendo o erro de as vezes a soma dar 0 mod o valor que eu quero ai eu nao consigo tirar o produto e no fim da merda
void dfs(int u, int p) {
    static int tem0[maxn];
    for(int v : g[u]) if(v != p)
        dfs(v, u);

    for(int j = 1; j < n; j++)
        prod[j] = 1, tem0[j] = 0;

    for(int v : g[u]) if(v != p)
        for(int j = 1; j < n; j++)
            if(S[v][j] || tem0[j])
                mult(prod[j], S[v][j]);
            else
                tem0[j] = 1;

    for(int i = 1; i < n; i++)
        dp[u][i] = prod[i] * !tem0[i];

    if(u != 1) for(int v : g[u]) if(v != p) {
        for(int j = 1; j < n; j++)
            pref[j] = tem0[j] ? (S[v][j] == 0) * prod[j] : product(prod[j], inv(S[v][j])), add(pref[j], pref[j-1]);
        for(int i = 1; i < n; i++)
            add(dp[u][i], product(dp[v][i], pref[i-1]));
    }

    for(int i = 1; i < n; i++)
        S[u][i] = dp[u][i], add(S[u][i], S[u][i-1]);
}

int main() {
    scanf("%d %d", &n, &mod);
    for(int i = 1, u, v; i < n; i++)
        scanf("%d %d", &u, &v), g[u].push_back(v), g[v].push_back(u);
    dfs(1, 0);
    
    calc();
    for(int i = 1; i < n; i++) {
        ans[i] = dp[1][i];
        for(int j = 1; j < i; j++)
            sub(ans[i], product(choose(i, j), ans[j]));
        printf("%d ", ans[i]);
    }
    puts("");
}

