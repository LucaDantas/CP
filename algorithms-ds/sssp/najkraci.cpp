#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
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

const int maxn = 1600, maxm = 5e3 +100, inf = 0x3f3f3f3f;
const int MOD = 1e9+7;

int n, m;

vector<piii> g[maxn]; //vertex to, weight, id of the edge

struct Edge{
	int w, from, to;
} edge[maxm];

int dist[maxn][maxn]; //distance to each edge from each edge

bool mark[maxn];

void dijkstra(int s){
	clr(mark, 0);
	
	rep(i,1,n+1)
		dist[i][s] = inf;
	
	dist[s][s] = 0;
	
	priority_queue<pii, vector<pii>, greater<pii>> q;
	
	q.push({0,s});
	
	while(!q.empty()){
		int u = q.top().ss;
		
		q.pop();
		
		if(!mark[u]){
			mark[u] = 1;
			
			for(auto pp : g[u]){
				int v = pp.ff;
				int w = pp.ss.ff;
				
				if(dist[v][s] > dist[u][s] + w)
				{	
					dist[v][s] = dist[u][s] + w;
					q.push({dist[v][s], v});
				}
				
			}
		}
	}
}

vector<pii> dag[maxn]; //to, id of the vertex

vi topo;

int dp[maxn], nxt[maxn];

int caminhos[maxm];

void dfs(int u){
	mark[u] = 1;
	
	for(auto v : dag[u])
		if(!mark[v.ff])
			dfs(v.ff);
			
	topo.pb(u);
}

void init(){
	rep(p,1,n+1)
			dag[p].clear();
			
	topo.clear();
	
	clr(mark, 0);
	clr(dp, 0);
	clr(nxt, 0);
}

int main(){
	scanf("%d %d", &n, &m);
	
	rep(i,1,m+1){
		//1-INDEXED
		int u, v, w;scanf("%d %d %d", &u, &v, &w);
		
		g[u].pb({v,{w, i}});
		edge[i] = {w, u, v};
	}
	
	//Calculate APSP
	rep(i,1,n+1) dijkstra(i);
	
	//Count the number of SP from each source
	
	rep(i,1,n+1){
		
		init();
		
		//Build dag
		rep(j,1,m+1){
			int &u = edge[j].from, &v = edge[j].to, &w = edge[j].w;
			if(dist[u][i] + w == dist[v][i])
				dag[u].pb({v, j});
		}
		
		
		dfs(i); //top sort
		
		for(auto u : topo){
			
			nxt[u] = 1;
			
			for(auto pp : dag[u]){
				int v = pp.ff;
				
				nxt[u] = (nxt[u] + nxt[v])%MOD;
			}
		}
		
		reverse(all(topo));
		
		dp[i] = 1;
		
		for(auto u : topo){
		
			for(auto pp : dag[u]){
				int v = pp.ff;

				dp[v] = (dp[v]+dp[u])%MOD;
			}
		}
		
		for(auto u : topo){
		
			for(auto pp : dag[u]){
				int v = pp.ff;
				int id = pp.ss;
		
				caminhos[id] = (caminhos[id]+ (1ll*dp[u]*nxt[v])%MOD)%MOD;
			}
		}
		
	} 
	
	rep(i,1,m+1) printf("%d\n", caminhos[i]);
}
