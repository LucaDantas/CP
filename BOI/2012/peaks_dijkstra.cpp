#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it); cerr << '\n';}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
#else
#define db(...)
#endif

#define pb push_back
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 2e3 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int n, m, aux = 0;
vector<pii> peaks;
pair<int, int> ord[MAXN*MAXN];
int h[MAXN][MAXN];
bool seen[MAXN][MAXN];

const pii pos[] = {{0,1}, {1,0}, {1,1}, {0,-1}, {-1,0}, {-1,-1}, {1, -1}, {-1, 1}};

int dijkstra(int sX, int sY) {
	priority_queue<pair<int, pii>> q; // Saves the greatest smallest value and the x,y pos
	q.push({h[sX][sY], {sX, sY}});

	int start = h[sX][sY];

	vector<vi> dist(n, vi(m));

	while(q.size()) {
		int val = q.top().ff;
		int x = q.top().ss.ff, y = q.top().ss.ss;
		dist[x][y] = val;
		q.pop();

		if(h[x][y] > start) return val;

		for(auto nxt : pos) {
			int i = x + nxt.ff, j = y + nxt.ss;
			if(i >= n || i < 0 || j >= m || j < 0) continue;
			if(min(val, h[i][j]) > dist[i][j]) {
				dist[i][j] = min(val, h[i][j]);
				q.push({min(val, h[i][j]),{i, j}});
			}
		}
	}
	return 0;
}

void dfs(int x, int y) {
	seen[x][y] = 1;
	for(auto nxt : pos) {
		int i = x + nxt.ff, j = y + nxt.ss;
		if(i >= n || i < 0 || j >= m || j < 0 || h[i][j] > h[x][y] || seen[i][j]) continue;
		dfs(i,j);
	}
}

int main() {
	scanf("%d %d", &n, &m);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%d", &h[i][j]);
			ord[aux++] = make_pair(i,j);
		}
	}

	sort(ord, ord+aux, [](const pii& a, const pii& b){
		return h[a.ff][a.ss] > h[b.ff][b.ss];
	});

	for(auto now : ord) {
		int x = now.ff, y = now.ss;
		if(!seen[x][y]) {
			peaks.pb({x,y});
			dfs(x,y);
		}
	}

	clr(seen, 0);

	vector<pii> ans;

	for(auto it : peaks) {
		int i = it.ff, j = it.ss;
		ans.pb({h[i][j], dijkstra(i,j)});
	}

	sort(all(ans), greater<pii>());

	printf("%d\n", sz(ans));
	for(auto it : ans) {
		printf("%d %d\n", it.ff, it.ss);
	}
}
