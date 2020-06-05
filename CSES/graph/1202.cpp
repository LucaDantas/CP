#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, pii> plii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

int n, m;

vector<pli> g[maxn][2]; //0 is normal 1 is inversed - weight , vertex-to

vector<plii> edges;

ll dist[maxn][2];

void dijkstra(int s, int k){
	bool mark[maxn];
	clr(mark,0);
	
	rep(i,1,n+1)
		dist[i][k] = inf;
		
	priority_queue<pli, vector<pli>, greater<pli>> q;
	
	dist[s][k] = 0;
	q.push({0,s});
	
	while(!q.empty()){
		int u = q.top().ss;
		ll d = q.top().ff;
		
		q.pop();
		
		if(!mark[u]){
			mark[u] = true;
			
			for(auto pp : g[u][k]){
				ll w = pp.ff;
				int v = pp.ss;
				if(dist[v][k] > d + w){
					dist[v][k] = d + w;
					q.push({d+w, v});
				}
			}
			
		}
	}
	
}

vi dag[maxn];

vi topo;

bool mark[maxn];

int dp[maxn][3];

void dfs(int u){
	mark[u] = true;
	for(auto v : dag[u])
		if(!mark[v])
			dfs(v);
	topo.pb(u);
}

int main(){
	scanf("%d %d", &n, &m);
	rep(i,0, m){
		int u, v; ll w;
		scanf("%d %d %lld", &u, &v, &w);
		g[u][0].pb({w,v});
		g[v][1].pb({w,u});
		edges.pb({w,{u,v}});
	}
	dijkstra(1,0);
	dijkstra(n,1);
	
	ll mdist = dist[n][0];
	
	for(auto e : edges){
		ll w = e.ff;
		int u = e.ss.ff;
		int v = e.ss.ss;
		if(dist[u][0] + w + dist[v][1] == mdist){
			dag[u].pb(v);
		}
	}
	
	dfs(1);
	reverse(all(topo));
	
	dp[1][0] = 1;
	
	rep(i,2,n+1)
		dp[i][1] = 0x3f3f3f3f;
	
	for(auto u : topo){
		for(auto v : dag[u]){
			dp[v][0] = (dp[u][0] + dp[v][0])%MOD;
			dp[v][1] = min(dp[v][1], dp[u][1]+1);
			dp[v][2] = max(dp[v][2], dp[u][2]+1);
		}
	}
	
	printf("%lld %d %d %d\n", mdist, dp[n][0], dp[n][1], dp[n][2]);
}
