#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 2e3 + 10;
constexpr int mod = 1000000007;

int n, m;

int h[MAXN*MAXN];
bool seen[MAXN*MAXN], isPeak[MAXN*MAXN];
int a[MAXN*MAXN];

const int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 1, 0, -1};

int pos(int x, int y) {
	return x*m + y;
}

pii rpos(int v) {
	return make_pair(v/m, v%m);
}

void dfs(int v) {
	seen[v] = 1;
	pii p = rpos(v);
	int x = p.ff, y = p.ss;
	rep(cnt,0,8) {
		int i = x+dx[cnt], j = y+dy[cnt];
		if(i < 0 || i >= n || j < 0 || j >= m || h[pos(i,j)] > h[pos(x,y)]) continue;
		if(!seen[pos(i,j)]) dfs(pos(i,j));
	}
}

int ans[MAXN*MAXN];
int pai[MAXN*MAXN], peso[MAXN*MAXN], mx[MAXN*MAXN];
vector<int> peaks[MAXN*MAXN];

int Find(int x) {
	if(pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void merge(int x, int y, int w) {
	if(mx[x] == mx[y]) {
		for(auto it : peaks[y]) {
			peaks[x].pb(it);
		}
		peaks[y].clear();
	}
	else if(mx[x] > mx[y]) {
		for(auto it : peaks[y]) {
			ans[it] = w;
		}
		peaks[y].clear();
	}
	else {
		for(auto it : peaks[x]) {
			ans[it] = w;
		}
		peaks[x].clear();
		swap(peaks[x], peaks[y]);
	}
}

void Join(int x, int y, int w) {
	x = Find(x);
	y = Find(y);
	if(x == y) return;
	if(peso[x] < peso[y]) swap(x,y);

	merge(x, y, w);

	mx[x] = max(mx[x], mx[y]);
	pai[y] = x;
	peso[x] += peso[y];
}

int main() {
	scanf("%d %d", &n, &m);

	int aux = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++, aux++) {
			scanf("%d", &h[aux]);
			a[aux] = aux;
		}
	}

	sort(a, a+m*n, [](const int& x, const int& y) {
		return h[x] > h[y];
	});

	for(int i = 0; i < m*n; i++) {
		if(!seen[a[i]]) {
			isPeak[a[i]] = 1;
			dfs(a[i]);
		}
	}

	// init the dsu
	aux = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++, aux++) {
			if(isPeak[aux]) {
				peaks[aux].eb(aux);
			}
			pai[aux] = aux;
			mx[aux] = h[aux];
			peso[aux] = 1;
		}
	}

	for(int k = 0; k < n*m; k++) {
		pii p = rpos(a[k]);
		int x = p.ff, y = p.ss;
		rep(cnt,0,8) {
			int i = x+dx[cnt], j = y+dy[cnt];
			if(i < 0 || i >= n || j < 0 || j >= m || h[pos(i,j)] < h[a[k]]) continue;

			Join(a[k], pos(i,j), h[a[k]]);
		}
	}

	vector<pii> vans;
	aux = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++, aux++) {
			if(!isPeak[aux]) continue;
			vans.eb(make_pair(h[aux], ans[aux]));
		}
	}

	sort(all(vans), greater<pii>());
	printf("%d\n", sz(vans));
	for(auto it : vans) {
		printf("%d %d\n", it.ff, it.ss);
	}
}
