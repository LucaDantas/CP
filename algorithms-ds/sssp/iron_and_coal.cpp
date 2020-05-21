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

const int maxn = 1e5 + 100, inf = 0x3f3f3f3f;

int n, m, k;

vi g[maxn][3], iron, coal;

int dist[maxn][3]; 	// dist 0 is from initial vertex(1), dist 2 is from some iron,
					// dist 3 is from some coal

bool mark[maxn];

void bfs(int t){
	clr(mark, 0);
	queue<int> q;
	
	rep(i,1,n+1)
		dist[i][t] = inf;
	
	if(t == 0){
		mark[1] = 1;
		dist[1][t] = 0;
		q.push(1);
	}
	
	if(t == 1){
		trav(it, iron){
			mark[it] = 1;
			dist[it][t] = 0;
			q.push(it);
		}
	}
	
	if(t == 2){
		trav(it, coal){
			mark[it] = 1;
			dist[it][t] = 0;
			q.push(it);
		}
	}
	
	while(!q.empty()){
		int u = q.front();
		q.pop();
		
		for(auto v : g[u][t]){
			if(!mark[v]){
				mark[v] = 1;
				dist[v][t] = dist[u][t] + 1;
				q.push(v);
			}
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	
	iron.resize(m);
	coal.resize(k);
	
	trav(it, iron)
		scanf("%d", &it);
	
	trav(it, coal)
		scanf("%d", &it);
		
	rep(u,1,n+1){
		int a; scanf("%d", &a);
		rep(i,0,a){
			int v; scanf("%d", &v);
			g[u][0].pb(v);
			g[v][1].pb(u);
			g[v][2].pb(u);
		}
	}
	
	bfs(0); bfs(1); bfs(2); // bfs 0 is from the beginning of the map - bfs 1 is from each
							// iron and bfs 2 is from each coal
		
	int ans = inf;
	
	rep(i,1,n+1)
		if(dist[i][0] != inf && dist[i][1] != inf && dist[i][2] != inf)
			ans = min(ans, dist[i][0] + dist[i][1] + dist[i][2]);
	
	if(ans != inf)
		printf("%d\n", ans);
	else
		puts("impossible");
}
