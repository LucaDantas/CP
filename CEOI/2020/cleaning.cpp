#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) (int)(a.size())
#define ff first
#define ss second

constexpr int maxn = 1e5+10;

vector<int> g[maxn];

int root, leafs, geral;
int par[maxn], ans[maxn], leaf[maxn]; // define a paridade do número de folhas de cada nó

int depth[maxn], on[maxn]; // qual o nível do meu cara e quantos ligados tem acima dele (contando com ele)

map<int, int> versao[maxn]; // pra cada nó a gente vai ter no map em quais versões ele tem um filho desparelhado
// e onde que começou

void pre(int u, int p) {
	if(sz(g[u]) == 1) {
		leafs++;
		par[u] = 1;
		leaf[u] = 1;
	} else {
		for(auto v : g[u]) {
			if(v != p) {
				pre(v, u);
				par[u] += par[v];
				par[u] %= 2;
			}
		}
	}
}

void calc(int u, int p) {
	on[u] += !par[u];
	for(auto v : g[u]) {
		if(v != p) {
			on[v] += on[u];
			depth[v] = depth[u]+1;
			calc(v, u);
		}
	}
}

void dfs(int u, int p) {
	int maior = u;
	for(auto v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		if(sz(versao[v]) > sz(versao[maior]))
			maior = v;
	}
	if(maior != u)
		swap(versao[u], versao[maior]);
	for(auto v : g[u]) {
		if(v == p) continue;
		// vou passar dos menores pra mim e ver os que batem
		for(auto it : versao[v]) {
			int ver = it.ff, ini = it.ss;
			if(versao[u].count(ver)) {
				// deu um 'match' nesse node da mesma versão e a esse nó é o lca
				// printf("versão %d -> lca %d\n", ver, u);
				
				// com o primeiro cara
				int tam = depth[ini] - depth[u]; // quantos caras tem no caminho excluindo o lca pq ele n troca
				int ligados = on[ini] - on[u];
				ans[ver] -= ligados;
				ans[ver] += tam - ligados;

				// com o segundo cara
				ini = versao[u][ver];
				tam = depth[ini] - depth[u]; // quantos caras tem no caminho excluindo o lca pq ele n troca
				ligados = on[ini] - on[u];
				ans[ver] -= ligados;
				ans[ver] += tam - ligados;

				versao[u].erase(ver);
			} else {
				versao[u][ver] = ini;
			}
		}
	}
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	if(sz(g[1]) == 1) root = g[1][0];
	else root = 1;
	pre(root, 0); // the root is not a leaf
	geral = n - 2; // começa com -1 porque a raiz sempre vai ser par, mas não conta mais porque não tem pai pra dobrar a aresta
	for(int i = 1; i <= n; i++)
		geral += !par[i];
	for(int test = 0; test < q; test++) {
		int d; scanf("%d", &d);
		map<int, int> mp;
		int here = 0; // we need to know how many resulting leafs there will be in this variation
		for(int i = 0; i < d; i++) {
			int add; scanf("%d", &add);
			if(leaf[add]) here += mp.count(add);
			else here++;
			mp[add]++;
		}
		if((here + leafs)&1) ans[test] = -1;
		else {
			ans[test] = geral + d;
			for(auto node : mp) {
				int id = node.ff, qtd = node.ss;
				qtd -= leaf[id];
				if(qtd&1)
					versao[id][test] = id;
			}
		}
	}
	depth[root] = 1;
	calc(root, 0);
	dfs(root, 0);
	if(leafs&1) {
		// assert(sz(versao[root]));
		for(auto it : versao[root]) {
			int ver = it.ff, ini = it.ss;
			ans[ver] -= on[ini];
			ans[ver] += depth[ini] - on[ini];
		}
	}
	else assert(!sz(versao[root]));

	// printf("%d\n", geral);
	for(int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}