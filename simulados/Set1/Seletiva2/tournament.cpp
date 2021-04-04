#include<cstdio>
#include<set>
using namespace std;
constexpr int maxn = 1e5+10, logn = 20;

struct BIT
{
	int bit[maxn];
	void upd(int x, int v) {
		for(; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
	int bs(int v) {
		int pos = 0, st = v;
		for(int l = logn; l >= 0; l--) {
			if(pos + (1 << l) >= maxn) continue;
			if(bit[pos + (1 << l)] < v) {
				pos += (1 << l);
				v -= bit[pos];
			}
		}
		return pos+(st>0);
	}
} bit;

struct SegmentTree
{
	int tree[4*maxn], a[maxn];
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
	int query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return max(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
	}
} seg;

int s[maxn], e[maxn], pref[maxn];

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
	set<int> st;
	for(int i = 1; i <= N; i++)
		bit.upd(i, 1), st.insert(i), seg.a[i] = K[i-1];

	seg.build(1, 1, N-1);

	for(int i = 0; i < C; i++) {
		++E[i], ++S[i];
		s[i] = bit.bs(S[i]-1) + 1;
		e[i] = bit.bs(E[i]);
		auto it = st.lower_bound(s[i]);
		while(next(it) != st.end() && *next(it) <= e[i])
			bit.upd(*it, -1), it = st.erase(it);

		int v = seg.query(1, 1, N-1, s[i], e[i]-1);
		if(v < R) ++pref[s[i]], --pref[e[i]+1];
	}
	int ans = 0;
	for(int i = 1; i <= N; i++) {
		pref[i] += pref[i-1];
		if(pref[ans] < pref[i])
			ans = i;
	}
	return max(0, ans-1);
}
