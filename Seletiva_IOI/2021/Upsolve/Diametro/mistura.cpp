#include <bits/stdc++.h>
using namespace std;

int n, L, R;

// solucao L = 2, R = n
namespace l2rn {

	constexpr int maxn = 2e5+10;

	vector<int> g[maxn];

	int deep[maxn], sub[maxn], t;
	void pre(int u, int p) {
		sub[u] = (g[u].size() == 1);
		for(int v : g[u]) if(v != p) {
			pre(v, u);
			deep[u] = max(deep[u], deep[v]+1);
			sub[u] += sub[v];
		}
	}

	long long ans = 0;
	int start = 0;

	void dfs(int u, int p, int longe_pai) {
		if(p)
			swap(g[u].front(), *find(g[u].begin(), g[u].end(), p));
		else
			reverse(g[u].begin(), g[u].end()), g[u].push_back(0), reverse(g[u].begin(), g[u].end());

		int sz = (int)(g[u].size());

		vector<pair<int,int>> pref(sz+1), suf(sz+1);
		for(int i = 1; i < sz; i++)
			pref[i] = max(pref[i-1], {1+deep[g[u][i]], g[u][i]});
		for(int i = sz-1; i >= 1; i--)
			suf[i] = max(suf[i+1], {1+deep[g[u][i]], g[u][i]});

		int cnt_folhas = 0;
		for(int i = 1; i < sz; i++)
		{	
			if(g[g[u][i]].size() == 1)
			{
				int folha = g[u][i];
				
				if(longe_pai > n/2)
				{
					ans -= sub[u]-1; // quantidade de folhas dentro da minha subarvore fora a folha em questao 
					++cnt_folhas;
				}
				else if(max(pref[i-1], suf[i+1]).first > n/2)
				{	
					int v = max(pref[i-1], suf[i+1]).second;
					ans -= (sub[start]-sub[v]-1); // todo mundo menos sub[v] e folha
					++cnt_folhas;

				}
			} else {
				dfs(g[u][i], u, 1+max({longe_pai, pref[i-1].first, suf[i+1].first}));
			}
		}
		ans += 1ll * cnt_folhas * (cnt_folhas-1) / 2;
	}

	void solve() {
		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
		start = g[1].size() == 1 ? g[1][0] : 1;
		pre(start, 0);
		ans = 1ll * sub[start] * (sub[start]-1) / 2;
		if(L == 1 && R == n) return (void)(printf("%lld\n", ans));
		dfs(start, 0, 0);
		printf("%lld\n", ans);
	}

}

// sol O(n^2)
namespace quadrado {

	constexpr int maxn = 5010;

	vector<int> g[maxn];

	int deep[maxn], prof[maxn];

	void pre(int u, int p = 0) {
		for(int v : g[u]) if(v != p) {
			prof[v] = prof[u]+1;
			pre(v, u);
			deep[u] = max(deep[u], deep[v]+1);
		}
	}

	void clear() { memset(deep, 0, sizeof deep); memset(prof, 0, sizeof prof); }

	int ans = 0;

	void dfs(int u, int p, int tam_min) {
		if(g[u].size() == 1) {
			ans += prof[u] * R >= tam_min;
			return;
		}

		swap(*g[u].begin(), *find(g[u].begin(), g[u].end(), p)); // o pai tá sempre no inicio, então posso desconsiderar
		assert(g[u].front() == p);

		int sz = (int)(g[u].size());
		vector<int> pref(sz+1), suf(sz+1);
		
		for(int i = 1; i < sz; i++) {
			pref[i] = max(pref[i-1], deep[g[u][i]]+1);
			suf[i] = max(suf[i+1], deep[g[u][i]]+1);
		}

		for(int i = 1; i < sz; i++) {
			if(prof[u] * R < max(pref[i-1], suf[i+1]) * L) continue; // não da pra chegar nesse cara porque a aresta não vai pro inicio da dfs
			dfs(g[u][i], u, max(tam_min, prof[u] * R + max(pref[i-1], suf[i+1]) * L));
		}

		// o que eu preciso garantir:
		// dist(u, folha_final) * R >= max(pref[i-1], suf[i+1]) * L ==> prof[folha_final] * R >= prof[u] * R + max(pref[i-1], suf[i+1]) * L
		// (dist(u, folha_inicial) == prof[u]) * R >= max(pref[i-1], suf[i+1]) * L
		
		// quando eu chego na folha pra verificar a resposta:
		// prof[folha] * R >= tam_min ==> caminho válido
	}

	int diam_ini = 0;

	void solve() {
		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);

		pre(1, 0);
		int longe = max_element(prof+1, prof+1+n) - prof;
		clear();
		pre(longe, 0);
		diam_ini = *max_element(prof+1, prof+1+n);
		clear();
		
		for(int i = 1; i <= n; i++) if(g[i].size() == 1) {
			clear();
			pre(i, 0);
			// também preciso garantir que, além de todos os caminhos que se intersectam com o meu, o caminho é >= a todos os caminhos que nao intersectam
			dfs(g[i][0], i, diam_ini*L);
		}

		printf("%d\n", ans>>1);
	}

}

// sol L = N, R = N+1
namespace count_diam {

	using pii = pair<long long, long long>;

#define pb push_back
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

	constexpr int maxn = 2e5 + 10;

	vector<int> g[maxn];

	pii ans;

	pii dfs(int u, int p) {
		// a dfs retorna qual o filho mais profundo e quantos têm
		vector<pii> hm;
		for(int v : g[u])
			if(v != p) hm.pb(dfs(v, u));
		sort(all(hm), greater<pii>());
		if(!hm.size()) hm.pb({0, 1});

		if(sz(hm) == 1) {
			if(hm.front().ff+1 > ans.ff) ans = {hm.front().ff+1, hm.front().ss};
			else if(hm.front().ff+1 == ans.ff) ans.ss += hm.front().ss;
			return {hm.front().ff+1, hm.front().ss};
		}

		// senao é >= 2
		vector<pii> bom;
		bom.pb(hm.front());
		for(int i = 1; i < sz(hm); i++)
			if(hm[i].first == hm[1].first) bom.pb(hm[i]);
		
		long long cnt = 0, aq = 0;
		for(int i = 0; i < sz(bom); i++)
			aq += cnt * bom[i].ss, cnt += (bom[i].ff == bom[0].ff) * bom[i].ss;

		if(bom[0].ff + bom[1].ff + 1 > ans.ff) ans = {bom[0].ff + bom[1].ff + 1, aq};
		else if(bom[0].ff + bom[1].ff + 1 == ans.ff) ans.ss += aq;

		pii ret = {hm.front().ff+1, hm.front().ss};
		for(int i = 1; i < sz(bom); i++)
			if(bom[i].ff == bom[0].ff) ret.ss += bom[i].ss;

		return ret;
	}

	void solve() {
		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
		dfs(1, 0);
		printf("%lld\n", ans.ss);
	}

}

int main() {
	scanf("%d %d %d", &n, &L, &R); // l == 2, r == n
	if(n <= 5000) quadrado::solve();
	else if(L == n && R == n+1) count_diam::solve();
	else l2rn::solve();
}
