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

const int maxn = 1e6 + 10;

int n, m;

struct Edge
{
	int u, l, r;
} edges[maxn];

vi g[maxn];

int ind[maxn], aux;

int mark[maxn];

void build(int node, int i, int j) {
	if(i == j) {
		ind[node] = ++aux;
		g[ind[node]].pb(i);
		return;
	}
	int mid = (i+j) >> 1;
	build(2*node, i, mid); build(2*node+1, mid+1, j);
	ind[node] = ++aux;
	g[ind[node]].pb(ind[2*node]);
	g[ind[node]].pb(ind[2*node+1]);
}

bool dfs(int u) {
	mark[u] = 1;
	for(auto v : g[u]) {
		if(mark[v] == 1 || (mark[v] == 0 && dfs(v))) return true; 
	}
	mark[u] = 2;
	return false;
}

void update(int node, int i, int j, int l, int r, int u) {
	if(i > r || j < l) return;
	if(i >= l && j <= r) {
		g[u].pb(ind[node]);
		return;
	}
	int mid = (i+j) >> 1;
	update(2*node, i, mid, l, r, u);
	update(2*node+1, mid+1, j, l, r, u);
}

bool find(int x) {
	clr(mark, 0);
	for(int i = 1; i <= n; i++)
		g[i].clear();

	for(int i = 1; i <= x; i++) {
		update(1,1,n,edges[i].l, edges[i].r, edges[i].u);
	}

	for(int i = 1; i <= n; i++)
		if(!mark[i] && dfs(i))
			return true;

	return false;
}

int bs(void) {
	int l = 1, r = m, ans = -1;
	while(l <= r) {
		int mid = (l+r) >> 1;
		if(find(mid))
			ans = mid, r = mid-1;
		else
			l = mid+1;
	}
	return ans;
}

int main(void){
	scanf("%d %d", &n, &m);

	for(int i = 1; i <= m; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].l, &edges[i].r);
	}

	aux = n;
	build(1,1,n);

	printf("%d\n", bs());
}
