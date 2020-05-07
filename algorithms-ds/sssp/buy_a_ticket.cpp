#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

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

const int maxn = 2e5 + 100;

int n, m;

vector<pll> g[maxn]; //vertex-to, weight

ll price[maxn];

void dijkstra(){
	bool mark[maxn];
	clr(mark, 0);
	
	priority_queue<pll, vector<pll>, greater<pll>> q;
	
	for(int i = 0; i < n; i++)
		q.push(mp(price[i], i));
		
	while(!q.empty()){
		ll u = q.top().ss;
		q.pop();
		
		if(mark[u]) continue;
		mark[u] = 1;
		
		for(auto nxt : g[u]){
			ll v = nxt.ff;
			ll w = nxt.ss;
			if(price[v] > price[u] + w){
				price[v] = price[u] + w;
				q.push(mp(price[v], v));
			}
		}
	}
}

int main(){
	FAST;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		ll u, v, w; cin >> u >> v >> w;
		u--, v--; 	//0-indexed
		w <<= 1; 	//multiply by 2 to make it go-return
		g[u].pb(mp(v,w));
		g[v].pb(mp(u,w));
	}
	read(price, 0, n);
	dijkstra();
	for(int i = 0; i < n; i++)
		cout << price[i] << ' ';
	cout << '\n';
}
