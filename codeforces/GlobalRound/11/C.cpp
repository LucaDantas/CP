#include <bits/stdc++.h>
using namespace std;
#define int long long
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

struct Pts
{
	int t, x, y;
} pts[maxn];

int dist(Pts a, Pts b) {
	return abs(a.x-b.x) + abs(a.y-b.y);
}

int dp[maxn];

int32_t main() {
	fast;
	
	for(int i = 1; i < maxn; i++)
		dp[i] = -inf;

	int r, n; cin >> r >> n;
	pts[0] = {0, 1, 1};
	
	for(int i = 1; i <= n; i++)
		cin >> pts[i].t >> pts[i].x >> pts[i].y;
	
	int ptr = 0, melhor = -inf;

	for(int i = 1; i <= n; i++) {
		if(dist(pts[i], pts[0]) <= pts[i].t)
			dp[i] = 1;
		for(; ptr < i-2*r; ptr++)
			melhor = max(melhor, dp[ptr]);
		dp[i] = max(dp[i], melhor+1);

		for(int j = ptr+1; j < i; j++) {
			if(dist(pts[i], pts[j]) <= pts[i].t-pts[j].t)
				dp[i] = max(dp[i], dp[j]+1);
		}
	}

	// for(int i = 1; i <= n; i++)
	// 	debug(i, dp[i]);

	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans = max(ans, dp[i]);

	cout << ans << '\n';
}
