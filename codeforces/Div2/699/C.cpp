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

vector<int> grp[maxn];

int find(vector<int>& a, vector<int>& b, int c) {
	int pos = -1;
	for(int i = 0; i < sz(b); i++) {
		if(b[i] == c) {
			if(a[i] == b[i]) pos = i+1;
			else return i+1;
		}
	}
	return pos;
}

void solve() {
	int n, m; scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			grp[i].clear();
		vector<int> a(n), b(n), c(m), ans(m);
		for(int& x : a)
			scanf("%d", &x);
		for(int& x : b)
			scanf("%d", &x);
		for(int& x : c)
			scanf("%d", &x);
		int trash = find(a, b, c.back());
		if(trash == -1) {puts("NO"); return;}
		for(int i = 0; i < n; i++) {
			if(a[i] != b[i] && i+1 != trash)
				grp[b[i]].pb(i+1);
		}
		for(int i = 0; i < m-1; i++) {
			if(grp[c[i]].size()) {
				ans[i] = grp[c[i]].back();
				grp[c[i]].pop_back();
			}
			else ans[i] = trash;
		}
		ans[m-1] = trash;
		bool ok = 1;
		for(int i = 1; i <= n; i++)
			if(grp[i].size()) ok = 0;
		if(!ok) {puts("NO"); return;}
		puts("YES");
		for(int i = 0; i < m; i++)
			printf("%d ", ans[i]);
		printf("\n");
}

int main() {
	int t; scanf("%d", &t);
	while(t--) solve();
}
