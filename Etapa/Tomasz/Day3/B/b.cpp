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

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int n, l, k, d;
set<int> st;

ll ve(set<int>::iterator it) {
	if(it == st.begin()) return calc_so(*it);
	return calc_junto(*it - *prev(it)) + ve(prev(it));
}

ll vd(set<int>::iterator it) {
	if(next(it) == st.end()) return calc_so(l - *it);
	return calc_junto(*next(it) - *it) + vd(next(it));
}

ll dpe(set<int>::iterator it) {
	
}

ll calc(set<int>::iterator it) {
	ll val_esq = ve(it), val_dir = vd(it);
	return min(val_esq + dpd(it), val_dir + dpe(it));
}

int main() {
	scanf("%d %d %d %d", &n, &l, &k, &d);
	for(int i = 0, x; i < n; i++)
		scanf("%d", &x), st.insert(x);
	while(d--) {
		int z, u, p; scanf("%d %d %d", &z, &u, &p);
		for(int i = 0, x; i < z; i++)
			scanf("%d", &x), st.insert(x);
		for(int i = 0, x; i < u; i++)
			scanf("%d", &x), st.erase(x);
		ll ans = inf;
		auto it = st.lower_bound(p);
		if(it != st.end()) ans = abs(*it - p) + calc(it);
		if(it != st.begin()) ans = min(ans, abs(*prev(it) - p) + calc(prev(it)));
		printf("%lld\n", ans);
	}
}
