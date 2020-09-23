#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using piii = pair<pii, int>;
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
#define x first.first
#define y first.second
#define id second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e3 + 10;
constexpr int mod = 1000000007;

int n;

struct DSU {
	int pai[maxn], peso[maxn], cc;
	DSU() {
		cc = n;
		for(int i = 0; i < n; i++)
			pai[i] = i, peso[i] = 0;
	}
	int find(int a) {
		if(pai[a] == a) return a;
		return pai[a] = find(pai[a]);
	}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		cc--;
		if(peso[a] < peso[b]) swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
	}
};

struct Edge {
	int a, b, w;
	friend ostream& operator<<(ostream& os, Edge e) {
		return os << e.a << ' ' << e.b << ' ' << e.w;
	}
	bool operator==(Edge oto) {
		return a==oto.a && b==oto.b && w==oto.w;
	}
};

vector<Edge> edges;
vector<piii> pt;

bool check(int t) {
	DSU dsu;
	for(auto e : edges)
		if(e.w <= t)
			dsu.join(e.a, e.b);
	if(dsu.cc == 1) {return 1;}
	if(dsu.cc > 4) return 0;
	vector<vector<pii>> pts(dsu.cc);
	map<int, int> mp;
	int aux = 0;
	for(int i = 0; i < n; i++)
		if(!mp[dsu.find(i)])
			mp[dsu.find(i)] = ++aux;
	for(auto& it : mp) it.second--;

	for(int i = 0; i < n; i++)
		pts[mp[dsu.find(i)]].pb({pt[i].x, pt[i].y});
	if(dsu.cc == 2) {
		for(auto a : pts[0]) {
			for(auto b : pts[1]) {
				if(abs(a.first - b.first) <= t && abs(a.second - b.second) <= t)
					return 1;
			}
		}
		for(auto e : edges) {
			if(dsu.find(e.a) != dsu.find(e.b) && e.w <= 2*t) return 1;
		}
		return 0;
	} 
	else if(dsu.cc == 3) {
		for(auto e : edges) {
			if(dsu.find(e.a) == dsu.find(e.b)) continue;
			vector<int> mark(3);
			int use = -1;
			mark[mp[dsu.find(e.a)]] = 1, mark[mp[dsu.find(e.b)]] = 1;
			for(int i = 0; i < 3; i++)
				if(!mark[i]) use = i;
			if(pt[e.a].x == pt[e.b].x) {
				for(auto p : pts[use]) {
					if(abs(p.first - pt[e.a].x) <= t && abs(p.second - pt[e.a].y) <= t
						&& abs(p.second - pt[e.b].y) <= t)
							return 1;
				}
			} else {
				for(auto p : pts[use]) {
					if(abs(p.second - pt[e.a].y) <= t && abs(p.first - pt[e.a].x) <= t
						&& abs(p.first - pt[e.b].x) <= t)
							return 1;
				}
			}
		}
		return 0;
	}
	else {
		for(auto e1 : edges) {
			for(auto e2 : edges) {
				if(e1 == e2) continue;
				vector<int> mark(4);
				mark[mp[dsu.find(e1.a)]] = 1;
				mark[mp[dsu.find(e1.b)]] = 1;
				mark[mp[dsu.find(e2.a)]] = 1;
				mark[mp[dsu.find(e2.b)]] = 1;
				bool ok = 1;
				for(int i = 0; i < 4; i++)
					if(!mark[i]) ok = 0;
				if(!ok) continue;
				pii lixo = {0, 0};
				pii h1 = lixo, h2 = lixo, v1 = lixo, v2 = lixo;
				if(pt[e1.a].x == pt[e1.b].x)
					v1 = {pt[e1.a].x, pt[e1.a].y}, v2 = {pt[e1.b].x, pt[e1.b].y};
				if(pt[e2.a].x == pt[e2.b].x)
					v1 = {pt[e2.a].x, pt[e2.a].y}, v2 = {pt[e2.b].x, pt[e2.b].y};

				if(v1.second > v2.second) swap(v1, v2);

				if(pt[e1.a].y == pt[e1.b].y)
					h1 = {pt[e1.a].x, pt[e1.a].y}, h2 = {pt[e1.b].x, pt[e1.b].y};
				if(pt[e2.a].y == pt[e2.b].y)
					h1 = {pt[e2.a].x, pt[e2.a].y}, h2 = {pt[e2.b].x, pt[e2.b].y};

				if(h1.first > h2.first) swap(h1, h2);
				if((h1==lixo && h2==lixo) || (v1==lixo && v2==lixo)) continue;

				int val = max({abs(h2.first - v1.first), abs(h1.first - v1.first), abs(v1.second - h1.second), abs(v2.second - h1.second)});
				if(val <= t) return 1;
			}
		}
		return 0;
	}
}

int main() {
	scanf("%d", &n);
	pt.resize(n);
	for(int i = 0; i < n; i++)
		scanf("%d %d", &pt[i].x, &pt[i].y), pt[i].id = i;
	
	sort(all(pt));
	for(int i = 1; i < n; i++)
		if(pt[i].x == pt[i-1].x)
			edges.pb({pt[i].id, pt[i-1].id, pt[i].y - pt[i-1].y});

	sort(all(pt), [](piii a, piii b) {
		if(a.y == b.y) return a.x < b.x;
		return a.y < b.y;
	});
	for(int i = 1; i < n; i++)
		if(pt[i].y == pt[i-1].y)
			edges.pb({pt[i].id, pt[i-1].id, pt[i].x - pt[i-1].x});

	sort(all(pt),[](piii a, piii b){return a.id < b.id;});

	int l = 0, r = 2e9+10, ans = -1;
	while(l <= r) {
		int mid = l + ((r-l)>>1);
		if(check(mid))
			ans = mid, r = mid-1;
		else
			l = mid+1;
	}
	printf("%d\n", ans);
}
