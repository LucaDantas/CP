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
constexpr int MAXN = 1e5 + 10;
constexpr int mod = 1000000007;

vi cor;

struct DSU {
	map<int, int> cnt[MAXN];
	vector<pair<ll,ll>> maior; // there can be multiples dominants {color, qtd}

	void init(int n) {
		maior.resize(n);
		rep(i,0,n) {
			cnt[i][cor[i]] = 1;
			maior[i] = {1, cor[i]};
		}
	}

	void update(int a, int b) {
		// we copy every value from b (smaller) to a
		assert(sz(cnt[a]) >= sz(cnt[b]));
		for(auto it : cnt[b]) {
			int color = it.ff, qtd = it.ss; // color is the one we're considering rn
			assert(qtd > 0);

			cnt[a][color] += qtd;
			int updated = cnt[a][color];
			
			if(updated == maior[a].ff) {
				maior[a].ss += color;
			}
			else if(updated > maior[a].ff) {
				maior[a] = {updated, color};
			}
		}

		cnt[b].clear();
	}

} dsu;

vi g[MAXN];

vector<ll> ans;

void dfs(int u, int pai=-1) {
	int maior = 0, bigchild = -1;
	for(auto v : g[u]) {
		if(v == pai) continue;
		dfs(v, u);
		
		if(sz(dsu.cnt[v]) > maior) {
			maior = sz(dsu.cnt[v]);
			bigchild = v;
		}
	}
	
	if(bigchild == -1) {
		ans[u] = cor[u];
		return;
	}
	dsu.update(bigchild, u);
	
	swap(dsu.cnt[u], dsu.cnt[bigchild]);
	swap(dsu.maior[u], dsu.maior[bigchild]);

	for(auto v : g[u]) {
		if(v == bigchild || v == pai) continue;
		dsu.update(u, v);
	}

	ans[u] = dsu.maior[u].ss;
}

int main() {
	int n; scanf("%d", &n);
	cor.resize(n); ans.resize(n);
	rep(i,0,n) scanf("%d", &cor[i]);
	dsu.init(n);

	rep(i,1,n) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		g[u].pb(v);
		g[v].pb(u);
	}

	dfs(0);

	rep(i,0,n) {
		printf("%lld%c", ans[i], " \n"[i==n-1]);
	}
}
