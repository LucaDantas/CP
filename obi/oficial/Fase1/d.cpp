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

const int maxn = 5e4 + 100;

vector<pii> g[maxn]; // pair = {adjacent node, color of the edge}

int ans = -1;

pii dfs(int u, int pai) {
	// Returns a pair containing best path starting from a white edge and for a black edge
	// White - 1 / first, Black - 0 / second
	pii ret = {0,0};
	for(pii nxt : g[u]) {
		int v = nxt.ff, color = nxt.ss;
		if(v == pai) continue;
		if(color) {
			// We get the best black path from the next one
			ret.ff = max(ret.ff, dfs(v, u).ss);
		}
		else {
			// We want the best white path from the next one
			ret.ss = max(ret.ss, dfs(v, u).ff);
		}
		// If the answer is completely contained in this node we update the answer
		// by adding up the best white path and black path + itself
		ans = max(ans, ret.ff + ret.ss + 1);
	}
	// We add one to count itself
	ret.ff++, ret.ss++;
	return ret;
}

int main(){
	int n;
	scanf("%d", &n);
	rep(i,1,n) {
		// We only have n-1 edges, since it's a tree
		int a, b, e;
		scanf("%d %d %d", &a, &b, &e);
		g[a].pb({b,e});
		g[b].pb({a,e});
	}

	dfs(1, -1);

	printf("%d\n", ans);
}
