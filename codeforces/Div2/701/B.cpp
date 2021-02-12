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

constexpr int inf = 1e9;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int main() {
	int n, q, k; scanf("%d %d %d", &n, &q, &k);
	vector<long long> a = {0}, ans(n+2), pref(n+2);
	for(int i = 0, v; i < n; i++)
		scanf("%d", &v), a.pb(1ll*v);
	a.pb(k+1);
	for(int i = 1; i <= n; i++)
		ans[i] = a[i+1]-a[i-1]-2, pref[i] = ans[i] + pref[i-1];
		// printf("%d\n", ans[i]);
	while(q--) {
		int l, r; scanf("%d %d", &l, &r);
		if(l == r) printf("%d\n", k-1);
		else printf("%lld\n", max(0ll, pref[r-1]-pref[l]) + k-a[r-1]-1 + a[l+1]-2);
	}
}
