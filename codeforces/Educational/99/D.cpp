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
constexpr int maxn = 501;
constexpr int mod = 1000000007;

int dp[2][maxn][maxn];
vector<int> a;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, X; scanf("%d %d", &n, &X);
		a.resize(n);
		for(int& v : a)
			scanf("%d", &v);
		for(int j = 0; j <= 500; j++)
			for(int k = 0; k <= 500; k++)
				dp[1][j][k] = 0, dp[0][j][k] = inf;
		for(int i = n-1; i >= 0; i--) {
			for(int last = 0; last <= 500; last++) {
				for(int x = 0; x <= 500; x++) {
					int& ans = dp[0][last][x];
					if(a[i] >= last)
						ans = min(ans, dp[1][a[i]][x]);
					if(a[i] > x && x >= last)
						ans = min(ans, dp[1][x][a[i]] + 1);
				}
			}
			for(int j = 0; j <= 500; j++)
				for(int k = 0; k <= 500; k++)
					swap(dp[0][j][k], dp[1][j][k]), dp[0][j][k] = inf;
		}
		printf("%d\n", dp[1][0][X]<inf?dp[1][0][X]:-1);
	}
}
