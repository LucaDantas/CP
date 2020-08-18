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

int n;

struct SegmentTree {
	double tree[4*maxn];
	void update(int pos, double val) {
		update(1, 1, n, pos, val);
	}
	void update(int node, int i, int j, int pos, double val) {
		if(i == j) return (void)(tree[node] = val);
		int m = (i+j) >> 1;
		if(pos <= m) update(2*node, i, m, pos, val);
		else update(2*node+1, m+1, j, pos, val);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	double query(int l, int r) {
		return query(1, 1, n, l, r);
	}
	double query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return query(2*node, i, m, l, r) + query(2*node+1, m+1, j, l, r);
	}
} seg;

int in[maxn], out[maxn], aux;
vi g[maxn];

void dfs(int u, int p) {
	in[u] = ++aux;
	for(auto v : g[u])
		if(v != p)
			dfs(v, u);
	out[u] = aux;
}

int main() {
	scanf("%d", &n);
	rep(i,1,n) {int a, b; scanf("%d %d", &a, &b); g[a].pb(b); g[b].pb(a);}
	dfs(1, 0);
	int q; scanf("%d", &q);
	while(q--) {
		int t, x, y; scanf("%d %d %d", &t, &x, &y);
		if(t == 1) {
			seg.update(in[x], log((double)y));
		} else {
			double ans = seg.query(in[x], out[x]) - seg.query(in[y], out[y]);
			if(ans >= 20.8) puts("1000000000");
			else {
				ans = exp(ans);
				if(ans >= 1e9) puts("1000000000");
				else printf("%.10lf\n", ans);
			}
		}
	}
}
