#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
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

const int maxn = 1e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m, k;

vector<pii> g[maxn]; //vertex to, weight

ll dist[maxn];

int qtd[maxn];

int sources[maxn];

inline void dijkstra(){
	rep(i,0,n)
		dist[i] = inf;
	
	priority_queue<pli, vector<pli>, greater<pli>> q;
	
	rep(i,0,k)
		q.push({0LL,sources[i]}), qtd[sources[i]] = 1;
		
	while(!q.empty()){
		int u = q.top().ss;
		ll d = q.top().ff;
		
		q.pop();
		
		if(qtd[u] == 0) {qtd[u] = 1; continue;}
		
		if(qtd[u] == 1){
			dist[u] = d;
			
			qtd[u] = 2;
			
			for(auto pp : g[u]){
				int v = pp.ff;
				int w = pp.ss;
				
				if(qtd[v] < 2)
					q.push({d + w*1ll, v});
			}
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	
	rep(i,0,m){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		
		g[u].pb({v,w});
		g[v].pb({u,w});
	}
	
	rep(i,0,k)
		scanf("%d", &sources[i]);
	
	dijkstra();
	
	printf("%lld\n", dist[0]);
}
