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
constexpr int maxn = 5e3 + 10;
constexpr int mod = 1000000007;

long long pref[maxn], dp[maxn][maxn], a[maxn], b[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	for(int i = 1; i <= n; i++) {
		pref[i] = pref[i-1] + a[i] * b[i];
		dp[i][i] = a[i] * b[i];
		dp[i][i+1] = a[i] * b[i+1] + a[i+1] * b[i];
	}
	long long ans = pref[n];
	for(int i = 1; i < n; i++)
		ans = max(ans, pref[n] - pref[i+1] + pref[i-1] + dp[i][i+1]);
	for(int l = n; l >= 1; l--) {
		for(int r = l+2; r <= n; r++) {
			dp[l][r] = dp[l+1][r-1] + a[l] * b[r] + a[r] * b[l];
			ans = max(ans, pref[n] - pref[r] + pref[l-1] + dp[l][r]);
		}
	}
	printf("%lld\n", ans);
}
