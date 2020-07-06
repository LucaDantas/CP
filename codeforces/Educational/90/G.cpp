#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
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
constexpr int MAXN = 4e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int cnt[MAXN];

set<pii> s;
set<int> massa;

int tree[4*MAXN], lazy[4*MAXN];

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = i;
		return;
	}
	int m = (i+j) >> 1;
	build(2*node, i, m); build(2*node+1, m+1, j);
	tree[node] = max(tree[2*node], tree[2*node+1]);
}

void flush(int node, int i, int j) {
	if(!lazy[node]) return;
	if(i != j) {
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}
	tree[node] += lazy[node];
	lazy[node] = 0;
}

void upd(int node, int i, int j, int l, int r, int v) {
	flush(node, i, j);
	if(i > r || j < l) return;
	if(i >= l && j <= r) {
		lazy[node] += v;
		flush(node, i, j);
		return;
	}
	int m = (i+j) >> 1;
	upd(2*node, i, m, l, r, v);
	upd(2*node+1, m+1, j, l, r, v);
	tree[node] = max(tree[2*node], tree[2*node+1]);
}

int query(int node, int i, int j, int l, int r) {
	flush(node, i, j);
	if(i > r || j < l) return 0;
	if(i >= l && j <= r) return tree[node];
	int m = (i+j) >> 1;
	return max(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
}

int main() {
	int n, k, m;
	scanf("%d %d %d", &n, &k, &m);
	build(1,1,2*n);
	while(m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		int pos = abs(x-k) + y;
		pii p = make_pair(x,y);
		if(s.count(p)) {
			--cnt[pos];
			if(cnt[pos] == 0) massa.erase(pos);
			upd(1,1,2*n,1,pos,-1);
			s.erase(p);
		}
		else {
			++cnt[pos];
			if(cnt[pos] == 1) massa.insert(pos);
			upd(1,1,2*n,1,pos,1);
			s.insert(p);
		}
		if(massa.empty()) printf("0\n");
		else {
			int ans = query(1,1,2*n,1,*massa.rbegin());
			printf("%d\n", max(0,ans - n - 1));
		}
	}
}
