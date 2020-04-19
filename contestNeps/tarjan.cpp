#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ll long long
#define f first
#define s second
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define debug(x) cout << "DEBUG " << x << endl
#define debug2(x, y) cout << "DEBUG " << x << " " << y << endl
#define debug3(x, y, z) cout << "DEBUG " << x << " " << y << " " << z<< endl
#define debug4(x, y, z, o) cout << "DEBUG " << x << " " << y << " " << z<< " " << o << endl
#define max3(x, y, z) max(x, max(y, z))

const int maxn = 1e5 + 100;
const int inf = 1e9+100;
vector<int> g[maxn];
vector<pair<int, int>> bridges;
int disc[maxn], low[maxn], pai[maxn];
bitset<maxn> visited;

void dfs(int u = 0, int d = 0, int p=-1){
	visited.set(u);
	vector<int> comp;
	disc[u] = low[u] = d;
	pai[u] = p;
	for(auto v : g[u]){
		//if(v==p) continue;
		if(visited.test(v)){ //continue;
			comp.pb(v);
			low[u] = min(low[u], disc[v]);
		}
		else{
			dfs(v, d+1, u);
			low[u] = min(low[u], low[v]);
			//if(low[v] < disc[u]) bridges.pb(mp(u,v));
		}
	}
	//for(auto v : comp){
		//low[v] = min(low[u], low[v]);
		//if(low[u] >= disc[v]) bridges.pb(mp(u,v));
	//}
}

int main(){
	FAST;
	int n, m;
	cin >> n >> m;
	for(int i = 0, a, b; i < m; i++){
		cin >> a >> b;
		a--, b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs();
	for(int u = 1; u < n; u++){
		if(low[u] >= disc[pai[u]]) bridges.pb(mp(u,pai[u]));
	}
	cout << bridges.size() << endl;
	for(auto k : bridges)
		cout << k.f+1 << ' ' << k.s+1 << endl;
	//for(int k=0; k <n;k++)
		//cout << low[k]+1 << ' ';
	//cout << endl;
}
