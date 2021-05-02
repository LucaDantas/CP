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
constexpr int maxn = 3e5 + 10;
constexpr int mod = 1000000007;

int cnt[maxn];

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, L, R; scanf("%d %d %d", &n, &L, &R);
		for(int i = 1; i <= n; i++) cnt[i] = 0;
		for(int i = 0, x; i < L; i++)
			scanf("%d", &x), --cnt[x];
		for(int i = 0, x; i < R; i++)
			scanf("%d", &x), ++cnt[x];
		int l = 0, r = 0;
		for(int i = 1; i <= n; i++)
			if(cnt[i] < 0) l -= cnt[i];
			else r += cnt[i];
		int ans = min(l, r), safe = ans;
		if(l > r)
			for(int i = 1; i <= n; i++)
				if(cnt[i] < 0) cnt[i] *= -1;
				else cnt[i] = 0;
		else 
			for(int i = 1; i <= n; i++)
				if(cnt[i] < 0) cnt[i] = 0;
		int opa = 0, tot = 0;
		for(int i = 1; i <= n; i++)
			tot += cnt[i] - (cnt[i]&1), opa += (cnt[i]&1);
		// db(tot, opa, safe);
		int gld = opa;
		opa -= min(opa, safe);
		safe -= min(gld, safe);
		// db(tot, opa, safe, '\n');
		tot -= min(safe, tot);
		printf("%d\n", ans+opa+tot/2);
	}
}
