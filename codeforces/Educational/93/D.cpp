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
constexpr int maxn = 210;
constexpr int mod = 1000000007;

int r, g, h;
vi a, b, c;

ll dp[maxn][maxn][maxn];

ll solve(int A, int B, int C) {
	if(dp[A][B][C] != -1) return dp[A][B][C];
	int fim = (A == r) + (B == g) + (C == h);
	if(fim >= 2) return 0;
	ll& here = dp[A][B][C];
	here = 0;
	if(B != g && C != h)
		here = max(here, (solve(A, B+1, C+1) + 1ll*b[B]*c[C]));
	if(A != r && C != h)
		here = max(here, (solve(A+1, B, C+1) + 1ll*a[A]*c[C]));
	if(A != r && B != g)
		here = max(here, (solve(A+1, B+1, C) + 1ll*a[A]*b[B]));
	return here;
}

int main() {
	scanf("%d %d %d", &r, &g, &h);
	a.resize(r), b.resize(g), c.resize(h);
	rep(i,0,r) {int v; scanf("%d", &v); a[i] = v;}
	rep(i,0,g) {int v; scanf("%d", &v); b[i] = v;}
	rep(i,0,h) {int v; scanf("%d", &v); c[i] = v;}
	sort(all(a), greater<int>());
	sort(all(b), greater<int>());
	sort(all(c), greater<int>());
	clr(dp, -1);
	printf("%lld\n", solve(0, 0, 0));
}
