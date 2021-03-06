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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

int n[4];
vector<int> g[4][maxn];
int cost[4][maxn];
pii dp[4][maxn];

int main() {
	for(int& x : n)
		scanf("%d", &x);
	for(int t = 0; t < 4; t++)
		for(int i = 0; i < n[t]; i++)
			scanf("%d", &cost[t][i]), dp[t][i] = {inf, i};

	for(int t = 0; t < 3; t++) {
		int m; scanf("%d", &m);
		for(int i = 0, u, v; i < m; i++)
			scanf("%d %d", &u, &v), g[t][u-1].pb(v-1);
	}

	for(int i = 0; i < n[3]; i++)
		dp[3][i] = {cost[3][i], i};

	for(int t = 2; t >= 0; t--) {
		for(int i = 0; i < n[t]; i++)
			sort(all(g[t][i]), [&](int a, int b){return dp[t+1][a]>dp[t+1][b];});
		sort(dp[t+1], dp[t+1]+n[t+1]);
		for(int i = 0; i < n[t]; i++) {
			for(int j = 0; j < n[t+1]; j++) {
				if(g[t][i].size() && dp[t+1][j].ss == g[t][i].back()) g[t][i].pop_back();
				else {
					dp[t][i].first = cost[t][i] + dp[t+1][j].first;
					break;
				}
			}
		}
	}
	int best = inf;
	for(int i = 0; i < n[0]; i++)
		best = min(best, dp[0][i].first);
	printf("%d\n", best<inf?best:-1);
}
