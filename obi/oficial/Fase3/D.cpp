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
constexpr int maxn = 10;
constexpr int mod = 1000000007;

int dp[1<<maxn][maxn], grid[maxn][maxn];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
	int l, c, p; scanf("%d %d %d", &l, &c, &p);
	for(int i = 0; i < p; i++) {
		int a, b; scanf("%d %d", &a, &b);
		grid[a][b] = 1;
	}
	for(int i = 1; i <= c; i++) {
		for(int next = 0; next < (1 << l); ++next) {
			for(int last = 0; last < (1 << l); ++last) {
				bool ruim = 0;
				for(int b = 1; b < l; b++)
					if(((1<<b)&next) && ((1<<(b-1))&next))
						ruim = 1;
				if((next&last) > 0 || ruim) continue;
				int qtd = 0, lixo = 0;
				for(int b = 1; b <= l; b++) {
					if(!((1<<(b-1))&next)) continue;
					if(grid[b][i]) {
						lixo = 1;
						break;
					}
					bool ok = 0;
					for(int x = 0; x < 4; x++)
						ok |= grid[b+dx[x]][i+dy[x]];
					qtd += ok;
					if(!ok) {lixo = 1; break;}
				}
				if(lixo) continue;
				dp[next][i] = max(dp[next][i], dp[last][i-1] + qtd);
			}
		}
	}
	int ans = 0;
	for(int mask = 0; mask < (1 << l); mask++)
		ans = max(ans, dp[mask][c]);
	printf("%d\n", ans);
}
