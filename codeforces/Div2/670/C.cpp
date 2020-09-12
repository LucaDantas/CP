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
// #define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

vi g[maxn];
int n, sz[maxn];
int ok, pai;
int leaf, pai_leaf;

void dfs(int u, int p) {
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    if(sz[u] == n/2) assert(!ok), ok = u, pai = p;
}

void find(int u, int p) {
    if(g[u].size() == 1) leaf = u, pai_leaf = p;
    else if(g[u][0] == p) find(g[u][1], u);
    else find(g[u][0], u);
}

void SOLVE() {
    cin >> n;
    ok = leaf = pai = pai_leaf = 0;
    for(int i = 0; i < n+5; i++) {
        g[i].clear();
        sz[i] = 0;
    }
    pii example;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
        example = {u, v};
    }
    if(n&1) {
        cout << example.ff << ' ' << example.ss << '\n';
        cout << example.ff << ' ' << example.ss << '\n';
        return;
    }
    dfs(1, 0);
    if(!ok) {
        cout << example.ff << ' ' << example.ss << '\n';
        cout << example.ff << ' ' << example.ss << '\n';
        return;
    }
    find(ok, pai);
    assert(leaf);
    cout << leaf << ' ' << pai_leaf << '\n';
    cout << leaf << ' ' << pai << '\n';
}

int main() {
    fast;
	int t; cin >> t;
    while(t--) SOLVE();
}
