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

int solve(vector<int>& a) {
	assert(sz(a));
	if(sz(a) == 1)
		return 1;
	vector<int> now;
	set<int> st;
	for(int& x : a)
		if(x)
			st.insert(__builtin_clz(x));
		else st.insert(32);
	int ans = 0;
	for(int i = 0, j = 0, qtd = sz(st)-1; i < sz(a); i = j, qtd--) {
		if(!a[i]) {
			j++;
			continue;
		}
		for(; j < sz(a) && __builtin_clz(a[i]) == __builtin_clz(a[j]); j++)
			now.pb(a[j]-(1 << (31 - __builtin_clz(a[j]))));
		ans = max(ans, (i>0) + solve(now) + qtd);
		now.clear();
	}
	return ans;
}

int main() {
	int n; scanf("%d", &n);
	vector<int> a(n);
	for(int& x : a)
		scanf("%d", &x);
	sort(all(a));
	printf("%d\n", n - solve(a));
}
