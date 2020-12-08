#include "dreaming.h"
#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

vector<pii> g[maxn];
pair<pii,pii> top[maxn];
bool mark[maxn];
int ans, diam;

int dfs(int u, int p) {
	mark[u] = 1;
	for(pii pp : g[u]) {
		int v = pp.ff, w = pp.ss;
		if(v != p) {
			int val = dfs(v, u) + w;
			if(val > top[u].ff.ff) top[u].ss = top[u].ff, top[u].ff = {val, v};
			else if(val > top[u].ss.ff) top[u].ss = {val, v};
		}
	}
	diam = max(diam, top[u].ff.ff + top[u].ss.ff);
	return top[u].ff.ff;
}

void dfs2(int u, int p, int up) {
	ans = min(ans, max(top[u].ff.ff, up));
	for(pii pp : g[u]) {
		int v = pp.ff, w = pp.ss;
		if(v != p)
			dfs2(v, u,w + max(up,
				(v != top[u].ff.ss?top[u].ff.ff:top[u].ss.ff)));
	}
}

struct ANS
{
	int a, b, c;
	void upd(int x) {
		if(x >= a) c = b, b = a, a = x;
		else if(x >= b) c = b, b = x;
		else if(x >= c) c = x;
	}
	inline int get(int x, int comp) { return !comp?0:(comp==1?(a+b+x):(max(a+b+x, b+c+2*x))); }
} opa;

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
	for(int i = 0; i < M; i++)
		g[A[i]].pb({B[i], T[i]}), g[B[i]].pb({A[i], T[i]});
	int c = -1;
	for(int i = 0; i < N; i++)
		if(!mark[i])
			++c, ans = inf, dfs(i, -1), dfs2(i, -1, 0), opa.upd(ans);
	return max(opa.get(L, c), diam);
}
