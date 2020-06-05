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

// Solution is the same as in the noic editorial -> https://noic.com.br/materiais-informatica/problemas-da-semana/avancado-semana4/solucao/

// I first need to find the connected components and then find wheter there is a cycle or not in each of those,
// because if there is we can simply do a big group union and every request inside that connected component
// will be satisfied, and if there is no cycle we can simply know that we can have |C| - 1 because we can put 
// them in a straight line, since there are no cycles, which means that we don't need to go back in that line

vi g[maxn], g2[maxn];

int grau[maxn];

bool mark[maxn];

void dfs(int u, vi& cc) {
	cc.pb(u);
	mark[u] = 1;
	for(auto v : g2[u]) {
		if(!mark[v])
			dfs(v, cc);
	}
}

bool bfs(const vi& cc) {
	queue<int> q;
	for(auto u : cc)
		if(grau[u] == 0)
			q.push(u);

	int qtd = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		qtd++;

		for(auto v : g[u]) {
			grau[v]--;
			if(!grau[v])
				q.push(v);
		}
	}
	return (qtd == sz(cc));
}

int main(){
	int n, m, ans = 0;
	scanf("%d %d", &n, &m);
	rep(i,0,m) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		grau[v]++;
		g2[u].pb(v);
		g2[v].pb(u);
	}
	for(int i = 0; i < n; i++) {
		if(mark[i]) continue;
		vi cc;
		dfs(i, cc);
		ans += sz(cc) - bfs(cc);
	}
	printf("%d\n", ans);
}
