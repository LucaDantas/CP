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
constexpr int maxn = 5e5 + 10;
constexpr int mod = 1000000007;

int last, ini;

ll ans = 0;	

int bit[maxn];

void upd(int x, int v) {
	for(x++; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ret = 0;
	for(x++; x > 0; x -= x&-x)
		ret += bit[x];
	return ret;
}

void add(int l, int r) {
	ans += r - l + 1;
	upd(l, 1); upd(r+1, -1);
}

int bs(int x, int i) {
	int l = 0, r = i, best = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(query(m) <= x)
			best = m, r = m-1;
		else l = m+1;
	}
	return best;
}

int main() {
	int n; scanf("%d", &n);
	ll opa = 0;
	for(int i = 0; i < n; i++) {
		char c; scanf(" %c", &c);
		if(c == '0') ini = i+1;
		else {
			int pos = bs(query(ini), i);
			add(pos, i);
		}
		opa += ans;
	}
	printf("%lld\n", opa);
}
