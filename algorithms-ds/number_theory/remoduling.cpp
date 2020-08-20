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

int m;

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1)
			ans = (int)(1ll * ans * b % m);
		b = (int)(1ll * b * b % m);
		e >>= 1;
	}
	return ans;
}

int n;
vi a;

#define inv(opa) power(opa, m-2)

int cnt(int d) {
	int cnt = 0;
	rep(i,0,n) {
		for(int add = -d; add <= d; add += 2*d) {
			int here = a[i] + add;
			if(here < 0) here += m;
			if(here > m) here -= m;
			if(a[i] > here)
				continue;
			auto it = lower_bound(all(a), here);
			if(it != a.end() && *it == here)
				cnt++;
		}
	}
	return cnt;
}

bool good(int d, int& first) {
	int here = a[0], cnt = 0;
	while(1) {
		auto it = lower_bound(all(a), here);
		if(it == a.end() || here != *it)
			break;
		cnt++;
		here += d;
		if(here > m) here -= m;
	}
	first = a[0];
	here = a[0] - d; if(here < 0) here += m;
	while(1) {
		auto it = lower_bound(all(a), here);
		if(it == a.end() || *it != here)
			break;
		cnt++;
		first = here;
		here -= d;
		if(here < 0) here += m;
	}
	return cnt == n;
}

int main() {
	scanf("%d %d", &m, &n);
	vi c(n); rep(i,0,n) scanf("%d", &c[i]);
	if(n == 1) {printf("%d 0\n", c[0]); return 0;}
	if(n == m) {puts("0 1"); return 0;}
	sort(all(c));
	if(2*n < m) {
		a = c;
		int x = a[1] - a[0];
		int k = n - cnt(x);
		int d = (int)(1ll * x * inv(k) % m);
		int first = -1;
		if(good(d, first)) printf("%d %d\n", first, d);
		else puts("-1");
	} else {
		assert(m < (int)1e6);
		vector<bool> mark(m);
		rep(i,0,n) mark[c[i]] = 1;
		rep(i,0,m) if(!mark[i]) a.pb(i);

		n = m - n;

		if(n == 1) {
			printf("%d %d\n", (a[0] + n) % m, 1);
			return 0;
		}

		int x = a[1] - a[0];
		int k = n - cnt(x);
		int d = (int)(1ll * x * inv(k) % m);
		int first = -1;
		
		if(good(d, first)) printf("%lld %d\n", (1ll*first + 1ll*n*d) % m, d);
		else puts("-1");
	}
}
