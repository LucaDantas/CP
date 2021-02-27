#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e3 + 10;
constexpr int mod = 1000000007;

int color[maxn], val[maxn][110];

vector<int> comp[maxn], valores[maxn], g[maxn];

int a[maxn][maxn], edge[maxn][maxn], t;

bool mark[maxn], ok = 1;

int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};

void dfs(int u) {
	comp[t].pb(u);
	mark[u] = 1;
	for(int v : g[u]) {
		if(mark[v] && color[v] == color[u]) ok = 0;
		if(mark[v]) continue;
		color[v] = 1-color[u];
		dfs(v);
	}
}

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= k; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		for(int j = x1; j <= x2; j++)
			for(int p = y1; p <= y2; p++)
				a[j][p] = i;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			for(int rep = 0; rep < 8; rep++) {
				int oto = a[i + dx[rep]][j + dy[rep]], eu = a[i][j];
				if(eu && oto && oto != eu && !edge[eu][oto])
					g[oto].pb(eu), g[eu].pb(oto), edge[oto][eu] = edge[eu][oto] = 1;
			}
		}
	}
	for(int i = 1; i <= k; i++)
		if(!mark[i]) dfs(i), ++t;

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			int h; scanf("%d", &h);
			if(a[i][j]) valores[a[i][j]].pb(h);
		}

	for(int i = 1; i <= k; i++) {
		sort(all(valores[i]));
		int suf = 0;
		for(int x : valores[i])
			suf += x;
		int last = 0, ptr = 1, pref = 0, qtd_left = 0, qtd_right = sz(valores[i]);
		valores[i].pb(101);
		for(int x : valores[i]) {
			if(x != last)
				for(; ptr < x; ptr++)
					val[i][ptr] = (qtd_left*ptr - pref) + (suf - qtd_right * ptr);
			++qtd_left;
			--qtd_right;
			suf -= x;
			pref += x;
			last = x;
		}
	}

	int ans = inf;
	for(int h1 = 1; h1 <= 100; h1++) {
		for(int h2 = 1; h2 <= 100; h2++) {
			int here = 0;
			for(int i = 0; i < t; i++) {
				int opa = 0;
				for(int x : comp[i]) {
					if(color[x]) opa += val[x][h1];
					else opa += val[x][h2];
				}

				int opa2 = 0;
				for(int x : comp[i]) {
					if(!color[x]) opa2 += val[x][h1];
					else opa2 += val[x][h2];
				}
				here += min(opa, opa2);
			}
			ans = min(ans, here);
		}
	}
	printf("%d\n", ok?ans:-1);
}
