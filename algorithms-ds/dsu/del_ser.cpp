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
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
#else
#define db(...)
#endif

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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

struct DSU {
	int pai[maxn], peso[maxn];
	map<int, int> cor[maxn]; // salva um exemplo de cada cor saindo de um cara
	set<int> out[maxn]; // salva todos os caras que saem de cada familia (update com small to large)

	void init(int n) {
		rep(i,1,n+1) {
			pai[i] = i;
			peso[i] = 1;
		}
	}

	int find(int x) {
		if(pai[x] == x) return x;
		return pai[x] = find(pai[x]);
	}

	void join(int x, int y) {
		x = find(x), y = find(y);
		if(x == y) return;

		if(peso[x] < peso[y]) swap(x, y);
		pai[y] = x;
		peso[x] += peso[y];

		merge(x, y);
	}

	void merge(int a, int b) {
		if(sz(out[a]) < sz(out[b])) {
			for(auto it : out[a])
				out[b].insert(it);
			swap(out[a], out[b]);
		}
		else {
			for(auto it : out[b])
				out[a].insert(it);
		}
	}

	void add(int a, int b, int c) {
		out[find(a)].insert(b);
		out[find(b)].insert(a);

		if(cor[a].count(c))
			join(b, cor[a][c]);
		if(cor[b].count(c))
			join(a, cor[b][c]);

		cor[a][c] = b;
		cor[b][c] = a;
	}

} dsu;

int main() {
	int n, m, trash, q; scanf("%d %d %d %d", &n, &m, &trash, &q);
	dsu.init(n);

	rep(i,0,m) {
		int u, v, c; scanf("%d %d %d", &u, &v, &c);
		dsu.add(u, v, c);
	}

	rep(i,0,q) {
		char t; int u, v; scanf(" %c %d %d", &t, &u, &v);
		if(t == '+') {
			int c; scanf("%d", &c);
			dsu.add(u, v, c);
		}
		else {
			puts((dsu.find(u) == dsu.find(v) || 
				dsu.out[dsu.find(u)].count(v))?"Yes":"No");
		}
	}
}
