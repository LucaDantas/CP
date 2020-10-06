#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pui = pair<uint32_t, int>;
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
#define x first
#define y second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr uint32_t inf = 0x7f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

struct Edge
{
	int x, y, id;
};

vector<pii> g[maxn];

uint32_t dist[maxn];

bool mark[maxn];

void dijkstra(int s) {
	for(int i = 0; i < maxn; i++)
		dist[i] = inf;
	priority_queue<pui, vector<pui>, greater<pui>> q;
	dist[s] = 0;
	q.push({0, s});

	while(q.size()) {
		int u = q.top().y; q.pop();
		if(mark[u]) continue;
		mark[u] = 1;

		for(auto pp : g[u]) {
			int v = pp.x, w = pp.y;
			if(dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				q.push({dist[v], v});
			}
		}
	}
}

int main() {
	int trash, n, cnt = 0; scanf("%d %d", &trash, &n);
	pii s, f; scanf("%d %d %d %d", &s.x, &s.y, &f.x, &f.y);
	vector<Edge> a(n);
	for(auto& it : a)
		scanf("%d %d", &it.x, &it.y), it.id = cnt++;

	g[n].pb({n+1, abs(s.x-f.x) + abs(s.y-f.y)});

	for(int i = 0; i < n; i++) {
		g[n].pb({i, min(abs(s.x-a[i].x), abs(s.y-a[i].y))});
		g[i].pb({n, min(abs(s.x-a[i].x), abs(s.y-a[i].y))});

		g[n+1].pb({i, abs(f.x-a[i].x) + abs(f.y-a[i].y)});
		g[i].pb({n+1, abs(f.x-a[i].x) + abs(f.y-a[i].y)});
	}

	sort(all(a),[](Edge p, Edge q){
		return p.x < q.x;
	});
	for(int i = 1; i < n; i++) {
		g[a[i-1].id].pb({a[i].id, a[i].x - a[i-1].x});
		g[a[i].id].pb({a[i-1].id, a[i].x - a[i-1].x});
	}

	sort(all(a),[](Edge p, Edge q){
		return p.y < q.y;
	});
	for(int i = 1; i < n; i++) {
		g[a[i-1].id].pb({a[i].id, a[i].y - a[i-1].y});
		g[a[i].id].pb({a[i-1].id, a[i].y - a[i-1].y});
	}

	dijkstra(n);
	printf("%d\n", (int)dist[n+1]);
}
