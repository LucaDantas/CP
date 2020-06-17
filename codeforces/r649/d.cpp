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

// We find the smallest cycle using dfs-tree, and if there is a cycle we consider the answer from it
// (the smallest one), otherwise it's a tree (each connected component) and we can easily find the
// maximum independent set

const int maxn = 1e5+100, inf = 0x3f3f3f3f;

int n, m, k, aux = 0;

vi g[maxn], path;

bool mark[maxn];

vector<int> pos;

int level[maxn];

void dfs(int u) {
	level[u] = sz(pos);
	pos.pb(u);

	for(auto v : g[u]) {
		if(!level[v])
			dfs(v);
		else if(level[u]-level[v]+1 > 2 && level[u]-level[v]+1 <= k) {
			// The first check is used both to check if u came after v and to check if it isn't
			// its direct child which wouldn't be a cycle
			puts("2");
			printf("%d\n", level[u]-level[v]+1);
			for(int i = level[v]; i <= level[u]; i++)
				printf("%d%c", pos[i], " \n"[i==level[u]]);
			exit(0);
		}
	}
	if(!mark[u]) for(auto v : g[u]) mark[v] = 1;
	pos.pop_back(); // remove u and its subtree
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
	for(int i = 1; i <= n && k; i++) {
		if(!mark[i])
			printf("%d%c", i, " \n"[k==1]), k--;
	}
}
