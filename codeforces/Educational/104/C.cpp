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
constexpr int maxn = 110;
constexpr int mod = 1000000007;

int resultado[maxn][maxn];

vector<int> g[maxn];

void dfs(int u) {
	while(g[u].size()) {
		int v = g[u].back(); g[u].pop_back();
		if(resultado[u][v] || resultado[v][u]) continue;
		// printf("%d %d\n", u, v);
		if(u > v) resultado[v][u] = -1;
		else resultado[u][v] = 1;
		dfs(v);
		return;
	}
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		// faz uma euler cycle
		// se for impar sempre é possível
		// se for par eu ligo n/2 pares com empates
		int n; scanf("%d", &n);
		// if(t == 1) continue;
		for(int i = 0; i < n; i++)
			g[i].clear();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				resultado[i][j] = 0;
		if(n%2) {
			// puts("0");
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					if(i != j) g[i].pb(j);
		} else {
			// printf("%d\n", (n-2)/2);
			vector<int> par(n);
			for(int i = 0; i < n; i += 2)
				par[i] = i+1, par[i+1] = i;
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					if(i != j && j != par[i]) g[i].pb(j);
		}
		dfs(0);
		for(int i = 0; i < n; i++)
			for(int j = i+1; j < n; j++)
				printf("%d ", resultado[i][j]);
		printf("\n");
	}
}
