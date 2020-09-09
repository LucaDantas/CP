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

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 5e6 + 10;
constexpr int mod = 1000000007;

vector<pii> g[maxn]; // the graph is inverted such that the color of the edge defines the color of the vertex

int b[maxn], w[maxn], dp[maxn], col[maxn];

void init() {
    for(int i = 0; i < maxn; i++) {
        b[i] = w[i] = dp[i] = inf;
        col[i] = -1;
    }
}

int main() {
    init();
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, t; scanf("%d %d %d", &u, &v, &t);
        g[v].pb({u, t});
    }
    queue<int> q;
    b[n] = w[n] = dp[n] = col[n] = 0; // the end has no color
    q.push(n);
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(auto pp : g[u]) {
            int v = pp.ff, t = pp.ss;
            if(col[v] != -1) continue;
            if(t == 0 && b[v] == inf) b[v] = dp[u]+1;
            if(t == 1 && w[v] == inf) w[v] = dp[u]+1;
            if(b[v] + w[v] < inf) {
                if(b[v] <= w[v]) dp[v] = w[v], col[v] = 1;
                else dp[v] = b[v], col[v] = 0;
                q.push(v);
            }
        }
    }
    if(dp[1] != inf) printf("%d\n", dp[1]);
    else puts("-1");
    for(int i = 1; i <= n; i++) {
        if(col[i] != -1) printf("%d", col[i]);
        else if(b[i] == inf) printf("0");
        else printf("1");
    }
    puts("");
}
