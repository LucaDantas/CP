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
constexpr int maxn = 20;
constexpr int mod = 1000000007;

int peso[maxn], tempo[maxn], p[1 << 16], t[1 << 16];

int dp[(1 << 16)];

int main() {
	int w, n; scanf("%d %d", &w, &n);
	
	rep(i,0,n)
		scanf("%d %d", &tempo[i], &peso[i]);

	rep(i,1,(1 << n)) dp[i] = inf;

	for(int mask = 0; mask < (1 << n); mask++) {
		for(int i = 0; i < n; i++) {
			if(mask&(1 << i))
				p[mask] += peso[i], t[mask] = max(t[mask], tempo[i]);
		}
	}
	
	for(int mask = 1; mask < (1 << n); mask++) {
		for(int inside = mask; inside > 0; inside = ((inside-1)&mask)) {
			if(p[inside] <= w)
				dp[mask] = min(dp[mask], dp[mask ^ inside] + t[inside]);
		}
	}
	
	printf("%d\n", dp[(1 << n)-1]);
}
