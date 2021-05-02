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
constexpr int maxn = 2000 * 100 + 1;
constexpr int mod = 1000000007;

std::mt19937 rng(random_device{}());

bool possible(const vector<int>& val) {
	vector<int> dp(maxn);
	dp[0] = 1;
	int sum = 0;
	for(int x : val) {
		sum += x;
		for(int i = maxn-1 - x; i >= 0; i--)
			dp[i + x] |= dp[i];
	}
	return ((sum&1) == 0) && dp[sum >> 1];
}

int main() {
	int n; scanf("%d", &n);
	vector<int> a(n);
	for(int& x : a)
		scanf("%d", &x);
	if(!possible(a)) return puts("0"), 0;
	for(int b = 0; b < 20; b++)
		for(int i = 0; i < n; i++)
			if(a[i] & (1 << b)) return printf("1\n%d\n", i+1), 0;
	// vector<int> ind(n);
	// iota(all(ind), 0);
	// shuffle(all(ind), rng);
	// for(int i = 0; i < n; i++) {
	// 	vector<int> v = a;
	// 	v.erase(v.begin() + ind[i]);
	// 	if(!possible(v)) return printf("1\n%d\n", ind[i]+1), 0;
	// }
}
