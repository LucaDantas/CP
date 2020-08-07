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
void debug() { cerr << '\n'; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
// #define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int centroid, sz[maxn], n, in[maxn], have[maxn];
vi g[maxn];

void dfs(int u, int p=0) {
	sz[u] = 1;
	for(auto v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

void find(int u) {
	int maior = 0, go = 0, tot = 0;
	for(auto v : g[u]) {
		if(sz[v] > maior) maior = sz[v], go = v;
		tot += sz[v];
	}
	if(maior <= n/2) return (void)(centroid = u);
	sz[u] = tot - maior;
	find(go);
}

int aux;

void time(int u, int p = 0) {
	in[aux++] = u;
	for(auto v : g[u]) {
		if(v != p) {
			time(v, u);
		}
	}
}

ll ans;

int main() {
	scanf("%d", &n);
	rep(i,1,n) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}
	
	dfs(1), find(1); // calculate the sizes and find centroid

	time(centroid);
	dfs(centroid);
	
	rep(i,1,n+1) if(i != centroid) ans += sz[i];
	printf("%lld\n", 2ll*ans);
	
	rep(i,1,n+1) have[i] = i;
	rep(i,0,n/2) swap(have[in[i]], have[in[i+n/2]]);
	if(n&1) swap(have[centroid], have[in[n-1]]);
	
	rep(i,1,n+1) printf("%d%c", have[i], " \n"[i==n]);
}
