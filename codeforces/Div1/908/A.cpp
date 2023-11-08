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
#define sz(a) ((int)(a).size())
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

vector<int> g[maxn];
bool mark[maxn];

bool dfs(int u, int k) {
    // printf("dfs %d %d\n", u, k);
    if(!k) return 1;
    mark[u] = 1;
    bool ok = 0;
    for(int v : g[u]) {
        if(mark[v]) return 1;
        ok |= dfs(v, k-1);
    }
    return ok;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k; scanf("%d %d", &n, &k);
        vector<int> a(n);
        for(int& x : a)
            scanf("%d", &x);
        for(int i = 0; i < n; i++) {
            if(a[i] > n) continue;
            int dist = ((i+1) - a[i] + n) % n;
            int fim = (dist + a[i]) % n;
            // printf("%d %d\n", dist, fim);
            g[fim].push_back(dist); // faco o grafo reverso ja
        }
        puts(dfs(0, k) ? "Yes" : "No");
        for(int i = 0; i <= n; i++)
            g[i].clear(), mark[i] = 0;
    }
}
