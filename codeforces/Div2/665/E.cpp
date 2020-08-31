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
constexpr int maxn = 1e6 + 10;
constexpr int fim = 1e6;
constexpr int mod = 1000000007;

int bit[maxn];

void upd(int x, int v) {
	for(x++; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(x++; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

vector<pii> pt[4];

int main() {
	ll ans = 0;
	int n, m; scanf("%d %d", &n, &m);

	for(int i = 0; i < n; i++) {
		int y, l, r; scanf("%d %d %d", &y, &l, &r);
		ans += (l == 0 && r == fim);
		if(l == 0) pt[2].pb({r, y});
		else pt[3].pb({l, y});
	}

	for(int i = 0; i < m; i++) {
		int x, l, r; scanf("%d %d %d", &x, &l, &r);
		ans += (l == 0 && r == fim);
		if(l == 0) pt[0].pb({x, r});
		else pt[1].pb({x, l});
	}

	sort(all(pt[0]), greater<pii>());
	sort(all(pt[2]), greater<pii>());

	int ptr = 0;
	for(auto p : pt[0]) {
		int x = p.ff, up = p.ss;
		for(; ptr < sz(pt[2]) && x <= pt[2][ptr].ff; ptr++)
			upd(pt[2][ptr].ss, 1);
		ans += query(up);
	}

	clr(bit, 0);
	sort(all(pt[0]));
	sort(all(pt[3]));

	ptr = 0;
	for(auto p : pt[0]) {
		int x = p.ff, up = p.ss;
		for(; ptr < sz(pt[3]) && x >= pt[3][ptr].ff; ptr++)
			upd(pt[3][ptr].ss, 1);
		ans += query(up);
	}

	clr(bit, 0);
	sort(all(pt[1]), greater<pii>());
	sort(all(pt[2]), greater<pii>());

	ptr = 0;
	for(auto p : pt[1]) {
		int x = p.ff, up = p.ss;
		for(; ptr < sz(pt[2]) && x <= pt[2][ptr].ff; ptr++)
			upd(pt[2][ptr].ss, 1);
		ans += query(fim) - query(up-1);
	}

	clr(bit, 0);
	sort(all(pt[1]));
	sort(all(pt[3]));

	ptr = 0;
	for(auto p : pt[1]) {
		int x = p.ff, up = p.ss;
		for(; ptr < sz(pt[3]) && x >= pt[3][ptr].ff; ptr++)
			upd(pt[3][ptr].ss, 1);
		ans += query(fim) - query(up-1);
	}

	printf("%lld\n", ans+1);
}
