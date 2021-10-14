/*
	The following case breaks my first submitted solution, in that case
	I forgot to consider the second step of the stair of dp's when considering the 'center'

	15 3
	1 12 7
	1 2
	2 3
	2 4
	1 5
	1 6
	6 7
	7 8
	7 9
	7 10
	1 11
	11 12
	12 13
	12 14
	12 15
*/

#include <bits/stdc++.h>
using namespace std;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

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

int dp_esp[2], val_esp[2];

void calc_esp(int u) {
	mark2[u] = 1;
	vector<int> aq;
	for(int v : g[u])
		if(!mark[v] && !mark2[v]) calc(v), aq.push_back(dp[v]);
	sort(all(aq), greater<int>());
	for(int i = 0; i < sz(aq); i++) {
		if(aq[i] + i + 1 >= dp_esp[0])
			val_esp[1] = 0, val_esp[0] = i+1, dp_esp[1] = 0, dp_esp[0] = aq[i] + i + 1;
		else if(aq[i] + i + 1 >= dp_esp[1])
			val_esp[1] = i+1, dp_esp[1] = aq[i] + i + 1;
	}
	val_esp[1] = max(0, val_esp[1] - val_esp[0]);
	assert(dp_esp[1]==0 || dp_esp[0] > dp_esp[1]);
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
	calc_esp(centro);
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
	if(dp_esp[0] + chegou > LIM) return;
	int aq = acertou+1;
	saber = 1;
	mark2[centro] = itr;
	++acertou;

	vector<int> vis;
	for(int i = 0; i < 3; i++)
		if(mark[sai[i]] && mark2[sai[i]] != itr)
			vis.pb(sai[i]);

	// db(vis, chegou, val_esp[0], val_esp[1]);

	for(int rep = 0; rep < 2; rep++, reverse(vis.begin(), vis.end()), opa.clear()) {
		if(vis.size() == 1)
			dfs(vis[0], chegou + 1 + (dp_esp[0] + chegou == LIM ? val_esp[0] : 0));
		else if(vis.size() == 2) {
			if(dp_esp[1] + 1 + chegou > LIM) { assert(!dp_esp[1] && !dp_esp[0]); continue; }

			dfs(vis[0], chegou + 1 + (dp_esp[0] + chegou == LIM ? val_esp[0] : 0));
			
			if(dp_esp[1] + 1 + chegou == LIM)
				dfs(vis[1], chegou + 2 + val_esp[0] + val_esp[1]);
			else if(dp_esp[0] + chegou + 1 >= LIM)
				dfs(vis[1], chegou + 2 + val_esp[0]);
			else dfs(vis[1], chegou + 2);
		}
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
		if(mark[i] && i != centro) calc(i);

	int l = 0, r = n, ans = 0;
	while(l <= r) {
		LIM = (l+r) >> 1;
		if(get()) ans = LIM, r = LIM-1;
		else l = LIM+1;
	}
	printf("%d\n", ans);
}
