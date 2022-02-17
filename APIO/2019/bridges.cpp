#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, maxq = maxn, B = 300;

struct DSU {
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	void init() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b]) swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
	}
	void reset(int a) { pai[a] = a, peso[a] = 1; }
	int sz(int a) { return peso[find(a)]; }
} dsu, dsu2;

struct Edge { int a, b, d, id; bool operator<(const Edge& o) const { return d > o.d; } } e[maxn], certo[maxn];

struct Query { int tipo, x, y, t; } qr[maxq];

bool special[maxn], foi[maxn];

int ans[maxq], back[maxn];

int main() {
	memset(ans, -1, sizeof ans);
	
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++)
		scanf("%d %d %d", &e[i].a, &e[i].b, &e[i].d), e[i].id = i, certo[i] = e[i];

	int q; scanf("%d", &q);
	for(int i = 0; i < q; i++) {
		scanf("%d %d %d", &qr[i].tipo, &qr[i].x, &qr[i].y);
		if(qr[i].tipo == 1) --qr[i].x;
		qr[i].t = i;
	}

	// ordenar as arestas pelo peso decrescente
	sort(e, e+m, [](const Edge& a, const Edge& b) { return a.d > b.d; });

	for(int i = 0; i < m; i++)
		back[e[i].id] = i;

	for(int k = 0; k < q; k += B) {
		vector<Query> ask;

		for(int i = k; i < min(q, k+B); i++) {
			if(qr[i].tipo == 1) // update
				special[qr[i].x] = 1;
			else ask.push_back(qr[i]);
		}

		sort(ask.begin(), ask.end(), [](const Query& a, const Query& b) { return a.y > b.y; }); // y==peso, ordeno pelo peso decrescente

		for(int i = 0, ptr = 0; i < (int)ask.size(); i++) {

			for(; ptr < m && e[ptr].d >= ask[i].y; ptr++) {
				if(!special[e[ptr].id])
					dsu.join(e[ptr].a, e[ptr].b);
			}

			vector<int> ver = {dsu.find(ask[i].x)}; // todos os caras que eu vou olhar no dsu2 pra ver se está junto ao vertice da pergunta

			for(int j = ask[i].t-1; j >= k; j--) { // vejo todos os updates anteriores pra ver se adiciono ou não
				if(qr[j].tipo == 1 && qr[j].y >= ask[i].y && !foi[qr[j].x]) {
					int id = qr[j].x;
					dsu2.join(dsu.find(certo[id].a), dsu.find(certo[id].b));
					ver.push_back(dsu.find(certo[id].a)), ver.push_back(dsu.find(certo[id].b));
				}
				if(qr[j].tipo == 1)
					foi[qr[j].x] = 1;
			}

			for(int j = ask[i].t; j < min(q, k+B); j++) {
				if(qr[j].tipo == 1 && certo[qr[j].x].d >= ask[i].y && !foi[qr[j].x]) {
					int id = qr[j].x;
					dsu2.join(dsu.find(certo[id].a), dsu.find(certo[id].b));
					ver.push_back(dsu.find(certo[id].a)), ver.push_back(dsu.find(certo[id].b));
				}
			}

			for(int j = ask[i].t-1; j >= k; j--)
				foi[qr[j].x] = 0;

			int val = 0;

			for(int x : ver) {
				if(!foi[x] && dsu2.find(dsu.find(ask[i].x)) == dsu2.find(x))
					foi[x] = 1, val += dsu.sz(x);
			}

			for(int x : ver) dsu2.reset(x), foi[x] = 0;

			ans[ask[i].t] = val;
		}


		// reiniciar as coisas pro próximo bloco
		dsu.init();
		ask.clear();
		vector<Edge> sla, bom;
		vector<int> add_dps;
		
		for(int i = 0; i < m; i++)
			if(!special[e[i].id]) bom.push_back(certo[e[i].id]);
			else add_dps.push_back(e[i].id);

		for(int i = k; i < min(q, k+B); i++) {
			if(qr[i].tipo == 1) {
				special[qr[i].x] = 0;
				certo[qr[i].x].d = qr[i].y;
			}
		}

		for(int x : add_dps)
			sla.push_back(certo[x]);
		
		sort(sla.begin(), sla.end());
		merge(bom.begin(), bom.end(), sla.begin(), sla.end(), e);
	}

	for(int i = 0; i < q; i++)
		if(ans[i] != -1) printf("%d\n", ans[i]);
}
