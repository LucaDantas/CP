#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back

constexpr int maxn = 5e5+10, logn = 20;

vector<pii> g[maxn];

int pai[maxn][logn];

int diam_cima[maxn], maior_cima[maxn], depth[maxn], edge_pai[maxn];

pii diam_baixo[maxn];

struct trio
{
	int a, b, c;
};

trio maior_baixo[maxn];

void upd(trio& pa, int val) {
	if(val > pa.a) pa.c = pa.b, pa.b = pa.a, pa.a = val;
	else if(val > pa.b) pa.c = pa.b, pa.b = val;
	else if(val > pa.c) pa.c = val;
}

void upd_par(pii& p, int val) {
	if(val > p.first) p.second = p.first, p.first = val;
	else if(val > p.second) p.second = val;
}

void dfs(int u, int p) {
	for(int l = 0; l < logn; l++)
		pai[u][l] = pai[pai[u][l-1]][l-1];
	
	// printf("u %d %d\n", u, p);

	for(auto [v, w] : g[u]) {
		if(v == p) continue;
		
		pai[v][0] = u;
		depth[v] = depth[u] + 1;
		edge_pai[v] = w;
		
		dfs(v, u);
		
		upd_par(diam_baixo[u], max(diam_baixo[v].first, maior_baixo[v].a + maior_baixo[v].b));

		upd(maior_baixo[u], maior_baixo[v].a + w);
	}
}

void calc_cima(int u, int p) {
	for(auto [v, w] : g[u]) {
		if(v == p) continue;

		maior_cima[v] = maior_cima[u] + w;
		diam_cima[v] = diam_cima[u];

		if(maior_baixo[v].a+w == maior_baixo[u].a) {
			// printf("FDD %d %d %d %d %d\n", u, v, maior_baixo[u].a, maior_baixo[v].a, v);
			maior_cima[v] = max(maior_cima[v], maior_baixo[u].b + w);
			diam_cima[v] = max(diam_cima[v], maior_baixo[u].b + max(maior_cima[u], maior_baixo[u].c));
		}
		else {
			// printf("FFD %d %d\n", u, v);
			// printf("uv %d %d %d %d %d\n", u, v, maior_baixo[u].a, maior_baixo[v].a, v);
			maior_cima[v] = max(maior_cima[v], maior_baixo[u].a + w);
			if(maior_baixo[u].b != maior_baixo[v].a+w)
				diam_cima[v] = max(diam_cima[v], maior_baixo[u].a + max(maior_cima[u], maior_baixo[u].b));
			else
				diam_cima[v] = max(diam_cima[v], maior_baixo[u].a + max(maior_cima[u], maior_baixo[u].c));
		}

		if(max(diam_baixo[v].first, maior_baixo[v].a+maior_baixo[v].b) == diam_baixo[u].first)
			diam_cima[v] = max(diam_cima[v], diam_baixo[u].second);
		else
			diam_cima[v] = max(diam_cima[v], diam_baixo[u].first);

		calc_cima(v, u);
	}
}

trio LCA(int x, int y) {
	if(x == y) return {0, 0, x};
	if(depth[x] < depth[y])
		swap(x, y);

	for(int l = logn -1; l >= 0; l--)
		if(depth[x] - (1 << l) > depth[y])
			x = pai[x][l];
	
	if(pai[x][0] == y) return {x, 0, y};
	x = pai[x][0];

	for(int l = logn-1; l >= 0; l--)
		if(pai[x][l] != pai[y][l])
			x = pai[x][l], y = pai[y][l];

	return {x, y, pai[x][0]};
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		g[u].pb({v, w});
		g[v].pb({u, w});
	}
	dfs(1, 0);
	calc_cima(1, 0);

	for(int i = 1; i <= n; i++) {
		// printf("%d %d %d\n", maior_baixo[i].a, maior_baixo[i].b, maior_baixo[i].c);
		// printf("%d %d\n", diam_baixo[i].first, diam_baixo[i].second);
		printf("%d %d\n", diam_cima[i], maior_cima[i]);
	}

	int q; scanf("%d", &q);
	while(q--) {
		int a, b; scanf("%d %d", &a, &b);
		if(pai[a][0] == b || pai[b][0] == a) { puts("-1"); continue; }

		auto [esq, dir, lca] = LCA(a, b);

		int ans = 0x3f3f3f3f;
		int f1 = a, f2 = b;
		while(pai[f1][0] != esq) {
			int junta;
			if(maior_baixo[pai[f1][1]].a == maior_baixo[pai[f1][0]].a + edge_pai[pai[f1][0]]) {
				junta = max(maior_cima[pai[f1][1]], maior_baixo[pai[f1][1]].c) + maior_baixo[pai[f1][1]].c;
			} else {
				if(maior_baixo[pai[f1][1]].b == maior_baixo[pai[f1][0]].a + edge_pai[pai[f1][0]])
					junta = max(maior_cima[pai[f1][1]], maior_baixo[pai[f1][1]].c) + maior_baixo[pai[f1][1]].a;
				else
					junta = max(maior_cima[pai[f1][1]], maior_baixo[pai[f1][1]].b) + maior_baixo[pai[f1][1]].a;
			}
			int val_cima = max(diam_cima[pai[f1][1]], junta);
			ans = min(ans, abs(diam_baixo[f1].first - val_cima));
			f1 = pai[f1][0];
		}
		while(pai[f2][0] != dir) {
			int junta;
			if(maior_baixo[pai[f2][1]].a == maior_baixo[pai[f2][0]].a + edge_pai[pai[f2][0]]) {
				junta = max(maior_cima[pai[f2][1]], maior_baixo[pai[f2][1]].c) + maior_baixo[pai[f2][1]].c;
			} else {
				if(maior_baixo[pai[f2][1]].b == maior_baixo[pai[f2][0]].a + edge_pai[pai[f2][0]])
					junta = max(maior_cima[pai[f2][1]], maior_baixo[pai[f2][1]].c) + maior_baixo[pai[f2][1]].a;
				else
					junta = max(maior_cima[pai[f2][1]], maior_baixo[pai[f2][1]].b) + maior_baixo[pai[f2][1]].a;
			}
			int val_cima = max(diam_cima[pai[f2][1]], junta);
			ans = min(ans, abs(diam_baixo[f2].first - val_cima));
			f2 = pai[f2][0];
		}
		printf("%d\n", ans);
	}
}