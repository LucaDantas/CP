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
	int a[maxn], lazy[4*maxn], ans = 0;
	ll tree[4*maxn][3];
	void build(int node, int i, int j) {
		if(i == j)
			return (void)(tree[node][0] = tree[node][1] = tree[node][2] = a[i]);
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		
		tree[node][0] = tree[2*node][0]+tree[2*node+1][0];
		tree[node][1] = min(tree[2*node][1], tree[2*node+1][1]);
		tree[node][2] = max(tree[2*node][2], tree[2*node+1][2]);
	}
	void flush(int node, int i, int j) {
		if(!lazy[node])
			return;
		if(i != j)
			lazy[2*node] = lazy[2*node+1] = lazy[node];
		tree[node][0] = 1ll*(j-i+1)*lazy[node];
		tree[node][1] = lazy[node];
		tree[node][2] = lazy[node];
		lazy[node] = 0;
	}
	void upd(int node, int i, int j, int r, int val) {
		flush(node, i, j);
		if(i > r || tree[node][1] > val) return;
		if(j <= r && tree[node][2] <= val)
			return (void)(lazy[node] = val, flush(node, i, j));
		
		int m = (i+j) >> 1;
		upd(2*node, i, m, r, val); upd(2*node+1, m+1, j, r, val);

		tree[node][0] = tree[2*node][0]+tree[2*node+1][0];
		tree[node][1] = min(tree[2*node][1], tree[2*node+1][1]);
		tree[node][2] = max(tree[2*node][2], tree[2*node+1][2]);
	}
	int find(int node, int i, int j, int l, int val) {
		flush(node, i, j);
		if(j < l || tree[node][1] > val) return 0;
		if(i >= l && tree[node][0] <= val) {
			ans += j-i+1;
			return (int)tree[node][0];
		}
		int m = (i+j) >> 1;
		int esq = find(2*node, i, m, l, val);
		return esq+find(2*node+1, m+1, j, l, val-esq);
	}
} seg;

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d", &seg.a[i]);
	seg.build(1, 1, n);
	while(q--) {
		int t, x, y; scanf("%d %d %d", &t, &x, &y);
		if(t&1)
			seg.upd(1, 1, n, x, y);
		else {
			seg.ans = 0;
			seg.find(1, 1, n, x, y);
			printf("%d\n", seg.ans);
		}
	}
}
