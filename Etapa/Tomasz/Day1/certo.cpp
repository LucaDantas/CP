#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

vector<int> g[maxn];

int inf[3], pai[maxn], filho[maxn], dp[maxn], val[maxn], mark2[maxn], centro;

bool mark[maxn];

void pre(int u) {
	for(int v : g[u])
		if(v != pai[u]) pai[v] = u, pre(v);
}

void calc(int u) {
	mark2[u] = 1;
	vector<int> aq;
	for(int v : g[u])
		if(!mark[v] && !mark2[v]) calc(v), aq.push_back(dp[v]);
	sort(all(aq), greater<int>());
	for(int i = 0; i < sz(aq); i++)
		if(aq[i] + i + 1 >= dp[u])
			val[u] = i+1, dp[u] = aq[i] + i + 1;
}

int LIM, itr, acertou, tem, k, sai[3], chegou;

void up(int u) {
	tem = 1;
	while(u != inf[0])
		mark[u] = 1, filho[pai[u]] = u, u = pai[u], ++tem;
	mark[inf[0]] = 1;
}

void up2(int u) {
	int sv = u;
	while(!mark[u])
		mark[u] = 1, u = pai[u], ++tem;
	centro = u;
	u = sv;
	sai[0] = pai[centro], sai[1] = filho[centro];
	while(u != centro) {
		if(pai[u] != centro) filho[pai[u]] = u;
		else sai[2] = u;
		u = pai[u];
	}
}

vector<int> opa;
bool saber;

void dfs(int u, int t) {
	if(dp[u] + t > LIM) return;
	if(u == centro) return (void)(chegou = min(chegou, t));
	mark2[u] = itr;
	++acertou;
	for(int rep = 0; rep < 2; rep++, swap(pai[u], filho[u])) {
		if(mark[pai[u]] && mark2[pai[u]] != itr)
			dfs(pai[u], t + 1 + (dp[u] + t == LIM ? val[u] : 0));
	}
	if(saber) opa.pb(u);
}

void checar3() {
	if(dp[centro] + chegou > LIM) return;
	int u = centro, aq = acertou+1;
	saber = 1;
	mark2[u] = itr;
	++acertou;
	for(int rep = 0; rep < 2; rep++, reverse(sai, sai+3), opa.clear()) {
		int foi = 1;
		for(int i = 0; i < 3; i++)
			if(mark[sai[i]] && mark2[sai[i]] != itr)
				dfs(sai[i], chegou + foi + (dp[u] + chegou + foi-1 >= LIM ? val[u] : 0)), ++foi;
		aq = max(aq, acertou);
		acertou -= sz(opa);
		for(int x : opa) mark2[x] = 0;
	}
	saber = 0;
	acertou = aq;
}

bool get() {
	chegou = 0x3f3f3f3f;
	itr += 2;
	dfs(inf[0], 0);
	if(mark2[inf[1]] != itr) dfs(inf[1], 0);
	if(k == 3 && mark2[inf[2]] != itr) dfs(inf[2], 0);
	if(k == 3) checar3();
	bool ok = tem == acertou;
	acertou = 0;
	return ok;
}

int main() {
	int n; scanf("%d %d", &n, &k); if(k > 3) return 0;
	for(int i = 0; i < k; i++)
		scanf("%d", &inf[i]);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);

	if(k == 1) return (calc(inf[0]), printf("%d\n", dp[inf[0]])), 0;
	
	pre(inf[0]);

	if(k >= 2) up(inf[1]);
	if(k == 3) up2(inf[2]);

	for(int i = 1; i <= n; i++)
		if(mark[i]) calc(i);
	
	int l = 0, r = n, ans = 0;
	while(l <= r) {
		LIM = (l+r) >> 1;
		if(get()) ans = LIM, r = LIM-1;
		else l = LIM+1;
	}
	printf("%d\n", ans);
}
