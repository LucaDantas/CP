#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v) for(int i=0; i < sz(v); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f; // approx 4*10^18 - 8 times 3f - hexadecimal repres

int n, m;

vector<pii> g[maxn]; //pair(vertex "to", weight)

ll dist[maxn];

bool mark[maxn];

void dijkstra(int s){
	for(int i = 1; i <= n; i++)
		dist[i] = inf;
		
	priority_queue<pli, vector<pli>, greater<pli>> q;
	
	dist[s] = 0;
	
	q.push(mp(0LL, s));
	
	while(!q.empty()){
		int u = q.top().second; //vertex in the top of the list
		
		q.pop(); //remove it from the list
		
		if(mark[u])
			continue;
			
		mark[u] = 1;
		
		
		for(auto next : g[u]){ //for every adjacent node
			
			int v = next.first;
			
			int w = next.second;
			
			if(dist[v] > dist[u] + (ll)w){ //relax the path
				
				dist[v] = dist[u] + (ll) w;
				
				q.push(mp(dist[v], v)); //add v to the queue
				
			}
			
		}
	}
}

void find_path(int u, vi &ans){
	
	ans.pb(u);
	
	for(auto next : g[u]){
		int v = next.first, w = next.second;
		if(dist[v] == dist[u] - w){
			find_path(v, ans);
			return;
		}
	}
}

int main(){
	FAST;
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b, w; cin >> a >> b >> w;
		g[a].pb(mp(b, w));
		g[b].pb(mp(a, w));
	}
	
	dijkstra(1);
	
	if(dist[n] == inf) {cout << "-1\n"; return 0;}
	
	vi ans;
	
	find_path(n, ans);
	
	reverse(all(ans));
	
	for(auto it : ans) cout << it << ' ';
	cout << '\n';
}
