#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second
#define all(a) (a).begin(), (a).end()
#define pb push_back

constexpr int maxn = 3e5+10;

vector<int> g[maxn], lines[maxn], ord;
queue<int> q;
int go[maxn], gt[maxn], in[maxn], out[maxn], t;

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
	int itv(int l, int r) { return query(r) - (l==1?0:query(l-1)); }
} bit;

struct DSU
{
	int pai[maxn], peso[maxn]; vector<int> grp[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1, grp[i] = {i};}
	int find(int x) {return x==pai[x]?x:pai[x]=find(pai[x]);}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		for(int x : grp[b])
			grp[a].pb(x);
		grp[b].clear();
	}
	int rm(int x) { return --peso[find(x)]; }
	vector<int> ordenado(int x) {
		vector<int> ans;
		x = find(x);
		int s = 0;
		for(int u : grp[x])
			if(!gt[u]) s = u;
		while(s) {
			if(bit.itv(in[s], out[s])) {puts("0"); exit(0);}
			bit.upd(in[s], 1);
			ans.pb(s);
			s = go[s];
		}
		for(int x : ans)
			bit.upd(in[x], -1);
		return ans;
	}
} dsu;

void dfs(int u) {
	in[u] = ++t;
	for(int v : g[u])
		dfs(v);
	out[u] = t;
}

int main() {
	int n, k, cnt = 0; scanf("%d %d", &n, &k);
	for(int i = 0, p; i < n; i++)
		scanf("%d", &p), g[p].pb(i+1);
	dfs(g[0][0]);
	for(int i = 0; i < k; i++) {
		int x, y; scanf("%d %d", &x, &y);
		if(go[x] || gt[y]) {puts("0"); return 0;}
		go[x] = y; gt[y] = x;
		dsu.join(x, y);
	}
	q.push(g[0][0]);
	while(q.size()) {
		int u = q.front(); q.pop();
		if(!go[u] && !gt[u]) {
			ord.pb(u);
			for(int v : g[u])
				q.push(v);
			continue;
		}
		if(!dsu.rm(u)) {
			vector<int> ordenado = dsu.ordenado(u);
			for(int x : ordenado) {
				ord.pb(x);
				for(int v : g[x])
					if(dsu.find(v) != dsu.find(u))
						q.push(v);
			}
		} else {
			for(int v : g[u])
				if(dsu.find(v) == dsu.find(u))
					q.push(v);
		}
	}
	if(ord.size() != n) {puts("0"); return 0;}
	for(int x : ord)
		printf("%d ", x);
	printf("\n");
}