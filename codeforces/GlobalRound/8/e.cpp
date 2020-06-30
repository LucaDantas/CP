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

const int maxn = 2e5 + 100;

vi top_sort(const vector<vi>& g, vi deg) {
	vi ans;
	queue<int> q;
	rep(i,1,sz(deg)) {
		if(deg[i] == 0)
			q.push(i);
	}

	while(!q.empty()) {
		int u = q.front();
		ans.pb(u);
		q.pop();

		for(auto v : g[u]) {
			deg[v]--;
			if(!deg[v])
				q.push(v);
		}
	}

	return ans;
}

int main(){
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		
		vector<vi> g(n+1);
		vi deg(n+1);
		for(int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			deg[v]++;
		}

		vi ord = top_sort(g, deg), ans;
		vi grp(n+1); // group of each node - starts with zero

		for(auto u : ord) {
			if(grp[u] == 0) {
				for(auto v : g[u])
					if(!grp[v])
						grp[v] = 1;
			}
			else if(grp[u] == 1) {
				for(auto v : g[u])
					grp[v] = 2;
			}
			else ans.pb(u);
		}

		printf("%d\n", sz(ans));
		rep(i,0,sz(ans)) printf("%d%c", ans[i], " \n"[i==sz(ans)-1]);
	}
}
