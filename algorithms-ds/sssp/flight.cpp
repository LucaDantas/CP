#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
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

const int maxn = 1e5 + 100, maxm = 2e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f;

//struct Edge{
	//int from, to, w;
//} edges[maxm];

int n, m, k;

vector<pli> g[maxn]; //weight, vertex-to - 1-indexed

bool mark[maxn];
	
ll dist[maxn][15];

int qtd[maxn];
	
void dijkstra(int s){
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= 11; j++)
			dist[i][j] = inf;
			
	priority_queue<pli, vector<pli>, greater<pli>> q;
	
	q.push({0,s});
	
	while(!q.empty()){
		
		int u = q.top().ss;
		ll d = q.top().ff;
		
		q.pop();
		
		if(qtd[u] == k) continue;
		
		dist[u][qtd[u]] = d;
		
		qtd[u]++;
		
		for(auto pp : g[u]){
			ll w = pp.ff;
			int v = pp.ss;
			q.push({d+w,v});
		}
		
	}
}

int main(){
	//FAST;
	scanf("%d %d %d", &n, &m, &k);
	rep(i,1,m+1){
		int a, b; ll w; scanf("%d %d %lld", &a, &b, &w);
		g[a].pb({w, b});
	}
	dijkstra(1);
	for(int i = 0; i < k; i++)
		printf("%lld%c", dist[n][i], " \n"[i==k-1]);
}
