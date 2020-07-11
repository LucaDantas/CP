#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
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
constexpr int MAXN = 2e5 + 10;
constexpr int mod = 1000000007;

// We could either find the diameter and then cut everything that is further away
// than the answer of the query or we could find the 'weight center' and then just
// binary search which side to go with the second query

vi g[MAXN];

int weight[MAXN], maior[MAXN], used;

bool mark[MAXN];

void dfs(int u, int p = -1) {
	weight[u] = 1;
	for(auto v : g[u]) {
		if(v == p || mark[v]) continue;
		dfs(v, u);
		weight[u] += weight[v];
		maior[u] = max(maior[u], weight[v]);
	}
}

int ans = 0, best = inf;

void calc(int u, int p = -1) {
	int memo = used;

	if(used >= maior[u]) {
		int dif = used - weight[u];
		if(dif < best)
			best = dif, ans = u;
	}
	else {
		int dif = maior[u] - (used + weight[u] - maior[u]);
		if(dif < best)
			best = dif, ans = u;
	}

	for(auto v : g[u]) {
		if(v == p || mark[v]) continue;
		used = memo + weight[u] - weight[v];
		calc(v, u);
	}
}

int main() {
	int n;
	scanf("%d", &n);

	rep(i,1,n) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}

	int start = 1;
	while(start) {
		clr(weight, 0); clr(maior, 0); 
		used = 0; ans = 0; best = inf;

		dfs(start); calc(start);

		mark[ans] = 1;

		printf("? 2 %d\n", ans);
		fflush(stdout);
		scanf("%d", &start);

		assert(start != -1);
	}
	printf("! %d\n", ans); fflush(stdout);
}
