#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back

constexpr int maxn = 3e5+10;

int color[maxn], match[maxn];
bool mark[maxn];

vector<int> g[maxn];

bool dfs(int u) {
	mark[u] = 1;

	if(color[u]) {
		if(match[u])
			return dfs(match[u]);
		return 1;
	}

	for(int v : g[u]) {
		if(mark[v] || !dfs(v)) continue;
		match[u] = v, match[v] = u;
		return 1;
	}

	return 0;
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

	int ans = 0;
	for(int i = 1; i < ptr; i++) {
		if(color[i] || match[i]) continue;
		memset(mark, 0, sizeof mark);
		ans += dfs(i);
	}

	printf("%d\n", ans);

	memset(mark, 0, sizeof mark);

	for(int i = 1; i < ptr; i++) {
		if(color[i] || match[i] || mark[i]) continue;
		dfs2(i);
	}

	for(int i = 1; i < ptr; i++)
		if(!in[i] && !color[i]) printf("%d %d DESNO\n", sv[i].first+1, sv[i].second+1);
	for(int x : t)
		printf("%d %d DOLJE\n", sv[x].first+1, sv[x].second+1);	
}