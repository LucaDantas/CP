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

void SOLVE() {
	int n, m; cin >> n >> m;
	vector<pii> p(m+1);
	rep(i,1,m+1) {
		int a, b; cin >> a >> b;
		p[i] = {a, b};
	}
	sort(p.begin()+1, p.end(), greater<pii>());
	vector<ll> pref(m+1);
	rep(i,1,m+1) pref[i] = pref[i-1] + p[i].ff;
	p[0].ff = inf;

	ll ans = pref[min(m, n)];
	rep(i,1,m+1) {
		int l = 1, r = m, best = 0;
		while(l <= r) {
			int mid = (l+r) >> 1;
			
			if(p[mid].ff > p[i].ss)
				best = mid, l = mid+1;
			else
				r = mid-1;
		}
		if(best >= n) continue;
		ll here;
		if(best >= i) here = pref[best] + 1ll * (n - best) * p[i].ss;
		else here = pref[best] + p[i].ff + 1ll * (n - best - 1) * p[i].ss;

		ans = max(ans, here);
	}

	cout << ans << '\n';
}

int main() {
	fast;
	int t; cin >> t;
	while(t--) SOLVE();
}
