/*
  A ideia pra transformar em uma grande SCC é primeiro montar
  um grafo em que toda raiz consegue chegar em toda folha, e pra
  fazer isso basta a gente ligar cada raiz inicial a alguma folha
  que ele não consegue chegar, pq não vai criar nenhuma componente
  nova com isso e essa raiz vai deixar de ser raiz e o mesmo pra
  antiga folha. Quando eu não puder fazer mais isso o grafo terá
  a característica desejada. Também é interessante perceber que
  sempre restará pelo menos uma raiz no nosso novo grafo. Com o
  grafo montado encontramos uma raiz que alcance o vertice com
  menor valor e ligamos alguma folha a essa raiz de modo que forme
  uma SCC com a raiz escolhida, chamaremos de rMin. Agora queremos
  provar que para o conjunto R/{rMin} (todas as outras raizes)
  conseguem chegar em rMin e também que o inverso é válido.
  Para percebre o primeiro basta ver que como todas as raízes do
  grafo conseguem chegar em todas as folhas, consequentemente
  conseguem chegar na folha ligada a rMin e consequentemente em rMin.
  Para ver que rMin também chega em todas as outras raízes vamos
  manter dois conjuntos R e L, que são respectivamente as raízes
  e folhas que ainda não foram pareadas.
  |R| > 0 ^ |L| > 0
  Podemos juntar um elemento de L com um elemento de R e como rMin
  chega em todos os elementos de L ele consequentemente chega no
  elemento selecionado de R, além disso como todos os elementos de R
  chegam em rMin o elemento de L escolhido também chega em rMin.
  Podemos repetir esse processo até chegar em um dos seguintes casos:
  |R| > 0 ^ |L| == 0.
  Nesse caso podemos juntar o mnNode com todos os elementos de R e
  como mnNode e rMin estão na mesma SCC, rMin consegue também chegar
  em todos os elementos de R.
  |R| == 0 ^ |L| > 0.
  Nesse caso rMin já consegue chegar em todos os elementos de R,
  porém nem todos os elementos de L conseguem chegar em rMin,
  portanto podemos simplesmente juntar cada elemento de L com mnNode
  e desse modo teremos que cada elemento de L também alcanca rMin

  Portanto como rMin alcança todas os elementos de R e a união dos
  elementos alcançados por R é o conjunto dos vértices do grafo, rMin
  alcança todos os vértices do grafo. Também como todos os elementos
  de L alcançam rMin e a união dos elementos alcançados por L U {lMin}
  é o conjunto de vértices do grafo todos os elementos também alcançam
  rMin e desse modo o grafo é fortemente conexo
*/

#include<bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define pb push_back

constexpr int maxn = 4e3+10;

int a[maxn], in[maxn], out[maxn], comp[maxn], menor[maxn], cnt, mn;

bool mark[maxn];

vector<int> g[maxn], rev_g[maxn], grp[maxn], g_comp[maxn], ord; // ordenados por time_out

void dfs1(int u) {
	mark[u] = 1;
	for(int v : g[u])
		if(!mark[v]) dfs1(v);
	ord.pb(u);
}

void dfs2(int u) {
	comp[u] = cnt;
	grp[cnt].pb(u);
	for(int v : rev_g[u])
		if(!comp[v]) dfs2(v);
}

void dfs3(int u) {
	mark[u] = 1;
	for(int v : g_comp[u])
		if(!mark[v]) dfs3(v);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	a[0] = 0x3f3f3f3f;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if(a[i] < a[mn]) mn = i;
	}
	for(int i = 0, x, y; i < m; i++)
		scanf("%d %d", &x, &y), g[x].pb(y), rev_g[y].pb(x);
	
	for(int i = 1; i <= n; i++)
		if(!mark[i]) dfs1(i);

	for(int i = 1; i <= n; i++) {
		if(!comp[ord.back()]) ++cnt, dfs2(ord.back());
		ord.pop_back();
	}
	if(cnt == 1) return puts("0 0"), 0;

	for(int i = 1; i <= cnt; i++) {
		menor[i] = 0;
		for(int u : grp[i]) {
			if(a[u] < a[menor[i]]) menor[i] = u;
			for(int v : g[u]) {
				if(comp[v] != i) {
					g_comp[i].pb(comp[v]);
					in[comp[v]] = out[i] = 1;
				}
			}
		}
	}
	for(int i = 1; i <= cnt; i++) {
		sort(all(g_comp[i]));
		g_comp[i].resize(unique(all(g_comp[i])) - g_comp[i].begin());
	}
	
	long long ans = 0;
	int opa[2]{}, qtd_ruim = 0;
	for(int i = 1; i <= cnt; i++) {
		if(!in[i]) ans += a[menor[i]], ++qtd_ruim, ++opa[0];
		if(!out[i]) ans += a[menor[i]], --qtd_ruim, ++opa[1];
	}

	ans += 1ll * abs(qtd_ruim) * a[mn];

	vector<int> roots, leafs;
	for(int i = 1; i <= cnt; i++) {
		if(!in[i]) roots.pb(i);
		if(!out[i]) leafs.pb(i);
	}

	vector<pair<int,int>> edges;
	vector<int> not_removed;
	for(int u : roots) {
		for(int i = 1; i <= cnt; i++)
			mark[i] = 0;
		dfs3(u);
		bool ok = 0;
		for(int& l : leafs) {
			if(!mark[l]) {
				ok = 1;
				edges.pb({menor[l], menor[u]});
				g_comp[l].pb(u);
				swap(l, leafs.back());
				leafs.pop_back();
				break;
			}
		}
		if(!ok) not_removed.pb(u);
	}
	for(int i = 1; i <= cnt; i++)
		mark[i] = 0;
	for(int& u : not_removed) {
		dfs3(u);
		if(mark[comp[mn]]) {
			for(int i = 1; i <= cnt; i++)
				mark[i] = 0;
			dfs3(u);
			vector<int> vis(cnt+1);
			for(int l : leafs)
				if(mark[l]) vis[l] = 1;
			for(int i = 1; i <= cnt; i++)
				mark[i] = 0;
			dfs3(comp[mn]);
			for(int& l : leafs) {
				if(mark[l] && vis[l]) {
					edges.pb({menor[l], menor[u]});
					g_comp[l].pb(u);
					swap(l, leafs.back());
					leafs.pop_back();
					break;
				}
			}
			swap(u, not_removed.back());
			not_removed.pop_back();
			break;
		}
	}

	while(not_removed.size() && leafs.size()) {
		edges.pb({menor[leafs.back()], menor[not_removed.back()]});
		not_removed.pop_back(); leafs.pop_back();
	}
	while(not_removed.size()) {
		edges.pb({mn, menor[not_removed.back()]});
		not_removed.pop_back();
	}
	while(leafs.size()) {
		edges.pb({menor[leafs.back()], mn});
		leafs.pop_back();
	}

	printf("%lld\n", ans);
	printf("%ld\n", edges.size());
	for(pair<int,int> e : edges)
		printf("%d %d\n", e.first, e.second);
}