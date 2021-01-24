#include<bits/stdc++.h>
using namespace std;
 
using pii = pair<int,int>;
 
#define pb push_back
 
constexpr int maxn = 3e5+10;
 
int color[maxn], match[maxn], dist[maxn];
bool mark[maxn];

vector<int> g[maxn];

bool dfs(int u) {
	mark[u] = 1;

	if(color[u]) {
		if(match[u])
			return dist[match[u]] == dist[u]+1 && dfs(match[u]);
		return 1;
	}

	for(int v : g[u]) {
		if(mark[v] || dist[v] != dist[u]+1 || !dfs(v)) continue;
		match[u] = v, match[v] = u;
		return 1;
	}

	return 0;
}

bool bfs(int n) {
	memset(mark, 0, sizeof mark);
	memset(dist, 0, sizeof dist);
	queue<int> q;
 
	for(int i = 1; i <= n; i++)
		if(!color[i] && !match[i]) q.push(i), mark[i] = 1;

	int lim = maxn;

	while(q.size() && dist[q.front()] <= lim) {
		int u = q.front(); q.pop();

		if(color[u]) {
			if(!match[u]) lim = dist[u];
			else if(!mark[match[u]]) dist[match[u]] = dist[u]+1, q.push(match[u]);
			continue;
		}

		for(int v : g[u]) {
			if(mark[v]) continue;
			mark[v] = 1;
			dist[v] = dist[u]+1;
			q.push(v);
		}
	}

	return lim != maxn;
}

int hk(int n) {
	int ans = 0;
	while(bfs(n)) {
		memset(mark, 0, sizeof mark);

		for(int i = 1; i <= n; i++)
			if(!color[i] && !match[i] && !mark[i])
				ans += dfs(i);

	}
	return ans;
}

bool in[maxn];

vector<int> t;

void dfs2(int u) {
	mark[u] = 1;

	if(color[u]) return (void)(t.pb(u), dfs2(match[u]));

	in[u] = 1;
	for(int v : g[u]) {
		if(mark[v]) continue;
		dfs2(v);
	}
}

pii sv[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);

	vector<int> last_ptr(m), ultimo_c(m);
	ultimo_c[0] = 1;
	int atras = 0, now = 0, ptr = 1;

	for(int k = 0; k < n; k++) {
		for(int i = 0; i < m; i++) {
			char c; scanf(" %c", &c);
			int a = c-'0';
			if(a && !atras) now = ptr++;
			if(a && !ultimo_c[i]) ++color[ptr], last_ptr[i] = ptr++;
			else if(!a) {
				g[now].pb(last_ptr[i]), g[last_ptr[i]].pb(now);
				if(sv[now] == make_pair(0, 0))
					sv[now] = {k, i-1};
				if(sv[last_ptr[i]] == make_pair(0, 0))
					sv[last_ptr[i]] = {k-1, i};
			}
			atras = a;
			ultimo_c[i] = a;
		}
	}

	int ans = hk(ptr-1);

	memset(mark, 0, sizeof mark);

	for(int i = 1; i < ptr; i++) {
		if(color[i] || match[i] || mark[i]) continue;
		dfs2(i);
	}

	printf("%d\n", ans);
	for(int i = 1; i < ptr; i++)
		if(!in[i] && !color[i]) printf("%d %d DESNO\n", sv[i].first+1, sv[i].second+1);
	for(int x : t)
		printf("%d %d DOLJE\n", sv[x].first+1, sv[x].second+1);	
}