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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int cnt[20];
char s[maxn];

bool isp(int n) {
	if(n == 1) return 0;
	for(int i = 2; i*i <= n; i++)
		if(!(n%i)) return 0;
	return 1;
}

void solve() {
	int n; scanf("%d", &n);
	scanf(" %s", s);
	clr(cnt, 0);
	vector<int> hm;
	for(int i = 0; i < n; i++)
		cnt[s[i]-'0']++, hm.pb(s[i]-'0');
	for(int i = 1; i < 10; i++) {
		if(!isp(i) && cnt[i]) {
			printf("1\n%d\n", i);
			return;
		}
	}
	for(int i = 1; i < 10; i++) {
		if(cnt[i] > 1) {
			printf("2\n%d%d\n", i,i);
			return;
		}
	}
	int ans = inf, tam = inf;
	for(int mask = 1; mask < (1 << (sz(hm))); mask++) {
		int nm = 0;
		for(int i = 0; i < sz(hm); i++) {
			if(!(mask&(1<<i))) continue;
			nm *= 10, nm += hm[i];
		}
		if(!isp(nm)) ans = min(ans, nm), tam = min(tam, __builtin_popcount(mask));
	}
	printf("%d\n%d\n", tam, ans);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) solve();
}
