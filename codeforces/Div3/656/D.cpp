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

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		char s[n+1]; scanf(" %s", s);

		int logn = (int)log2(n);
		vector<vector<int>> dp(n, vi(logn+1));

		auto cnt = [&](const int& l, const int& r, const char& c) {
			int ret = r - l;
			rep(i,l,r) if(s[i] == c) ret--;
			return ret;
		};

		for(int i = n-1; i >= 0; i--) {
			dp[i][0] = (s[i] != 'a'+logn);
			for(int k = 1; k <= logn; k++) {
				if(i % (1 << k)) continue;
				char now = (char)('a'+logn-k);

				int l = cnt(i, i+(1<<(k-1)), now);
				int r = cnt(i+(1<<(k-1)), i+(1<<k), now);

				dp[i][k] = min(dp[i][k-1]+r, dp[i+(1<<(k-1))][k-1]+l);
			}
		}
		printf("%d\n", dp[0][logn]);
	}
}
