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
#define jump cerr << '\n';
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

// What we'll do here is a priority queue with small to large. The first thing
// Important to notice is that it is a tree, since every node (ninja) only has
// one parent (boss), which means that we can't any no cycles even if a node
// has multiple children (just like in trees).

// Then what we're going to do is a small to large / dsu on trees, using a
// a priority queue and keeping the group of smallest nodes for each vertex
// keeping the invariant that the sum of the values in each priority queue
// will never be greater than the budget we have, and we're going to compute
// the answer for each node by calculating the product of the size of the pq
// by the leadership value updated (we update by propagating the maximal to 
// that node's children, because we can always choose any parent to be the 
// manager of the entire group)

int m;

int L[MAXN], C[MAXN];

vi g[MAXN];

struct DSU {
	vector<ll> sum;
	vector<priority_queue<int>> menores;
	
	void init(int n) {
		sum.resize(n+1);
		menores.resize(n+1);
		rep(i,1,n+1) {
			assert(C[i] <= m);
			sum[i] = C[i];
			menores[i].push(C[i]);
		}
	}

	void update(int a, int b) {
		assert(sz(menores[a]) >= sz(menores[b]));
		while(!menores[b].empty()) {
			int now = menores[b].top();
			menores[b].pop();
			if(sum[a] + now <= m) {
				sum[a] += now;
				menores[a].push(now);
			}
			else {
				if(now >= menores[a].top()) continue;
				sum[a] -= menores[a].top();
				menores[a].pop();
				sum[a] += now;
				assert(sum[a] <= m);
				menores[a].push(now);
			}
		}
	}
} dsu;

ll ans = 0;

void dfs(int u, int pai=-1) {
	int maior = 0, bigchild = -1;

	for(auto v : g[u]) {
		if(v == pai) continue;
		dfs(v, u);
		if(sz(dsu.menores[v]) > maior) {
			maior = sz(dsu.menores[v]);
			bigchild = v;
		}
	}

	if(bigchild == -1) { // has no children, so it's a leaf node
		ans = max(ans, 1ll*L[u]*sz(dsu.menores[u]));
		return;
	}

	dsu.update(bigchild, u); // give u to bigchild
	swap(dsu.menores[bigchild], dsu.menores[u]);
	swap(dsu.sum[bigchild], dsu.sum[u]);

	for(auto v : g[u]) {
		if(v == pai || v == bigchild) continue;
		dsu.update(u, v);
	}

	assert(dsu.sum[u] <= m);
	ans = max(ans, 1ll*L[u]*sz(dsu.menores[u]));
}

int main() {
	int n;
	scanf("%d %d", &n, &m);
	
	int trash;
	scanf("%d %d %d", &trash, &C[1], &L[1]);
	
	rep(i,2,n+1) {
		int pai;
		scanf("%d %d %d", &pai, &C[i], &L[i]);
		assert(pai > 0);
		g[pai].pb(i);
	}

	dsu.init(n);

	dfs(1);

	printf("%lld\n", ans);
}
