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

const int maxn = 1e6 + 100;

vi g[maxn];
int dist[maxn];

void bfs(int s) {
	
	clr(dist, -1);
	dist[s] = 0;
	
	queue<int> q;
	
	q.push(s);
	
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(auto v : g[u]) {
			if(dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
}

int main(){
	int n;
	scanf("%d", &n);
	
	rep(i,0,n) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	
	bfs(1);
	int atual = -1;
	int longe;
	
	rep(i,2,n+1) {
		if(dist[i] > atual)
			atual = dist[i], longe = i;
	}
	
	bfs(longe);
	int ans = -1;
	rep(i,1,n+1) {
		ans = max(ans, dist[i]);
	}
	printf("%d\n", ans);
}
