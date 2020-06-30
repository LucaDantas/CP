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

vector<pair<int, bool>> g[maxn];
bitset<maxn> visited;
int level[maxn], pai[maxn], sq;
pair<int, int> ciclo = {-1,-1};
set<int> blocked;
vector<int> pick;

void dfs(int u=0, int l=0, int p=-1){
	visited.set(u);
	level[u] = l;
	pai[u]=p;
	int maxback=0;
	for(auto &v : g[u]){
		if(visited.test(v.f)){
			maxback = max(maxback, level[u] - level[v.f]);
		}
		else{
			v.s = true;
			dfs(v.f, l+1, u);
		}
	}
	if(maxback >= sq-1){
		ciclo = {u, maxback+1};
		return;
	}
	else if(blocked.find(u) == blocked.end() && (int)pick.size() < sq){
		pick.pb(u);
		for(auto v : g[u]){
			blocked.insert(v.f);
		}
		if((int)pick.size() == sq) return;
	}
}

int main(){
	FAST;
	int n, m;
	cin >> n >> m;
	sq = sqrt(n);
	if(sq*sq != n) sq++;
	for(int i = 0, a, b; i < m; i++){
		cin >> a >> b;
		a--,b--;
		g[a].pb(mp(b,false));
		g[b].pb(mp(a,false));
	}
	dfs();
	if(ciclo != mp(-1,-1)){
		int size = ciclo.s, u = ciclo.f;
		cout << 2 << endl << size << endl;
		while(size--){
			cout << u+1 << ' ';
			u = pai[u];
		}
		cout << endl;
	}
	else{
		cout << 1 << endl;
		for(auto it : pick)
			cout << it+1 << ' ';
		cout << endl;
	}
}
