#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

vector<int> g[maxn];

int deep[maxn], sub[maxn], t, n;
void pre(int u, int p) {
	sub[u] = (g[u].size() == 1);
	for(int v : g[u]) if(v != p) {
		pre(v, u);
		deep[u] = max(deep[u], deep[v]+1);
		sub[u] += sub[v];
	}
}

long long ans;
int start;

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

int main() {
	int l, r; scanf("%d %d %d", &n, &l, &r); // l == 2, r == n
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	start = g[1].size() == 1 ? g[1][0] : 1;
	pre(start, 0);
	ans = 1ll * sub[start] * (sub[start]-1) / 2;
	dfs(start, 0, 0);
	printf("%lld\n", ans);
}
