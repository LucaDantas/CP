// Se eu pegar um cara qualquer e definir que ele vai ser um resort e minha raiz
// eu posso fazer um guloso escolhendo sempre o cara mais fundo e atualizando a profundidade
// dos outros, o problema é que eu nao necessariamente preciso pegar essa raiz
// entao eu teria q brutar todas as possiveis, o que ficaria n^2, já pega n<=2000 though
// Faço um centroid e em cada nivel eu escolho sempre caras de pelo menos duas subarvores
// diferentes, se a melhor resposta n tiver ai so descer nos filhos e ta safe
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

using ll = long long;

#define int ll

#define pb push_back
#define sz(a) (int)((a).size())
#define all(a) (a).begin(), (a).end()

constexpr int maxn = 2e5+10;

vector<pair<int,int>> g[maxn];

ll ans[maxn];

struct Centroid {
	bool mark[maxn]; int sz[maxn];
	void pre(int u, int p = 0) {
		sz[u] = 1;
		for(auto [v, w] : g[u]) if(!mark[v] && v != p)
			pre(v, u), sz[u] += sz[v];
	}
	int get(int u) {
		for(auto [v, w] : g[u]) if((sz[v] << 1) > sz[u] && !mark[v])
			return (sz[u] -= sz[v], sz[v] += sz[u], get(v));
		return u;
	}
	
	ll dfs(int u, int p, ll& cost, vector<pair<ll,int>>& guloso, int idx) {
		vector<ll> td;
		ll maior = 0;
		
		for(auto [v, w] : g[u]) {
			if(v == p) cost += w;
			else if(!mark[v]) {
				ll gld = dfs(v, u, cost, guloso, idx) + w;
				td.pb(gld);
				if(gld > maior) maior = gld;
			}
		}
		
		bool ok = 0;
		for(ll a : td) {
			if(a == maior && !ok) ok = 1;
			else guloso.pb({a, idx});
		}

		return maior;
	}

	void decompose(int u, ll add) {
		pre(u); u = get(u);

		mark[u] = 1;
		
		vector<ll> custo;
		
		vector<pair<ll,int>> guloso;
		
		int idx = 0;
		ll custo_tot = 0;
		
		guloso.pb({0, -1});
		for(auto [v, w] : g[u]) {
			if(mark[v]) continue;
			ll cost = 0;
			ll gld = dfs(v, u, cost, guloso, idx) + w;
			guloso.pb({gld, idx});
			custo.pb(cost); custo_tot += cost;
			++idx;
		}

		sort(all(guloso));
		reverse(all(guloso));

		ans[1] = max(ans[1], custo_tot + add);

		if(sz(guloso) > 1) {
			idx = guloso.front().second;

			int primeiro = 0;
			for(int i = 0; i < sz(guloso); i++)
				if(guloso[i].second != idx) { primeiro = i; break; }
			assert(primeiro >= 1);
			
			ll bom = custo_tot, foi = guloso[primeiro].first, ok = 1;
			
			for(int i = 0; i < sz(guloso); i++) {
				bom += guloso[i].first;
				if(primeiro == i) foi = 0, ok = 0;
				ans[i + 1 + ok] = max(ans[i + 1 + ok], bom + foi + add);
			}
		}

		ll val = 0;

		vector<ll> suf;
		for(int i = sz(custo)-1; i >= 0; i--)
			suf.pb(val), val += custo[i];
		reverse(all(suf));

		val = 0;
		int i = 0;
		for(auto [v, w] : g[u]) {
			if(mark[v]) continue;
			decompose(v, val + suf[i] + w + add);
			val += custo[i];
			++i;
		}
	}
} centroid;

ll aq[maxn];

struct AAA
{
	int v, w, back;
};

vector<AAA> g_esp[maxn];

void pre_caso1(int u, int p) {
	for(auto [v, w, back] : g_esp[u]) {
		if(v == p) continue;
		pre_caso1(v, u);
		aq[u] += aq[v] + back;
	}
}

void caso1(int u, int p) {
	ans[1] = max(ans[1], aq[u]);
	for(auto [v, w, back] : g_esp[u]) {
		if(v == p) continue;
		aq[v] = w + aq[u] - back;
		caso1(v, u);
	}
}

int32_t main() {
	int n; scanf("%lld", &n);
	ll tot = 0;
	for(int i = 1; i < n; i++) {
		int a, b, c, d; scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		g[a].pb({b, c});
		g[b].pb({a, d});
		tot += c + d;

		g_esp[a].pb({b, c, d});
		g_esp[b].pb({a, d, c});
	}

	centroid.decompose(1, 0);

	for(int i = 1; i <= n; i++)
		ans[i] = max(ans[i], ans[i-1]);

	int q; scanf("%lld", &q);
	while(q--) {
		int e; scanf("%lld", &e);
		printf("%lld\n", tot - ans[e]);
	}
}
