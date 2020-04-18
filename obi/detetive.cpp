#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define show(a) cout << #a << " = " << a << endl;
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

const int maxn = 1e3 + 100;

bitset<maxn> sources[maxn];
//bitset<maxn> verd;
vector<int> g[maxn], source, verd;
int grau[maxn], vis[maxn], pass;

void dfs(int u){
	vis[u] = pass;
	sources[u].set(source[pass]);
	for(auto v : g[u]){
		if(vis[v]==pass) continue;
		dfs(v);
	}
}

int main(){
	FAST;
	int n, m, v;
	cin >> n >> m >> v;
	memset(vis, -1, sizeof vis);
	for(int i = 0, a, b; i < m; i++){
		cin >> a >> b;
		g[a-1].pb(b-1);
		grau[b-1]++;
	}
	for(int i = 0, a; i < v; i++){
		cin >> a;
		verd.pb(a-1);
	}
	for(int i=0; i < n; i++)
		if(grau[i] == 0)
			source.pb(i);
	for(pass = 0; pass < (int)source.size(); pass++)
		dfs(source[pass]);
	
	vector<int> ans;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < v; j++){
			if((sources[i]&sources[verd[j]]) == sources[verd[j]]){
				ans.pb(i);
				break;
			}
		}
	}
	sort(ans.begin(), ans.end());
	for(auto a : ans) cout << a+1 << " ";
	cout << endl;
}
