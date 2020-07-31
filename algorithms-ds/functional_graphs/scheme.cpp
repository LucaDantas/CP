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
void debug() { cerr << '\n'; }
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

int f[maxn], fam[maxn], mark[maxn], cc;

bool in[maxn];

vi head, sources[maxn];

void dfs(int u) {
	int v = f[u]; in[v] = 1;
	mark[u] = 1;
	if(mark[v] == 1) {
		head.eb(u);
		fam[u] = cc++;
	}
	else if(!mark[v]) {
		dfs(v);
		fam[u] = fam[v];
	}
	else fam[u] = fam[v];
	mark[u] = 2;
}

int main() {
	int n; scanf("%d", &n);
	rep(i,0,n) {
		int nxt; scanf("%d", &nxt);
		f[i] = nxt-1;
	}

	rep(i,0,n) if(!mark[i]) dfs(i);

	int ans = 0;
	rep(i,0,n)
		if(!in[i])
			ans++, sources[fam[i]].eb(i);

	if(cc == 1 && !ans) {
		puts("0"); return 0;
	}

	rep(i,0,cc)
		if(!sz(sources[i]))
			ans++, sources[i].eb(head[i]);

	printf("%d\n", ans);

	rep(i,0,cc) {
		int prox = (i+1)%cc;
		for(auto s : sources[prox])
			printf("%d %d\n", head[i]+1, s+1);
	}
}
