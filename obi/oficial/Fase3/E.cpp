#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using piii = pair<pii, int>;
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
constexpr int maxn = 2e4 + 10;
constexpr int mod = 1000000007;

vector<pii> g[maxn];
vector<piii> g_comp[maxn];

int d[maxn], pos[maxn], mark[maxn], comp[maxn], tam[maxn], tem[maxn], cnt;

vector<int> here;

void dfs(int u, int p) {
	mark[u] = 1;
	pos[u] = sz(here);
	here.pb(u);
	for(pii pp : g[u]) {
		int v = pp.ff, w = pp.ss;
		if(v == p || mark[v] == 2) continue;
		if(mark[v] == 1) {
			++cnt;
			tam[cnt] = d[u] - d[v] + w;
			for(int i = pos[v]; i < sz(here); i++) {
				tem[here[i]] = 1;
				comp[here[i]] = cnt;
			}
			for(int i = pos[v]; i < sz(here); i++) {
				for(pii gld : g[here[i]]) {
					int x = gld.ff, w2 = gld.ss;
					if(comp[x] == cnt) continue;
					g_comp[cnt].pb({{here[i], x}, w2});
				}
			}
		} else {
			d[v] = d[u] + w;
			dfs(v, u);
		}
	}
	if(!tem[u]) {
		++cnt;
		tam[cnt] = 0; comp[u] = cnt;
		for(pii gld : g[u]) {
			int x = gld.ff, w2 = gld.ss;
			g_comp[cnt].pb({{u, x}, w2});
		}
	}
	here.pop_back();
	mark[u] = 2;
}

int dist[maxn];

void dijkstra(int s) {
	for(int i = 0; i <= cnt; i++)
		dist[i] = inf, mark[i] = 0;
	queue<pii> q;
	dist[comp[s]] = 0;
	q.push({0, s});
	while(q.size()) {
		int u = q.front().ss, c = comp[u]; q.pop();
		if(mark[c]) continue;
		mark[c] = 1;
		for(piii pp : g_comp[c]) {
			int from = pp.ff.ff, to = pp.ff.ss, w = pp.ss;
			int dist_go = min(abs(d[u] - d[from]), tam[c] - abs(d[u] - d[from])) + w;
			if(dist[comp[to]] > dist[c] + dist_go) {
				dist[comp[to]] = dist[c] + dist_go;
				q.push({dist[comp[to]], to});
			}
		}
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		g[a].pb({b, c});
		g[b].pb({a, c});
	}
	dfs(1, 0);

	int q; scanf("%d", &q);
	while(q--) {
		int x, t; scanf("%d %d", &x, &t);
		dijkstra(x);
		int ans = inf;
		for(int i = 1; i <= cnt; i++)
			if(tam[i] >= t)
				ans = min(ans, 2*dist[i] + tam[i]);
		printf("%d\n", ans<inf?ans:-1);
	}
}
