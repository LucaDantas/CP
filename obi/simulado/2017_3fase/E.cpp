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
constexpr int maxn = 210;
constexpr int mod = 1000000007;

int dp[maxn][maxn], n;

int a[maxn], pref[maxn], suf[maxn];

int itv(int l, int r) {
	if(l <= r) return pref[r] - (l?pref[l-1]:0);
	return suf[l] + pref[r];
}

int solve(int l, int r) {
	int& ans = dp[l][r];
	if(ans != -1) return ans;
	if(l == r) return 0;
	ans = inf;
	for(int i = l; i != r; i = (i+1)%n)
		ans = min(ans, solve(l, i) + solve((i+1)%n, r) + max(itv(l, i), itv((i+1)%n, r)));
	return ans;
}

int main() {
	double f; scanf("%d %lf", &n, &f);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(int i = 0; i < n; i++)
		pref[i] = a[i] + (i?pref[i-1]:0),
		suf[n-1-i] = a[n-1-i] + suf[n-i];
	int ans = inf;
	clr(dp, -1);
	for(int i = 0; i < n; i++)
		ans = min(ans, solve((i+1)%n, i));
	printf("%.2lf\n", f*ans);
}
