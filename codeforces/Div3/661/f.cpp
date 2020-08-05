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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

void SOLVE() {
	int n; scanf("%d", &n);
	vector<pii> pt(n);
	map<int, int> compress;
	
	rep(i,0,n) {
		int l, r; scanf("%d %d", &l, &r); r++;
		pt[i] = {l, r};
		compress[l], compress[r];
	}
	
	int coord = 0;
	for(auto& it : compress)
		it.ss = coord++;
	rep(i,0,n)
		pt[i] = {compress[pt[i].ff], compress[pt[i].ss]};
	
	sort(all(pt), [](const pii& a, const pii& b){
		return a.ss-a.ff < b.ss-b.ff;
	});

	vector<vector<pii>> st(coord);

	rep(i,0,n)
		st[pt[i].ff].eb(pt[i].ss, i);

	vector<int> dp(coord), val(n);

	rep(i,0,n) {
		int l = pt[i].ff, r = pt[i].ss;
		dp[r] = 0;
		for(int p = r-1; p >= l; p--) {
			dp[p] = dp[p+1];
			for(auto s : st[p])
				if(s.ff <= r) dp[p] = max(dp[p], val[s.ss] + dp[s.ff]);
		}
		val[i] = dp[l]+1;
	}

	dp[coord-1] = 0;
	for(int p = coord-2; p >= 0; p--) {
		dp[p] = dp[p+1];
		for(auto s : st[p])
			dp[p] = max(dp[p], val[s.ss] + dp[s.ff]);
	}
	printf("%d\n", dp[0]);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) SOLVE();
}
