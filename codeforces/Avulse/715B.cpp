#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using piii = pair<pii,int>;
using pli = pair<ll,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e3+10, inf = 0x3f3f3f3f;

vector<pii> g[maxn], g_er[maxn], er;
vector<piii> normal;

map<pii,int> edges;

ll dist[maxn];
bool mark[maxn];

void dijkstra(int s) {
	for(int i = 0; i < maxn; i++)
		dist[i] = inf, mark[i] = 0;
	dist[s] = 0;
	priority_queue<pli, vector<pli>, greater<pli>> q;
	q.push({0, s});
	while(q.size()) {
		int u = q.top().ss; q.pop();
		if(mark[u]) continue;
		mark[u] = 1;
		for(pii pp : g[u]) {
			auto [v, w] = pp;
			if(dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				q.push({dist[v], v});
			}
		}
		for(pii pp : g_er[u]) {
			auto [v, w] = pp;
			if(dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				q.push({dist[v], v});
			}
		}
	}
}

int main() {
	int n, M, L, s, t, cnt = 0; scanf("%d %d %d %d %d", &n, &M, &L, &s, &t);
	for(int i = 0; i < M; i++) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		if(w) g[u].pb({v, w}), g[v].pb({u, w}), normal.pb({{u, v}, w});
		else g_er[u].pb({v, 0}), g_er[v].pb({u, 0}), er.pb({u, v}),
			edges[make_pair(u, v)] = cnt, edges[make_pair(v, u)] = cnt++;
	}
	int l = 0, r = cnt, ans = 0;
	while(l <= r) {
		int m = (l+r) >> 1;
		for(int i = 0; i < n; i++) {
			for(pii& x : g_er[i]) {
				if(edges[make_pair(i, x.ff)] < m) x.ss = 1;
				else x.ss = L+1;
			}
		}
		dijkstra(s);
		if(dist[t] <= L) {
			ans = m;
			r = m-1;
		} else l = m+1;
	}
	if(!ans && dist[t] != L) {puts("NO"); return 0;}
	puts("YES");
	for(piii x : normal)
		printf("%d %d %d\n", x.ff.ff, x.ff.ss, x.ss);
	for(int i = 0; i < n; i++) {
		for(pii& x : g_er[i]) {
			if(edges[make_pair(i, x.ff)] < ans) x.ss = 1;
			else x.ss = L+1;
		}
	}
	dijkstra(s);
	--ans;
	for(int i = 0; i < cnt; i++) {
		int val = 1+(i<ans?0:i==ans?L-(int)dist[t]:L);
		printf("%d %d %d\n", er[i].ff, er[i].ss, val);
	}
}