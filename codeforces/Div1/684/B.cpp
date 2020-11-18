#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

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
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

int grau[maxn];
bool mark[maxn];
vector<int> g[maxn];
set<int> grp[maxn];

void erase(int u, int tam) {
	mark[u] = 1;
	for(int v : g[u]) {
		if(mark[v]) continue;
		assert(grau[v] >= tam);
		if(grau[v] == tam)
			erase(v, tam);
		if(grau[v] == tam+1)
			grp[tam+1].erase(v), erase(v, tam);
		else {
			grp[grau[v]].erase(v);
			grau[v]--;
			grp[grau[v]].insert(v);
		}
	}
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m, k; scanf("%d %d %d", &n, &m, &k);
		for(int i = 0; i <= n; i++) {
			grau[i] = 0;
			mark[i] = 0;
			g[i].clear();
			grp[i].clear();
		}
		for(int i = 0; i < m; i++) {
			int a, b; scanf("%d %d", &a, &b);
			grau[a]++, grau[b]++;
			g[a].pb(b);
			g[b].pb(a);
		}
		if(k * (k-1) / 2 > m) { puts("-1"); continue; }
		for(int i = 1; i <= n; i++)
			grp[grau[i]].insert(i);
		for(int i = 0; i < k; i++) {
			for(int u : grp[i]) {
				if(!mark[u])
					erase(u, i);
			}
			grp[i].clear();
		}
		bool ok = 0;
		for(int i = 1; i <= n; i++)
			if(!mark[i]) ok = 1;
		if(ok) {
			int ans = 0;
			for(int i = 1; i <= n; i++)
				if(!mark[i]) ans++;
			printf("1 %d\n", ans);
			for(int i = 1; i <= n; i++)
				if(!mark[i]) printf("%d ", i);
			printf("\n");
			continue;
		}
		for(int i = 0; i <= n; i++)
			grp[i].clear(), grau[i] = sz(g[i]), mark[i] = 0;
		for(int i = 1; i <= n; i++)
			grp[grau[i]].insert(i), sort(all(g[i]));
		for(int i = 1; i < k-1; i++) {
			for(int u : grp[i]) {
				if(!mark[u])
					erase(u, i);
			}
			grp[i].clear();
		}
		while(grp[k-1].size()) {
			int u = *grp[k-1].begin();
			vector<int> ver = {u};
			for(int v : g[u])
				if(!mark[v])
					ver.pb(v);
			if(sz(ver) != k) { erase(u, k-2); grp[k-1].erase(u); continue; }
			sort(all(ver), [](int a, int b){return grau[a]<grau[b];});
			bool chk = 1;
			for(int i = 0; i < k; i++) {
				for(int j = i+1; j < k; j++)
					if(!binary_search(all(g[ver[i]]), ver[j])) { chk = 0; break; }
				if(!chk) break;
			}
			if(chk) {
				ok = 1;
				printf("2\n");
				for(int x : ver)
					printf("%d ", x);
				printf("\n");
				break;
			}
			erase(u, k-2);
			grp[k-1].erase(u);
		}
		if(!ok) puts("-1");
	}
}
