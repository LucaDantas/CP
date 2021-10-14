#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>

constexpr int maxn = 2e5+10;

int N;

struct Seg {
	int tree[4*maxn], lazy[4*maxn];
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;
		if(i != j) lazy[node<<1] += lazy[node], lazy[node<<1|1] += lazy[node];
		tree[node] += lazy[node], lazy[node] = 0;
	}
	void upd(int node, int i, int j, int pos, int v) {
		flush(node, i, j);
		if(j < pos) return;
		if(i >= pos) return (void)(lazy[node] = v, flush(node, i, j));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, pos, v);
		upd(node<<1|1, m+1, j, pos, v);
		tree[node] = std::min(tree[node<<1], tree[node<<1|1]);
	}
	void upd(int pos, int v) { upd(1, 1, N, pos, v); }
	int first(int node, int i, int j) {
		flush(node, i, j);
		if(tree[node] >= 0) return -1;
		if(i == j) return i;
		int m = (i+j) >> 1;
		int qr = first(node<<1, i, m);
		if(qr == -1) return first(node<<1|1, m+1, j);
		return qr;
	}
} seg;

struct BIT {
	int bit[maxn];
	void upd(int x, int v) {
		seg.upd(x, v);
		for(; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
} bit;

std::set<int> atv, morto;

void add_a(int x) {
	int v = bit.query(x);
	if(v > 0) atv.insert(x), bit.upd(x, -1);
	else morto.insert(x);
	int pos = seg.first(1, 1, N);
	if(pos != -1)
		morto.insert(pos), bit.upd(pos, 1), atv.erase(pos);
}

void add_b(int x) {
	bit.upd(x, 1);
	auto it = morto.upper_bound(x);
	if(it != morto.end())
		atv.insert(*it), bit.upd(*it, -1), morto.erase(it);
}

int a[maxn], b[maxn], cnt;
bool mark[maxn];

int pref[maxn], suf[maxn], ans;

FILE *in, *out;

int main() {
	in = fopen("cardgame.in", "r");
	out = fopen("cardgame.out", "w");
	int n; fscanf(in, "%d", &n); N = 2*n;
	for(int i = 0; i < n; i++)
		fscanf(in, "%d", &a[i]), mark[a[i]] = 1;
	for(int i = 1; i <= 2*n; i++)
		if(!mark[i]) b[cnt++] = i;
	
	std::reverse(a, a+n);

	for(int i = 0; i < n; i++) {
		add_b(b[i]);
		add_a(a[i]);
		pref[i+1] = (int)atv.size();
	}

	std::reverse(a, a+n);
	std::reverse(b, b+n);
	for(int i = 0; i < n; i++)
		a[i] = 2*n+1 - a[i], b[i] = 2*n+1 - b[i];
	atv.clear(), morto.clear();
	memset(bit.bit, 0, sizeof bit.bit);
	memset(seg.tree, 0, sizeof seg.tree);
	memset(seg.lazy, 0, sizeof seg.lazy);
	
	for(int i = 0; i < n; i++) {
		add_a(a[i]);
		add_b(b[i]);
		suf[i+1] = (int)atv.size();
	}
	
	for(int i = 0; i <= n; i++)
		ans = std::max(ans, pref[i] + suf[n-i]);
	fprintf(out, "%d\n", ans);
}
