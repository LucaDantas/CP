#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<pii, int> piii;
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

const int maxn = 3e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m;

struct Edge{
	int u, v, w;
} edges[maxn];

vector<piii> g[maxn];

ll dist[maxn], ans = 0;

bool mark[maxn];

int edge_pai[maxn]; //we can check the cost of the edge by just looking at the edges arr

void dijkstra(int s){
	rep(i,1,n+1)
		dist[i] = inf;
		
	dist[s] = 0ll;
		
	priority_queue<pli, vector<pli>, greater<pli>> q;
	
	q.push({0ll, s});
	
	while(!q.empty()){
		int u = q.top().ss;
		q.pop();
		
		if (mark[u]) continue;
		mark[u] = 1;
		
		for(auto pp : g[u]){
			int v = pp.ff.ff;
			int w = pp.ff.ss;
			int id = pp.ss;
			
			if(dist[v] == dist[u] + w && edges[edge_pai[v]].w > w){
				ans += w - edges[edge_pai[v]].w;
				edge_pai[v] = id;
			}
			
			if(dist[v] > dist[u] + w){
				ans += w - (edges[edge_pai[v]].w? edges[edge_pai[v]].w : 0);
				
				edge_pai[v] = id;
				dist[v] = dist[u] + w;
				
				q.push({dist[u] + w, v});
			}
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	
	rep(i,1,m+1){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		
		g[u].pb({{v,w}, i});
		g[v].pb({{u,w}, i});
		edges[i] = {u,v,w};
	}
	
	//rep(i,1,n+1)
		//rep(j,0,sz(g[i]))
			//printf("from %d to %d weight %d\n", i, g[i][j].ff.ff, g[i][j].ff.ss);
	
	int s; scanf("%d", &s);
	
	dijkstra(s);
	
	printf("%lld\n", ans);
	
	rep(i,1,n+1)
		if(i != s)
			printf("%d%c", edge_pai[i], " \n"[i==n]);
	if(s == n) puts("");
	//print the minimal total weight
	//indices of the edges included - any order - to do this save the index of each parent edge
}
