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
constexpr int maxn = 1e6 + 10;
constexpr int mod = 1000000007;

int par[maxn], cost[maxn], cima[maxn], baixo[maxn];

int main() {
	fast;
	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n, vi(m));
	rep(i,0,n) {
		string s;
		cin >> s;
		rep(j,0,m) grid[i][j] = s[j]-'0';
	}

	if(min(n, m) >= 4) {cout << "-1\n"; return 0;}
	// so it'll be either a long row or a long column with size <= 3
	if(min(n, m) == 1) {cout << "0\n"; return 0;}

	if(min(m, n) == 2) {
		if(n < m) {
			rep(j,0,m) {
				rep(i,0,n) par[j] += grid[i][j];
				par[j] %= 2;
			}
		} else {
			rep(i,0,n) {
				rep(j,0,m) par[i] += grid[i][j];
				par[i] %= 2;
			}
		}

		int a1 = 0, a2 = 0, mx = max(m, n);
		rep(i,0,mx) {
			if(i%2) {
				a1 += (par[i] == 1);
				a2 += (par[i] == 0);
			} else {
				a2 += (par[i] == 1);
				a1 += (par[i] == 0);
			}
		}
		cout << min(a1, a2) << '\n';

		return 0;
	}

	if(n < m) {
		rep(j,0,m) {
			cima[j] = (grid[0][j] + grid[1][j])%2;
			baixo[j] = (grid[2][j] + grid[1][j])%2;
		}
	} else {
		rep(i,0,n) {
			cima[i] = (grid[i][0] + grid[i][1])%2;
			baixo[i] = (grid[i][2] + grid[i][1])%2;
		}
	}

	int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
	rep(i,0,max(m, n)) {
		if(i%2) {
			a1 += min(1, (cima[i]==0) + (baixo[i] == 0));
			a2 += min(1, (cima[i]==1) + (baixo[i] == 0));
			a3 += min(1, (cima[i]==0) + (baixo[i] == 1));
			a4 += min(1, (cima[i]==1) + (baixo[i] == 1));
		} else {
			a1 += min(1, (cima[i]==1) + (baixo[i] == 1));
			a2 += min(1, (cima[i]==0) + (baixo[i] == 1));
			a3 += min(1, (cima[i]==1) + (baixo[i] == 0));
			a4 += min(1, (cima[i]==0) + (baixo[i] == 0));
		}
	}
	cout << min({a1, a2, a3, a4}) << '\n';
}
