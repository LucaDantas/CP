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

vector<int> a;

int solve(int l, int r, int lim, int upper) {
	if(lim+r-l+1 >= upper) {puts("-1"); exit(0);}
	vector<int> lis;
	for(int i = 0; i < r-l+1; i++) {
		if(a[l+i]-i <= lim || a[l+i]+r-l-i >= upper) continue;
		auto it = upper_bound(all(lis), a[l+i]-i);
		if(it == lis.end())
			lis.pb(a[l+i]-i);
		else *it = a[l+i]-i;
	}
	return r-l+1-sz(lis);
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	a.clear();
	a.resize(n);
	for(int& x : a)
		scanf("%d", &x);
	if(k) {
		vector<int> b(k);
		for(int& x : b)
			scanf("%d", &x), x--;
		for(int i = 1; i < k; i++)
			if(a[b[i]] <= a[b[i-1]])
				{puts("-1"); return 0;}
		int ans = 0;
		if(b[0])
			ans += solve(0, b[0]-1, -inf, a[b[0]]);
		for(int i = 1; i < k; i++)
			if(b[i] != b[i-1]+1)
				ans += solve(b[i-1]+1, b[i]-1, a[b[i-1]], a[b[i]]);
		if(b[k-1] != n-1)
			ans += solve(b[k-1]+1, n-1, a[b[k-1]], inf);
		printf("%d\n", ans);
	}
	else printf("%d\n", solve(0, n-1, -inf, inf));
}
