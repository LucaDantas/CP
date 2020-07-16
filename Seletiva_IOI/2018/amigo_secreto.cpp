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
#define db(a) cerr << "DEBUG ( " << #a << " == ", debug(a), cerr << ")\n"
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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

pii f[maxn];
int cc, fam[maxn];
vi head;
vector<pii> in[maxn];

ll ans;

int mark[maxn];
bool in_cycle[maxn], done[maxn];
pii edge_cycle[maxn];

void dfs(int u) {
	mark[u] = 1;
	int v = f[u].ff, c = f[u].ss;
	in[v].eb(u, c);
	if(mark[v] == 0)
		dfs(v), fam[u] = fam[v];
	else if(mark[v] == 2)
		fam[u] = fam[v];
	else {
		fam[u] = cc;
		head.eb(u);
		cc++;
	}
	mark[u] = 2;
}

void dfs2(int u) {
	int v = f[u].ff, c = f[u].ss;
	edge_cycle[v] = {u, c};
	in_cycle[u] = 1;

	if(v != head[fam[u]]) dfs2(v);
}

int main() {
	int n; scanf("%d", &n);
	rep(i,1,n+1) scanf("%d %d", &f[i].ff, &f[i].ss);
	rep(i,1,n+1) if(!mark[i]) dfs(i);

	for(auto u : head) dfs2(u);

	bool check = 1;
	rep(i,1,n+1) if(in_cycle[i] == 0) check = 0;
	if(cc == 1 && check) {
		printf("0\n");
		return 0;
	}

	vi best(cc, inf);

	rep(i,1,n+1) {
		int mx = 0;
		if(in_cycle[i]) {
			for(auto l : in[i]) {
				if(l == edge_cycle[i]) continue;
				mx = max(mx, l.ss); ans += l.ss;
			}
			ans -= mx;

			if(edge_cycle[i].ss <= mx)
				done[fam[i]] = 1, ans += edge_cycle[i].ss;
			else
				ans += mx, best[fam[i]] = min(best[fam[i]], edge_cycle[i].ss-mx);
		}
		else {
			for(auto l : in[i])
				mx = max(mx, l.ss), ans += l.ss;
			ans -= mx;
		}
	}

	rep(i,0,cc) if(!done[i]) ans += best[i];

	printf("%lld\n", ans);
}
