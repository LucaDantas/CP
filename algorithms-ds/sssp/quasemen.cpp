#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 550;
const int inf = 0x3f3f3f3f;

int n, m;

void dijkstra(int s, vector<pii>(&g)[maxn], vi &dist){ //passes the graph by reference so we don't need to write two dijkstra, one from inverse and other for normal
	
	bool mark[maxn];
	clr(mark, 0);
	
	for(int i = 0; i < n; i++)
		dist[i] = inf;
	
	priority_queue<pii, vector<pii>, greater<pii>> q;

	dist[s] = 0;
	q.push({0, s});
	
	while(!q.empty()){
		int u = q.top().second;
		
		q.pop();
		
		if(mark[u]) continue;
		mark[u] = 1;
		
		for(auto next : g[u]){
			int v = next.first;
			int p = next.second;
			
			if(dist[v] > dist[u] + p){
				dist[v] = dist[u] + p;
				q.push({dist[v], v});
			}
		}
	}
}

int main(){
	FAST;
	while(true){
		
		cin >> n >> m;
		if(!(n+m)) break;
		
		int s, d; cin >> s >> d;
		
		vector<pii> g[maxn], ginv[maxn], gfim[maxn];
		vector<piii> edges;
		vi dist(n), dist_inv(n), dist_fim(n);
		
		clr(g, 0);
		clr(ginv, 0);
		
		rep(i, 0, m){
			int u, v, p; cin >> u >> v >> p;
			g[u].pb(mp(v, p));
			ginv[v].pb(mp(u,p));
			edges.pb(mp(p, mp(u,v)));
		}
		
		dijkstra(s, g, dist);
		dijkstra(d, ginv, dist_inv);
		
		//build the last graph
		
		for(auto e : edges){
			int p = e.first;
			int u = e.second.first, v = e.second.second;
			if(dist[u] + p + dist_inv[v] != dist[d]) gfim[u].pb(mp(v, p));
		}
		
		dijkstra(s, gfim, dist_fim);
		
		if(dist_fim[d] == inf) cout << -1 << '\n';
		else cout << dist_fim[d] << '\n';
	}
}
