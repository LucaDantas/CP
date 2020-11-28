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
constexpr int maxn = 1e5+10;
constexpr int mod = 1000000007;

int gcd(int a, int b) {return !b?a:gcd(b, a%b);}

int a[maxn];

struct SegmentTree
{
	struct Node
	{
		vector<pii> g[2];
		int gcd_td;
		ll ans;
	};
	Node tree[4*maxn];
	Node combine(Node l, Node r) {
		Node ret;
		ret.gcd_td = gcd(l.gcd_td, r.gcd_td);
		ret.ans = l.ans + r.ans;

		int ptr = sz(r.g[0])-1, t = 0;
		for(pii x : r.g[0]) t += x.ss;
		for(pii x : l.g[1]) {
			for(; ptr >= 0 && gcd(x.ff, r.g[0][ptr].ff) == 1; ptr--)
				t -= r.g[0][ptr].ss;
			ret.ans += 1ll*x.ss*t;
		}

		ret.g[0] = l.g[0];
		if(l.gcd_td > 1) {
			int last = l.gcd_td;
			for(pii x : r.g[0]) {
				int val = gcd(x.ff, last);
				if(val == 1) break;
				if(val != ret.g[0].back().ff)
					ret.g[0].pb({val, x.ss});
				else ret.g[0].back().ss += x.ss;
				last = val;
			}
		}
		ret.g[1] = r.g[1];
		if(r.gcd_td > 1) {
			int last = r.gcd_td;
			for(pii x : l.g[1]) {
				int val = gcd(x.ff, last);
				if(val == 1) break;
				if(val != ret.g[1].back().ff)
					ret.g[1].pb({val, x.ss});
				else ret.g[1].back().ss += x.ss;
				last = val;
			}
		}
		return ret;
	}
	void build(int node, int i, int j) {
		if(i == j) {
			tree[node].g[0].pb({a[i], 1}); tree[node].g[1].pb({a[i], 1});
			tree[node].gcd_td = a[i];
			tree[node].ans = a[i]>1;
			return;
		}
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = combine(tree[2*node], tree[2*node+1]);
	}
	void upd(int node, int i, int j, int pos, int v) {
		if(i == j) {
			a[i] = v;
			tree[node].g[0].clear(); tree[node].g[1].clear();
			tree[node].g[0].pb({a[i], 1}); tree[node].g[1].pb({a[i], 1});
			tree[node].gcd_td = a[i];
			tree[node].ans = a[i]>1;
			return;
		}
		int m = (i+j) >> 1;
		if(pos <= m) upd(2*node, i, m, pos, v);
		else upd(2*node+1, m+1, j, pos, v);
		tree[node] = combine(tree[2*node], tree[2*node+1]);
	}
	Node query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) {
			Node ret;
			ret.g[0] = {{1, 0}};
			ret.g[1] = {{1, 0}};
			ret.gcd_td = 1;
			ret.ans = 0;
			return ret;
		}
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return combine(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
	}
} seg;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	seg.build(1, 1, n);
	while(m--) {
		int t, x, y; scanf("%d %d %d", &t, &x, &y);
		if(t == 1)
			seg.upd(1, 1, n, x, y);
		else printf("%lld\n", seg.query(1, 1, n, x, y).ans);
	}
}
