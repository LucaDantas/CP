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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

struct SegmentTree
{
	int tree[4*maxn], lazy[4*maxn], a[maxn];
	void build(int node, int i, int j) {
		lazy[node] = -1;
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	void flush(int node, int i, int j) {
		if(lazy[node] == -1) return;
		if(i != j)
			lazy[2*node] = lazy[2*node+1] = lazy[node];
		tree[node] = (j-i+1)*lazy[node];
		lazy[node] = -1;
	}
	void upd(int node, int i, int j, int l, int r, int v) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) {
			lazy[node] = v;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(2*node, i, m, l, r, v); upd(2*node+1, m+1, j, l, r, v);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	int query(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return query(2*node, i, m, l, r)+query(2*node+1, m+1, j, l, r);
	}
} seg;

int main() {
	fast;
	int T; cin >> T;
	while(T--) {
		int n, q; cin >> n >> q;
		string s, t; cin >> s >> t;
		for(int i = 0; i < n; i++)
			seg.a[i] = t[i]-'0';
		seg.build(1, 0, n-1);
		vector<pii> qry(q);
		for(pii& x : qry)
			cin >> x.ff >> x.ss;
		reverse(all(qry));
		bool ok = 1;
		for(pii x : qry) {
			--x.ff, --x.ss;
			auto [l, r] = x;
			int qtd1 = seg.query(1, 0, n-1, l, r), qtd0 = r-l+1-qtd1;
			int cor = qtd0>qtd1?0:1, qtd = min(qtd0, qtd1), lim = (r-l)/2;
			if(qtd > lim) {ok = 0; break;}
			seg.upd(1, 0, n-1, l, r, cor);
		}
		for(int i = 0; i < n; i++)
			if(seg.query(1, 0, n-1, i, i) != s[i]-'0')
				{ok = 0; break;}
		cout << (ok?"YES\n":"NO\n");
	}
}
