#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 2e5 + 100;
int c[maxn], used[maxn], sz[maxn], n;
vi g[maxn];
ll ans[maxn];

void dfs(int v = 0, int p=-1){
	sz[v] = 1;
	for(auto u : g[v]){
		if(u == p) continue;
		dfs(u, v);
		sz[v] += sz[u];
	}
}

void solve(int v=0, int p=-1){
	
	int last = used[c[v]];
	
	ll sum = sz[v]-1; //sum of all subtrees (-1 to remove itself)
	
	ans[c[v]] += 1ll*(n - last - sz[v] + 1)*(sz[v]);
	
	for(auto u : g[v]){
        if(u == p) continue;
        sum -= sz[u];
        ans[c[v]] += sz[u] * sum;
    }
	
	for(auto u : g[v]){
		if(u == p) continue;
		used[c[v]] = n-sz[u];
		solve(u, v);
	}
	
	used[c[v]] = last + sz[v];
}

int main(){
	FAST;
	
	cin >> n;
	
	for(int i = 0, val; i < n; i++){
		cin >> val;
		c[i] = --val;
	}
	
	for(int i = 1; i < n; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].pb(b);
		g[b].pb(a);
	}
		
	dfs();
	solve();
	
	for(int i = 0; i < n; i++)
		cout << ans[i] << '\n';
}
