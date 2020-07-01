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
constexpr int MAXN = 1e6 + 10;
constexpr int mod = 1000000007;

struct DSU
{
	int pai[MAXN], peso[MAXN];

	void init(int n) {
		rep(i,0,n) {
			pai[i] = i;
			peso[i] = 1;
		}
	}

	int Find(int x) {
		if(pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Join(int x, int y) {
		x = Find(x);
		y = Find(y);
		if(x == y) return;

		if(peso[x] < peso[y]) swap(x,y);

		peso[x] += peso[y];
		pai[y] = x;
	}	
} dsu;

vi lista, val;
vi g[MAXN];

bool mark[MAXN];

int main() {
	int n; scanf("%d", &n);

	lista.resize(n);
	val.resize(n);

	rep(i,0,n) scanf("%d", &val[i]), lista[i] = i;

	sort(all(lista), [](const int& x, const int& y) {
		return val[x] > val[y];
	});

	rep(i,1,n) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		g[u].eb(v);
		g[v].eb(u);
	}

	ll ans = 0;
	dsu.init(n);
	
	for(int u : lista) {
		mark[u] = 1;
		ll soma = 0;
		for(auto v : g[u]) {
			if(!mark[v]) continue;
			ans -= 1ll*dsu.peso[dsu.Find(v)]*soma*val[u];
			soma += dsu.peso[dsu.Find(v)];
			dsu.Join(u, v);
		}
		ans -= 1ll*soma*val[u];
	}

	reverse(all(lista));
	dsu.init(n); clr(mark, 0);

	for(int u : lista) {
		mark[u] = 1;
		ll soma = 0;
		for(auto v : g[u]) {
			if(!mark[v]) continue;
			ans += 1ll*dsu.peso[dsu.Find(v)]*soma*val[u];
			soma += dsu.peso[dsu.Find(v)];
			dsu.Join(u, v);
		}
		ans += 1ll*soma*val[u];
	}

	printf("%lld\n", ans);
}
