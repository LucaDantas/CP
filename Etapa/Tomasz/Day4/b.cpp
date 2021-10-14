#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

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
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e6 + 10;
constexpr int mod = 1000000007;

struct DSU {
	int pai[maxn], peso[maxn], tam[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	void join(int a, int b) {
		// db(a, b);
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b])
			swap(a, b);
		peso[a] += peso[b];
		pai[b] = a;
		tam[a] += tam[b];
		// if(tam[a] >= mod) tam[a] -= mod;
	}
	int cnt() {
		int ans = 0;
		for(int i = 0; i < maxn; i++)
			if(pai[i] == i && tam[i]) {
				++ans;
			}
		return ans;
	}
	int mx() {
		int ans = 0;
		for(int i = 0; i < maxn; i++)
			ans = max(ans, tam[i]);
		return ans;
	}
} dsu;

int n, m;
char s[maxn];

struct piii {
	int sz, cor, t;
	friend ostream& operator<<(ostream& os, const piii& o) { return os << o.sz << ' ' << o.cor << ' ' << o.t; }
	// bool operator==(const piii& o) const { return sz == o.sz && cor == o.cor && t == o.t; }
};

void add(set<int>& v, int b) {
	auto it = v.lower_bound(b);
	while(it != v.end() && *it == b) ++b, it = v.erase(it);
	v.insert(b);
}

int comp(set<int>& a, set<int>& b) {
	while(a.size() && b.size() && *a.rbegin() == *b.rbegin())
		a.erase(--a.end()), b.erase(--b.end());
	if(!a.size() && !b.size()) return 2; // a == b
	if(!a.size()) return 0; // a < b
	if(!b.size()) return 1; // a > b
	return *a.rbegin() > *b.rbegin();
}

void join(const vector<piii>& a, const vector<piii>& b) {
	static set<int> pos_a, pos_b;
	for(int i = 0, ptr = 0; i < sz(a); i++) {
		while(comp(pos_a, pos_b) == 1 && ptr < sz(b))
			add(pos_b, b[ptr].sz), ++ptr;

		add(pos_a, a[i].sz);
		if(!a[i].cor) continue;
		

		if(comp(pos_a, pos_b) != 1 && b[ptr-1].cor)
		// if(comp(pos_a, pos_b) == 0 && b[ptr-1].cor)
			dsu.join(a[i].t, b[ptr-1].t);

		while(ptr < sz(b) && comp(pos_a, pos_b) == 1) {
			if(b[ptr].cor)
				dsu.join(a[i].t, b[ptr].t);
			add(pos_b, b[ptr].sz);
			++ptr;
		}
	}
	pos_a.clear(), pos_b.clear();
}

void merge(vector<piii>& a, vector<piii>& b) {
	for(auto it : b)
		a.pb(it);
	b.clear();
}

int pot[maxn];

vector<piii> l[maxn], r[maxn], u[maxn], d[maxn];

void init(int pos, int depth) {
	dsu.tam[pos] = s[pos] - '0';
	u[pos] = {{depth, s[pos]-'0', pos}};
	d[pos] = u[pos];
	l[pos] = u[pos];
	r[pos] = u[pos];
}

int solve(int& pos, int depth) {
	int aq = pos;
	++pos;
	if(s[aq] != '4') return init(aq, depth), aq;
	int LU = solve(pos, depth-1);
	int RU = solve(pos, depth-1);
	int LD = solve(pos, depth-1);
	int RD = solve(pos, depth-1);

	{
		join(r[LU], l[RU]); r[LU].clear(), l[RU].clear();
		join(r[LD], l[RD]); r[LD].clear(), l[RD].clear();

		join(u[LD], d[LU]); u[LD].clear(), d[LU].clear();
		join(u[RD], d[RU]); u[RD].clear(), d[RU].clear();

		merge(l[LU], l[LD]); swap(l[aq], l[LU]);
		merge(r[RU], r[RD]); swap(r[aq], r[RU]);
		merge(u[LU], u[RU]); swap(u[aq], u[LU]);
		merge(d[LD], d[RD]); swap(d[aq], d[LD]);
	}

	return aq;
}

int main() {
	pot[0] = 1;
	for(int i = 1; i < maxn; i++)
		pot[i] = 2 * pot[i-1] % mod;
	scanf("%d", &m);
	scanf(" %s", s);
	n = (int)strlen(s);
	int pos = 0;
	solve(pos, m);
	// mx is wrong
	printf("%d\n0\n", dsu.cnt());
}
