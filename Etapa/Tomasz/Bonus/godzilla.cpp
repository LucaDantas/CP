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
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

bool mark[maxn];
pii edges[maxn];
vector<int> g[maxn], qr;
int comp, sobe[maxn];

struct DSU {
	int pai[maxn], peso[maxn];
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		if(peso[a] < peso[b])
			swap(a, b);
		peso[a] += peso[b];
		pai[b] = a;
		return 1;
	}
} dsu;

void join(int a, int b) {

}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	comp = n;
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), edges[i] = pii(a, b);
	int q; scanf("%d", &q);
	qr.resize(q);
	for(int i = 0; i < q; i++)
		scanf("%d", &qr[i]), --qr[i], mark[qr[i]] = 1;
	for(int i = 0; i < m; i++)
		if(!mark[i]) join(edges[i].ff, edges[i].ss);
	vector<int> ans;
	for(int i = q-1; i >= 0; i--)
		join(edges[qr[i]].ff, edges[qr[i]].ss), ans.pb(comp);
	for(int i = sz(ans)-1; i >= 0; i--)
		printf("%d\n", ans[i]);
}

