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
constexpr int mod = 998244353;

struct FenwickTree
{
	int n, BIT[maxn];
	FenwickTree(int _n) {n = _n; for(int i = 0; i <= n; i++) BIT[i] = 0;}
	void upd(int x, int v) {
		for(; x <= n; x += x&-x)
			BIT[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x -= x&-x)
			ans += BIT[x];
		return ans;
	}
	int bs(int x) {
		int pos = 0, val = 0;
		for(int lg = 20; lg >= 0; lg--) {
			if(pos + (1 << lg) > n) continue;
			if(val + BIT[pos+(1 << lg)] < x)
				val += BIT[pos+(1 << lg)], pos += (1 << lg);
		}
		return pos+1;
	}
};

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, k; scanf("%d %d", &n, &k);
		vector<int> a(n+1), b(k+1), pos(n+1), r(k+1), l(k+1);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]), pos[a[i]] = i;
		for(int i = 1; i <= k; i++)
			scanf("%d", &b[i]);
		FenwickTree bit(n);
		for(int i = k; i >= 1; i--) {
			if(!bit.query(pos[b[i]])) l[i] = 1;
			else l[i] = bit.bs(bit.query(pos[b[i]])) + 1;
			r[i] = bit.bs(bit.query(pos[b[i]])+1) - 1;
			bit.upd(pos[b[i]], 1);
		}
		int ans = 1;
		for(int i = 1; i <= k; i++) {
			int here = 0;
			if(l[i] != pos[b[i]]) here++;
			if(r[i] != pos[b[i]]) here++;
			// n dá overflow pq here = é no max 2
			ans *= here;
			ans %= mod;
		}
		printf("%d\n", ans);
	}
}
