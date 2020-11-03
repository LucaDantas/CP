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

ll fat[20];

inline ll sum(int x) {return 1ll * x * (x+1) / 2;}

int get(int n, ll pos, int l, int r) {
	vector<int> val;
	for(int i = max(1, n-14); i <= n; i++)
		val.pb(i);
	vector<int> ans;
	for(int i = 1; i <= min(n, 15); i++) {
		int qtd = (int)(pos / fat[min(n, 15)-i]);
		ans.pb(val[qtd]); val.erase(val.begin()+qtd);
		pos %= fat[min(n, 15)-i];
	}
	int ret = 0;
	for(int i = l; i <= r; i++)
		ret += ans[i];
	return ret;
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	ll pos = 0;
	fat[0] = 1;
	for(int i = 1; i < 20; i++)
		fat[i] = 1ll*fat[i-1]*i;
	while(q--) {
		int t; scanf("%d", &t);
		if(t==1) {
			int l, r; scanf("%d %d", &l, &r);
			ll ans = sum(min(max(0, n-15), r)) - sum(min(max(0, n-15), l-1));
			if(r > n-15) ans += get(n, pos, max(l-max((n-15),0)-1, 0), r-max((n-15),0)-1);
			printf("%lld\n", ans);
		} else {
			int x; scanf("%d", &x);
			pos += x;
		}
	}
}
