#include<cstdio>
#include<utility>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cassert>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10, mod = 1000000007;

using pii = pair<int,int>;

FILE *in, *out;

struct Event {
	int l, r;
	bool operator<(Event a) {
		return l < a.l;
	}
} events[maxn];

inline void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

int dp[11], pot[maxn], fat[11], inv_fat[11], n;

struct SegmentTree
{
	int tree[4*maxn], lazy[4*maxn], val;
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;
		if(i != j) {
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		tree[node] = (int)(1ll * tree[node] * pot[lazy[node]] % mod);
		lazy[node] = 0;
	}
	void upd(int pos, int v) {
		upd(1, 1, 2*n, pos, v);
	}
	void upd(int node, int i, int j, int pos, int v) {
		flush(node, i, j);
		if(i == j) return (void)(tree[node] += v);
		int m = (i+j) >> 1;
		if(pos <= m) upd(2*node, i, m, pos, v);
		else upd(2*node+1, m+1, j, pos, v);
		flush(2*node, i, m); flush(2*node+1, m+1, j);
		tree[node] = tree[2*node] + tree[2*node+1];
		if(tree[node] >= mod) tree[node] -= mod;
	}
	int query(int l, int r) {
		val = 0;
		query(1, 1, 2*n, l, r);
		return val;
	}
	void query(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(add(val, tree[node]));
		int m = (i+j) >> 1;
		query(2*node, i, m, l, r);
		query(2*node+1, m+1, j, l, r);
	}
	void duplica(int l, int r) {
		duplica(1, 1, 2*n, l, r);
	}
	void duplica(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(++lazy[node], flush(node, i, j));
		int m = (i+j) >> 1;
		duplica(2*node, i, m, l, r);
		duplica(2*node+1, m+1, j, l, r);
		tree[node] = tree[2*node] + tree[2*node+1];
		if(tree[node] >= mod) tree[node] -= mod;
	}
} seg[11]; // guarda pref da dp pra cada K

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

void calc() {
	fat[0] = inv_fat[0] = pot[0] =  1;
	for(int i = 1; i < 11; i++)
		fat[i] = (int)(1ll * i * fat[i-1] % mod),
		inv_fat[i] = power(fat[i], mod-2);
	for(int i = 1; i < maxn; i++)
		pot[i] = 2*pot[i-1]%mod;
}

int choose(int a, int b) {
	if(b > a) return 0;
	return (int)((1ll * fat[a] * inv_fat[a-b] % mod) * inv_fat[b] % mod);
}

int	main() {
	calc();
	in = fopen("help.in", "r");
	out = fopen("help.out", "w");
	int K, ans = 0; fscanf(in, "%d %d", &n, &K);
	for(int i = 0; i < n; i++)
		fscanf(in, "%d %d", &events[i].l, &events[i].r);
	sort(events, events+n);
	for(int i = 0; i < n; i++) {
		for(int k = 0; k <= K; k++)
			dp[k] = seg[k].query(events[i].l, events[i].r),
			seg[k].duplica(events[i].r, 2*n);

		// eu me colocando sozinho
		int val[11];
		for(int j = 0; j <= K; j++)
			val[j] = seg[j].query(1, events[i].l-1);
		for(int k = 0; k <= K; k++) {
			// quantos eu boto em mim
			for(int j = 0; j+k <= K; j++) {
				// quantos eu pego do anterior
				add(dp[j+k], (int)(1ll*choose(j+k, j)*val[j]%mod));
			}
			add(dp[k], 1);
		}

		for(int k = 0; k <= K; k++)
			seg[k].upd(events[i].r, dp[k]);
	}
	
	ans = seg[K].query(1, 2*n);
	
	fprintf(out, "%d\n", ans);
	fprintf(stderr, "%d\n", ans);
}