#include <bits/stdc++.h>
using namespace std;

#define int long long

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
constexpr int mod = 1000000007;

int32_t main() {
	int t; scanf("%lld", &t);
	while(t--) {
		int n; scanf("%lld", &n);
		vector<int> a(n);
		for(int& x : a)
			scanf("%lld", &x);
		vector<pair<int,int>> hm;
		for(int i = 0; i < n; i++)
			if(!hm.size() || a[i] != hm.back().ff) hm.pb({a[i], 1});
			else hm.back().ss++;
		a.clear();
		for(int i = 0; i < sz(hm); i++)
			a.pb(hm[i].ff);
		int ans = 0;
		for(int i = 0; i < sz(hm); i++) {
			int aq = hm[i].ss, val = hm[i].ff;
			while(1) {
				auto it = lower_bound(all(a), val + (val != hm[i].ff ? val - hm[i].ff : 1));
				if(it == a.end()) break;
				++aq;
				val = *it;
			}
			ans = max(ans, aq);
		}
		printf("%lld\n", n-ans);
	}
}
