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

const int maxn = 550, inf = 0x3f3f3f3f;

int val_cara[maxn], val_node[maxn]; //o valor de val cara nunca troca, somente o do nó

vi atual(maxn); //representa o nó em que o cara está, não o cara que está no nó

vi g[maxn];

bool mark[maxn];

int dfs(int u) {
	int ans = val_node[u];
	for(auto v : g[u]) {
		if(!mark[v]) {
			mark[v] = 1;
			ans = min(ans, dfs(v));
		}
	}
	return ans;
}

int main(){
	FAST;
	int n, m, Q;
	cin >> n >> m >> Q;
	
	for (int i = 1; i <= n; i++) {
		cin >> val_cara[i];
		val_node[i] = val_cara[i];
	}
	
	for (int i = 1; i <= n; i++) {
		atual[i] = i;
	}
	
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[v].pb(u);
	}
	
	for (int q = 1; q <= Q; q++) {
		char tipo;
		cin >> tipo;
		//cout << tipo << '\n';
		
		if(tipo == 'P') {
			int a; cin >> a;
			
			auto posA = find(all(atual), a);
			
			int ans = inf;
			
			//db(posA - atual.begin());
			
			clr(mark, 0);
			mark[posA - atual.begin()] = 1;
			
			for(auto v : g[posA-atual.begin()])
				ans = min(ans, dfs(v));
			
			if(ans != inf) printf("%d\n", ans);
			else printf("*\n");			
		}
		
		else {
			int a, b;
			cin >> a >> b;
			auto posA = find(all(atual), a);
			auto posB = find(all(atual), b);
			swap(*posA, *posB);

			
			val_node[posB-atual.begin()] = val_cara[a];
			val_node[posA-atual.begin()] = val_cara[b];
			
			//for (int i = 1; i <= n; i++) {
				//printf("Nó atual do cara %d: %d\n", i, atual[i]);
			//}
			//puts("");
		}
	}
	
	//for (int i = 1; i <= n; i++) {
		//printf("Nó atual do cara %d: %d\n", i, atual[i]);
	//}
	
	//for (int i = 1; i <= n; i++) {
		//printf("Valor atual do nó %d: %d\n", i, val_node[i]);
	//}
}
