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

const int maxn = 5e5 + 100, inf = 0x3f3f3f3f;

// A gente tem q fazer tipo uma bfs e ir salvando cada nível, ou seja a gente salva os caras em 'bucket' diferentes
// tipo, os caras que a gente quer que tenham 1 salva no bucket 1, 2 no bucket 2 e assim vai

// A gente vai ir colocando nos vizinhos do

// quando chegar em um cara a gente pega todos os vizinhos dele, coloca num set e a dentro desse set que vai ta ordenado
// a gente pega qual o menor que não apareceu ainda

vector<int> g[maxn], bucket[maxn], ans; //weight of the number - value of the neighbour
int val[maxn];
set<int> seen[maxn];

bool bad = false;

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	rep(i,0,m) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	rep(i,1,n+1) {
		int u; scanf("%d", &u);
		val[i] = u;
		bucket[u].pb(i);
		if(seen[u].find(i) != seen[u].end()) bad = true;
		allin(it, g[i]) seen[u].insert(it);
	}
	if(bad) {printf("-1\n"); return 0;}
	rep(lvl,1,n+1) {
		for(auto u : bucket[lvl]) {
			set<int> now;
			for(auto v : g[u]) {
				if(val[v] <= lvl) now.insert(val[v]);
			}
			int want = sz(now) + 1;
			int i = 1;
			for(auto it = now.begin(); it != now.end(); ++it, i++) {
				// db(i);
				if(*it != i) {want = i; break;}
			}
			if(want != val[u]) {printf("-1\n"); return 0;}
			ans.pb(u);
		}
	}
	rep(i,0,n) printf("%d%c", ans[i], " \n"[i==n-1]);
}
