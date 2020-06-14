#include <bits/stdc++.h>
using namespace std;

#define int long long

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

const pii pos[] = {{0,1},{1,0},{0,-1},{-1,0}};

int dist(pii a, pii b) {
	return abs(a.ff - b.ff) + abs(a.ss-b.ss);
}

int32_t main(){
	int n, m; cin >> n >> m; // cin e cout por causa de string
	vector<vector<char>> grid(n,vector<char>(m));

	rep(i,0,n) {
		string linha; cin >> linha;
		rep(j,0,m) grid[i][j] = linha[j];
	}

	vector<vector<int>> tempo(n,vector<int>(m, -1)), visit(n,vector<int>(m, -1));
	pii start;

	queue<pii> q;

	rep(i,0,n) rep(j,0,m) {
		if(grid[i][j] == 'O')
			tempo[i][j] = 0, q.push(mp(i,j));
		if(grid[i][j] == 'P')
			tempo[i][j] = 0;
		if(grid[i][j] == 'C')
			visit[i][j] = 0, start = mp(i,j);
	}

	// BFS

	while(!q.empty()) {
		pii u = q.front();
		q.pop();

		allin(it, pos) {
			pii nxt = mp(u.ff + it.ff, u.ss + it.ss);
			if(nxt.ff < 0 || nxt.ff >= n || nxt.ss < 0 || nxt.ss >= m || tempo[nxt.ff][nxt.ss] >= 0) continue;
			tempo[nxt.ff][nxt.ss] = tempo[u.ff][u.ss]+1;
			q.push(nxt);
		}
	}

	// queue is empty now, ans we do another bfs but now from start [aka C]

	q.push(start);

	while(!q.empty()) {
		pii u = q.front();
		q.pop();

		allin(it, pos) {
			pii nxt = mp(u.ff + it.ff, u.ss + it.ss);
			if(nxt.ff < 0 || nxt.ff >= n || nxt.ss < 0 || nxt.ss >= m || 
				visit[nxt.ff][nxt.ss] >= 0 || visit[u.ff][u.ss] >= tempo[nxt.ff][nxt.ss]) continue;
			if(visit[u.ff][u.ss]+1 != dist(start, nxt)) continue;
			visit[nxt.ff][nxt.ss] = visit[u.ff][u.ss]+1;
			q.push(nxt);
		}
	}
	int ans = 0;
	rep(i,0,n) rep(j,0,m) ans = max(ans, visit[i][j]);
	printf("%lld\n", ans+1);
	// rep(i,0,n) rep(j,0,m) printf("%d%c", visit[i][j], " \n"[j==m-1]);
}
