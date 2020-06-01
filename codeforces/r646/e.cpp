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

const int maxn = 2e5 + 100;

int a[maxn], has[maxn], price[maxn], unbalance[maxn];

bool mark[maxn];

vi g[maxn];

void dfs(int u) {	
	unbalance[u] = has[u];
	for(auto v : g[u]) {
		if(mark[v]) continue;
		mark[v] = 1;
		price[v] = min(price[u], a[v]);
		dfs(v);
		unbalance[u] += unbalance[v];
	}
}

int main(){
	int n, tot = 0;
	scanf("%d", &n);
	
	rep(i,1,n+1) {
		int now, want;
		scanf("%d %d %d", &a[i], &now, &want);
		has[i] = now - want;
		tot += has[i];
	}
	
	rep(i,1,n) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	
	if(tot) {puts("-1"); return 0;}
	
	// we must find the best value for each node
	// and also the unbalance of his subtree
	// we do that with a dfs
	
	price[1] = a[1];
	mark[1] = 1;
	dfs(1);
	
	ll ans = 0;	
	
	queue<int> q;
	q.push(1);
	
	clr(mark, 0);
	
	while(!q.empty()) {
		int u = q.front(), abrem = 0, fecham = 0;
		if(has[u] < 0) abrem++;
		if(has[u] > 0) fecham++;
		q.pop();
		for(auto v : g[u]) {
			if(mark[v]) continue;
			mark[v] = 1;
			if(unbalance[v] < 0) abrem -= unbalance[v];
			if(unbalance[v] > 0) fecham += unbalance[v];
			q.push(v);
		}
		ans += 2ll*min(abrem, fecham)*price[u];
	}
	
	printf("%lld\n", ans);
}
