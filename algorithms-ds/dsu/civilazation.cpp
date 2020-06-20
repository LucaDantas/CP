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

const int maxn = 3e5 + 100;

int n;

int pai[maxn], depth[maxn], depth2[maxn];

int find(int x) {
	if(pai[x] == x) return x;
	return pai[x] = find(pai[x]);
}

void join(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(depth[x] < depth[y]) swap(x,y);
	pai[y] = x;
	if(depth[x] == depth[y]) depth2[x] = depth[x]++;
	else depth2[x] = max(depth2[x], depth[y]+1);
}

vi g[maxn];

bool mark[maxn];

int dist[maxn];

int bfs(int s) {
	queue<int> q;
	q.push(s);

	int last;
	while(!q.empty()) {
		int u = q.front();
		mark[u] = 1;
		last = u;
		q.pop();
		for(auto v : g[u]) {
			if(mark[v]) continue;
			q.push(v);
		}
	}
	return last;
}

int bfs2(int s) {
	queue<int> q;
	q.push(s);

	int last;
	while(!q.empty()) {
		int u = q.front();
		last = u;
		q.pop();
		for(auto v : g[u]) {
			if(v == pai[u]) continue;
			dist[v] = dist[u]+1;
			pai[v] = u;
			q.push(v);
		}
	}
	return last;
}

void init() {
	for(int i = 1; i <= n; i++) {
		if(!mark[i]) {
			int last = bfs(i);
			pai[last] = last;
			int other = bfs2(last);
			depth[last] = (dist[other]+1)/2;
			depth2[last] = dist[other]/2;
		}
	}
}

int main(){
	int m, q;
	scanf("%d %d %d", &n, &m, &q);
	rep(i,0,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}
	init();
	while(q--) {
		int t, a, b; scanf("%d %d", &t, &a);
		if(t == 1) {
			printf("%d\n", depth[find(a)] + depth2[find(a)]);
		}
		else {
			scanf("%d", &b);
			join(a,b);
		}
	}
}
