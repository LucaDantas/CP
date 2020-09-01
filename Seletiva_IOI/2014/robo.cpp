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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int n;

struct SegmentTree
{
	int tree[4*maxn], lazy[4*maxn];

	// tree(0) = something free / tree(1) = full
	// lazy(0) = clear / lazy(1) = activate everyone
	void flush(int node, int i, int j) {
		if(lazy[node] == -1) return;
		if(i != j) {
			lazy[2*node] = lazy[node];
			lazy[2*node+1] = lazy[node];
		}
		tree[node] = lazy[node];
		lazy[node] = -1;
	}

	void upd(int l, int r) {upd(1,0,n-1,l,r);}
	void upd(int node, int i, int j, int l, int r) {
		// turn the interval [l..r] on
		flush(node, i, j);
		if(l > j || r < i) return;
		if(l <= i && j <= r) {
			lazy[node] = 1;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(2*node, i, m, l, r);
		upd(2*node+1, m+1, j, l, r);
		tree[node] = min(tree[2*node], tree[2*node+1]);
	}

	void clear() {
		lazy[1] = 0;
		flush(1,0,n-1);
	}
} seg;

int main() {
	int x; scanf("%d %d", &n, &x);
	int ans = 1;
	for(int i = 1; i < x; i++) {
		int l, r; scanf("%d %d", &l, &r);
		seg.upd(l, r-1);
		if(seg.tree[1]) {
			seg.clear();
			seg.upd(l, r-1);
			ans += 2;
		}
	}
	printf("%d\n", ans);
}
