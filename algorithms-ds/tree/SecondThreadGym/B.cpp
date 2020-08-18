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
constexpr int maxn = 3e5 + 10;
constexpr int mod = 1000000007;

int dist[maxn], pai[maxn], n, diam;
vi g[maxn];

int bfs(int s) {
	queue<int> q;
	q.push(s); pai[s] = 0;
	dist[s] = 0;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(auto v : g[u])
			if(v != pai[u])
				dist[v] = dist[u]+1, pai[v] = u, q.push(v);
	}
	int val = s;
	rep(i,1,n+1)
		if(dist[i] > dist[val])
			val = i;
	return val;
}

bool in[maxn], ans[maxn], mark[maxn];
int dpt[maxn];

void dfs(int u, int lvl, int want) {
	mark[u] = 1;
	if(lvl == want)
		ans[u] = 1;
	for(auto v : g[u])
		if(!in[v] && !mark[v])
			dfs(v, lvl+1, want);
}

int main() {
	scanf("%d", &n);
	rep(i,1,n) {int a, b; scanf("%d %d", &a, &b); g[a].pb(b); g[b].pb(a);}
	int st = bfs(1), fim = bfs(st);
	diam = dist[fim];
	int now = fim, lvl = 0;
	while(now != st) {
		in[now] = 1;
		dpt[now] = min(lvl, diam-lvl);
		lvl++;
		now = pai[now];
	}
	in[st] = 1;
	rep(i,1,n+1) {
		if(in[i]) {
			dfs(i, 0, dpt[i]);
		}
	}
	rep(i,1,n+1) printf("%d\n", diam + ans[i]);
}
