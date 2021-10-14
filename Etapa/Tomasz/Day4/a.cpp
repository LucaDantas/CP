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
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 5e5 + 10, B = 700;
constexpr int mod = 1000000007, p1 = 7, inv_p1 = 142857144;

int tipo(char c) { return c == 'A' ? 0 : c == 'C' ? 1 : c == 'T' ? 2 : 3; }

char s[maxn];
int a[maxn];

int dp[maxn];
int dp1[5010][5010], n;
int cor[4];

void calc() {
	for(int l = 1; l <= n; l++) {
		for(int i = l; i <= n; i++) {
			if(!cor[a[i]]) dp1[l][i] = dp1[l][i-1] + 1;
			else dp1[l][i] = (dp1[l][i-1] - dp1[l][cor[a[i]] - 1] + mod) % mod;
			dp1[l][i] += dp1[l][i-1]; if(dp1[l][i] >= mod) dp1[l][i] -= mod;
			cor[a[i]] = i;
		}
		memset(cor, 0, sizeof cor);
	}
}

int solve(int l, int r) {
	if(n <= 5000) return dp1[l][r];
	for(int i = l-1; i <= r; i++)
		dp[i] = 0;
	
	memset(cor, 0, sizeof cor);
	for(int i = l; i <= r; i++) {
		if(!cor[a[i]]) dp[i] = dp[i-1] + 1;
		else dp[i] = (dp[i-1] - dp[cor[a[i]] - 1] + mod) % mod;
		dp[i] += dp[i-1]; if(dp[i] >= mod) dp[i] -= mod;
		cor[a[i]] = i;
	}
	return dp[r];
}

int main() {
	int q; scanf("%d %d", &n, &q);
	scanf(" %s", s);

	for(int i = 1; i <= n; i++)
		a[i] = tipo(s[i-1]);
	
	if(n <= 5000) calc();

	while(q--) {
		int l, r; scanf("%d %d", &l, &r);
		printf("%d\n", solve(l, r));
	}
}

