#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 1e5+10;

struct DSU {
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		peso[a] += peso[b];
		pai[b] = a;
		return 1;
	}
} dsu[3];

struct Par {
	int cor, id;
	bool operator<(const Par& p) const {
		return cor < p.cor;
	}
};

int a[maxn][2], b[maxn][2], qtd[2], K;

bool mark[maxn];

std::vector<Par> cores[maxn];

int main() {
	int n, m[2]; scanf("%d %d %d", &n, &m[0], &m[1]);
	for(int k = 0; k < 2; k++) {
		qtd[k] = n;
		for(int i = 0; i < m[k]; i++) {
			scanf("%d %d", &a[i][k], &b[i][k]);
			qtd[k] -= dsu[k].join(a[i][k], b[i][k]);
		}
	}
	
	K = qtd[1] <= qtd[0];
	printf("%d\n", qtd[K]-1);

	for(int i = 1; i <= n; i++)
		cores[dsu[K].find(i)].push_back({dsu[!K].find(i), i});

	std::vector<Par> tem, lixo;
	for(int i = 1; i <= n; i++) {
		if(i != dsu[K].find(i)) continue;
		int ok = 0, cor_junta = 0;
		for(Par c : cores[i])
			if(!mark[c.cor]) ok = c.id+1, cor_junta = c.cor;
		if(ok && tem.size()) printf("%d %d\n", ok-1, tem.front().id), dsu[2].join(cor_junta, tem.front().cor);
		if(ok) for(Par c : cores[i])
			if(!mark[c.cor])
				tem.push_back(c), mark[c.cor] = 1;
		if(!ok) lixo.push_back(cores[i].front());
	}

	for(int i = 0, ptr = 0; i < (int)(lixo.size()); i++) {
		for(; !dsu[2].join(lixo[i].cor, tem[ptr].cor); ptr = (ptr+1) % ((int)tem.size()));
		mark[ptr] = 1;
		printf("%d %d\n", lixo[i].id, tem[ptr].id);
	}
}
