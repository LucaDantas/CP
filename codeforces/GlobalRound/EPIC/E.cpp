#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 5e3 + 10;
constexpr int mod = 1000000007;

int a[maxn], depth[maxn];
ll ans;

vector<int> g[maxn];

map<int, ll> ativos[maxn];

void pre(int u, int p = 0) {
    for(int v : g[u]) if(v != p)
        depth[v] = depth[u]+1, pre(v, u);
}

void dfs(int u, int p = 0) {
    if(!g[u].size())
        return (void)(ativos[u][depth[u]] = inf);

    ll soma = 0;
    pii maior = {-0x3f3f3f3f, -0x3f3f3f3f};
    for(int v : g[u]) if(v != p) {
        soma += a[v];
        dfs(v, u);
        maior = max(maior, {sz(ativos[v]), v});
    }

    swap(ativos[u], ativos[maior.ss]);
    for(int v : g[u]) if(v != maior.ss)
        for(auto &it : ativos[v])
            ativos[u][it.first] = min(inf, ativos[u][it.first] + it.second);

    if(a[u] < soma)
        ativos[u][depth[u]] += soma - a[u];

    while(soma < a[u]) {
        auto it = ativos[u].begin();
        int add = min(1ll * a[u] - soma, it->second);
        soma += add;
        ans += 1ll * (it->first - depth[u]) * add;
        it->second -= add;
        if(!it->second)
            ativos[u].erase(it);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%d", a+i);
        for(int i = 2, x; i <= n; i++)
            scanf("%d", &x), g[x].push_back(i);
        pre(1);
        dfs(1);
        printf("%lld\n", ans);
        ans = 0;
        for(int i = 1; i <= n; i++)
            g[i].clear(), ativos[i].clear();
    }
}
