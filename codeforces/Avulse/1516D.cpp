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
constexpr int logn = 20;
constexpr int mod = 1000000007;

vector<int> pr;

int f[maxn];

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) f[i] = i, pr.pb(i);
		for(int j = 0; j < sz(pr) && pr[j] <= f[i] && 1ll * i * pr[j] < maxn; j++)
			f[i * pr[j]] = pr[j];
	}
}

vector<int> dd(int x) {
	vector<int> ans;
	while(x > 1) {
		ans.pb(f[x]);
		x /= f[x];
	}
	return ans;
}

int a[maxn], cnt[maxn], pai[maxn][logn];

bool valid(int x) {
	vector<int> d = dd(x);
	for(int k : d)
		if(cnt[k]) return 0;
	return 1;
}

void add(int x) {
	vector<int> d = dd(x);
	for(int k : d)
		++cnt[k];
}

void rmv(int x) {
	vector<int> d = dd(x);
	for(int k : d)
		--cnt[k];
}

int main() {
	sieve();
	int n, Q; scanf("%d %d", &n, &Q);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		vector<int> d = dd(a[i]);
	}
	for(int i = 1, ptr = 1; i <= n; i++) {
		for(; ptr <= n && valid(a[ptr]); ptr++)
			add(a[ptr]);
		rmv(a[i]);
		pai[i][0] = ptr;
		// printf("%d %d\n", i, pai[i][0]);
	}
	for(int l = 1; l < logn; l++)
		for(int i = 1; i <= n; i++)
			pai[i][l] = pai[pai[i][l-1]][l-1];
	while(Q--) {
		int L, R; scanf("%d %d", &L, &R);
		int ans = 0;
		for(int l = logn-1; l >= 0; l--)
			if(pai[L][l] <= R && pai[L][l]) ans += (1 << l), L = pai[L][l];
		printf("%d\n", ans + 1);
	}
}
