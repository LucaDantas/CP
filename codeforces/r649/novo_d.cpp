#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 1e5 + 100;

vi g[maxn];

int level[maxn], aux = 0;

bool mark[maxn];

int n, m, k;

vi path;

void dfs(int u) {
	level[u] = sz(path);
	path.pb(u);
	int best = -1;
	for(auto v : g[u]) {
		if(level[v] && level[u] - level[v] > 1) {
			best = max(best, level[v]);
		}
	}
	if(best != -1) {
		// We have a cycle so we can end here, and we're sure there is nothing cutting through it because
		// it is the deepest node going up from him and we're on the first cycle that was found
		if(level[u]-best+1 <= k) {
			printf("2\n%d\n", level[u]-best+1);
			rep(i,best, level[u]+1)
				printf("%d%c", path[i], " \n"[i==level[u]]);
		}
		else {
			printf("1\n");
			k = (k+1)/2;
			for(int i = best; i < level[u] && k; i += 2)
				printf("%d%c", path[i], " \n"[k--==1]);
		}
		exit(0);
	}
	for(auto v : g[u]) {
		if(!level[v])
			dfs(v);
	}
	if(!mark[u]) for(auto v : g[u]) mark[v] = 1; // For the case it is a tree, we start from the leafs
	path.pop_back();
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	rep(i,0,m) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1);
	k = (k+1)/2;
	puts("1");
	for(int i = 1; i <= n && k; i++)
		if(!mark[i])
			printf("%d%c", i, " \n"[k--==1]);
}
