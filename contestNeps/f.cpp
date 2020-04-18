#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define pib pair<int, bool>
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
const int inf = 1000;
//The adj list will have the vertex that this edge connects 
//and wether it is a span (true) or back (false) -edge
vector<pib> g[maxn];
bitset<maxn> visited;
int level[maxn] /*this is ok*/, dp[maxn];

void visit(int u = 0, int l=0, int pai=-1){ //CERTO
	level[u] = l;
	visited.set(u);
	for(auto &v : g[u]){
		if(v.f == pai)
			v.s = true;
		if(!visited.test(v.f)){
			v.s = true;
			//I need to make the edge true from both sides - This only makes it in one
			//g[v.f][u].s = true;
			visit(v.f, l+1, u);
		}
	}
}

void build(int u = 0){ //FUDIDO
	//visited.set(u);
	for(auto v : g[u]){
		if(v.s){
			if(level[v.f] > level[u]){
				build(v.f);
				dp[u] += dp[v.f];
			}
		}
		else{
			//cout << u+1 << ' ' << v.f+1 << endl;
			if(level[v.f] > level[u]){
				dp[u]--;
			}
			else{
				dp[u]++;
			}
		}
	}
}

int main(){
	FAST;
	int n, m;
	cin >> n >> m;
	for(int i = 0, a, b; i < m; i++){ //CERTO
		cin >> a >> b;
		//We start with everything false (back-edge)
		//and then we run dfs to create the dfs-tree setting the span-edges
		g[a].pb(mp(b,false));
		g[b].pb(mp(a,false));
	}
	
	visit(); //CERTO
	visited.reset();
	build(); //FUDIDO
	
	//RESPOSTA
	int ans=0;
	//We skip dp[0] because it'll always be 0, but it has no parents so it doesn't count
	for(int i = 1; i < n; i++){
		if(dp[i] == 0) ans++;
	}
	cout << ans << endl;
	
	//DEBUG PRA PRINTAR OS VALORES DA DP DE CADA - TA ERRADO ESSA PORRA
	//for(int i = 0; i < n; i++)
		//cout << dp[i] << ' ';
	//cout << endl;
	
	//DEBUG PRA ACHAR O LVL DO VERTEX
	//for(int i = 0; i < n; i++)
		//cout << level[i] << ' ';
	//cout << endl;
	
	//DEBUG PRA PRINTAR OS EDGES
	//for(int i = 0; i < n; i++){
		//for(auto it : g[i]){
			//if(it.s) cout << i+1 << ' ' << it.f+1 << endl;
		//}
	//}
}
