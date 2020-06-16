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

const int maxn = 1e5 + 100;

vi g[maxn][2];

int grau[maxn][2], tam[2], dist[maxn][2];

void dfs(int u, int pai, int k) {
	for(auto v : g[u][k]) {
		if(v == pai) continue;
		dist[v][k] = dist[u][k]+1;
		dfs(v,u,k);
	}
}

int center(int k) {
	queue<int> leafs;

	for(int i = 1; i <= tam[k]; i++) {
		if(grau[i][k] == 1)
			leafs.push(i);
	}

	int used = 0;
	while(tam[k] - used > 2) {
		int n = sz(leafs);
		used += n;
		while(n--) {
			int u = leafs.front();
			leafs.pop();
			grau[u][k]--; // Makes its degree 0 not to be counted again
			for(auto v : g[u][k]) {
				grau[v][k]--;
				if(grau[v][k] == 1)
					leafs.push(v);
			}
		}
	}

	dist[1][k] = 0;
	dfs(1,-1,k);
	
	if(sz(leafs) == 1)
		return leafs.front();
	else {
		int u1 = leafs.front();
		leafs.pop();
		int u2 = leafs.front();
		leafs.pop();
		if(dist[u1][k] > dist[u2][k])
			return u1;
		else
			return u2;
	}
}

int main(){
	scanf("%d %d", &tam[0], &tam[1]);

	for(int k = 0; k < 2; k++) {
		for(int i = 1; i < tam[k]; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u][k].pb(v);
			g[v][k].pb(u);
			grau[u][k]++;
			grau[v][k]++;
		}
	}	

	printf("%d %d\n", center(0), center(1));
}
