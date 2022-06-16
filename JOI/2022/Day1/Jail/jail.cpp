#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 120010, logn = 20;

struct Top {
	vector<int> g[(2*logn+1) * maxn];
	int ingrau[(2*logn+1) * maxn];
	queue<int> q;
	void add_edge(int a, int b) {
		// if(a == b) return; // só colocar esse if não funciona mais já que agr eu tenho arestas virtuais do binary lifting
		// printf("adding %d -> %d\n", a, b);
		ingrau[b]++;
		g[a].push_back(b);
	}
	void clear(int n) {
		for(int i = 0; i <= n; i++)
			ingrau[i] = 0, g[i].clear();
		while(q.size())
			q.pop();
	}
	bool dag(int n) {
		for(int i = 1; i <= n; i++)
			if(!ingrau[i]) q.push(i);
		int vis = 0;
		while(q.size()) {
			int u = q.front(); q.pop();
			++vis;
			for(int v : g[u])
				if(!(--ingrau[v]))
					q.push(v);
		}
		return vis == n;
	}
} top;

int p[maxn][logn], depth[maxn], comeca[maxn][logn], termina[maxn][logn]; // salvo o indice do cara que comeca e termina em mim caso exista
int s[maxn], t[maxn];
int idx;
bool mark[maxn];
vector<int> g[maxn];

void dfs(int u) {
	for(int v : g[u]) if(v != p[u][0]) {
		p[v][0] = u;
		depth[v] = depth[u] + 1;
		dfs(v);
	}
}

void build(int n) {
	idx = n;
	for(int i = 1; i <= n; i++)
		comeca[i][0] = ++idx, termina[i][0] = ++idx;
	for(int l = 1; l < logn; l++) {
		for(int i = 1; i <= n; i++) {
			comeca[i][l] = ++idx, termina[i][l] = ++idx;
			p[i][l] = p[p[i][l-1]][l-1];

			top.add_edge(comeca[i][l-1], comeca[i][l]);
			if(p[i][l-1])
				top.add_edge(comeca[p[i][l-1]][l-1], comeca[i][l]);

			top.add_edge(termina[i][l], termina[i][l-1]);
			if(p[i][l-1])
				top.add_edge(termina[i][l], termina[p[i][l-1]][l-1]);
		}
	}
	// printf("idx %d\n", idx);
}

void go(int id) {
	int a = s[id], b = t[id];
	// printf("comeca %d %d\n", a, b);
	// a != b sempre
	
	top.add_edge(comeca[b][0], id);
	top.add_edge(id, termina[a][0]);

	bool foi = 0;
	if(depth[a] == depth[b]) {
		foi = 1;
		a = p[a][0];
		b = p[b][0];
		if(a == b) {
			top.add_edge(comeca[a][0], id), top.add_edge(id, termina[a][0]);
			return;
		}
	} else {
		if(depth[a] < depth[b])
			swap(a, b); // a é o mais fundo
		a = p[a][0]; // não quero que ele crie uma aresta dele pra ele mesmo, então eu crio subo um andar do mais baixo sem fazer o upd
	}

	for(int l = logn-1; l >= 0; l--)
		if(depth[a] - (1 << l) >= depth[b]) // comeca[a][l] e termina[a][l] não incluem p[a][l] no seu intervalo: [a, p[a][l][
			top.add_edge(comeca[a][l], id), top.add_edge(id, termina[a][l]), a = p[a][l];

	// printf("primeira %d %d\n", a, b);
	if(a == b) return;

	if(!foi) {
		b = p[b][0]; // não quero que o b crie uma aresta pra ele mesmo então eu também subo
		top.add_edge(comeca[a][0], id), top.add_edge(id, termina[a][0]), a = p[a][0];
		// mas com isso também preciso subir o a pra eles ficarem no mesmo nível dnv, só que no a eu add a aresta
		if(a == b) {
			top.add_edge(comeca[a][0], id), top.add_edge(id, termina[a][0]);
			return;
		}
	}

	for(int l = logn-1; l >= 0; l--) {
		if(p[a][l] != p[b][l]) {
			top.add_edge(comeca[a][l], id), top.add_edge(id, termina[a][l]), a = p[a][l];
			top.add_edge(comeca[b][l], id), top.add_edge(id, termina[b][l]), b = p[b][l];
		}
	}
	// comeca/termina[a][1] porque eu também quero colocar o pai (lca(a,b)) que não foi contado, então pego um intervalo de tamanho 2
	top.add_edge(comeca[a][1], id), top.add_edge(id, termina[a][1]);
	top.add_edge(comeca[b][0], id), top.add_edge(id, termina[b][0]);
}

void clear(int n) {
	for(int i = 0; i <= n; i++)
		g[i].clear(), depth[i] = 0, mark[i] = 0, s[i] = 0, t[i] = 0;
	for(int i = 0; i <= n; i++)
		for(int l = 0; l < logn; l++)
			p[i][l] = comeca[i][l] = termina[i][l] = 0;
	top.clear(idx);
	idx = 0;
}

int main() {
	int q; scanf("%d", &q);
	while(q--) {
		int n; scanf("%d", &n);
		clear(n);
		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
		
		dfs(1); build(n);

		int m; scanf("%d", &m);
		for(int i = 1; i <= m; i++)
			scanf("%d %d", s+i, t+i), top.add_edge(i, comeca[s[i]][0]), top.add_edge(termina[t[i]][0], i);
		
		for(int i = 1; i <= m; i++)
			go(i);
		
		puts(top.dag(idx) ? "Yes" : "No");
	}
}
