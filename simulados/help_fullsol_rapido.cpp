// Tive q usar a seg de Benq pq com a minha sem otimização fdd
// dava TLE
#include<bits/stdc++.h>
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

int n, K;

struct mi {
	int v; explicit operator int() const { return v; }
	mi(long long _v) : v(_v%mod) { v += (v<0)*mod; }
	mi() : mi(0) {}
};
mi operator+(mi a, mi b) { return mi(a.v+b.v); }
mi operator-(mi a, mi b) { return mi(a.v-b.v); }
mi operator*(mi a, mi b) { return mi(1ll*a.v*b.v); }

mi pot[maxn], fat[11], inv_fat[11];

typedef array<mi,11> T;

struct SegmentTree
{
	T seg[4*maxn];
	mi lazy[4*maxn];

	void push(int ind, int L, int R) {
		if (lazy[ind].v == 1) return;
		for (int i = 0; i <= K; ++i) seg[ind][i] = seg[ind][i]*lazy[ind];
		if (L != R) {
			lazy[2*ind] = lazy[2*ind]*lazy[ind];
			lazy[2*ind+1] = lazy[2*ind+1]*lazy[ind];
		}
		lazy[ind] = 1;
	}
	 
	void mul(int pos, int ind, int L, int R) {
		push(ind,L,R);
		if (pos > R) return;
		if (pos <= L) {
			lazy[ind] = 2;
			push(ind,L,R);
			return;
		}
		int M = (L+R)/2;
		mul(pos,2*ind,L,M); mul(pos,2*ind+1,M+1,R);
		for (int i = 0; i <= K; ++i) seg[ind][i] = seg[2*ind][i]+seg[2*ind+1][i];
	}
	 
	void upd(int pos, const T& val, int ind, int L, int R) {
		push(ind,L,R);
		if (pos < L || pos > R) return;
		for (int i = 0; i <= K; ++i) seg[ind][i] = seg[ind][i]+val[i];
		if (L == R) return;
		int M = (L+R)/2;
		if (pos <= M) upd(pos,val,2*ind,L,M);
		else upd(pos,val,2*ind+1,M+1,R);
	}
	 
	void query(int lo, int hi, T& t, int ind, int L, int R) {
		push(ind,L,R);
		if (hi < L || lo > R) return;
		if (lo <= L && R <= hi) { 
			for (int i = 0; i <= K; ++i) t[i] = t[i]+seg[ind][i]; 
			return; 
		}
		int M = (L+R)/2;
		query(lo,hi,t,2*ind,L,M); query(lo,hi,t,2*ind+1,M+1,R);
	}
} seg;

mi power(mi b, int e) {
	mi ans = 1;
	while(e) {
		if(e&1) ans = ans * b;
		b = b * b;
		e >>= 1;
	}
	return ans;
}

void calc() {
	fat[0] = inv_fat[0] = pot[0] = 1;
	for(int i = 1; i < 11; i++)
		fat[i] = mi(i) * fat[i-1],
		inv_fat[i] = power(fat[i], mod-2);
	for(int i = 1; i < maxn; i++)
		pot[i] = mi(2)*pot[i-1];
}

mi choose(int a, int b) {
	if(b > a) return 0;
	return fat[a] * inv_fat[a-b] * inv_fat[b];
}

int	main() {
	calc();
	in = fopen("help.in", "r");
	out = fopen("help.out", "w");
	fscanf(in, "%d %d", &n, &K);
	
	for(int i = 0; i < n; i++)
		fscanf(in, "%d %d", &events[i].l, &events[i].r);
	sort(events, events+n);
	
	for(int i = 0; i < n; i++) {
		T dp;
		seg.query(events[i].l, events[i].r, dp, 1, 1, 2*n);
		seg.mul(events[i].r, 1, 1, 2*n);

		T val;
		seg.query(1, events[i].l-1, val, 1, 1, 2*n);

		for(int k = 0; k <= K; k++) {
			// quantos eu boto em mim
			for(int j = 0; j+k <= K; j++) {
				// quantos eu pego do anterior
				dp[j+k] = dp[j+k] + choose(j+k, j)*val[j];
			}
			dp[k] = dp[k] + 1;
		}

		seg.upd(events[i].r, dp, 1, 1, 2*n);
	}
	
	T ans;
	seg.query(1, 2*n, ans, 1, 1, 2*n);
	
	fprintf(out, "%d\n", ans[K].v);
	fprintf(stderr, "%d\n", ans[K].v);
}