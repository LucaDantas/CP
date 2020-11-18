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

vector<array<int,6>> resp;

void solve(int i, int j, vector<vector<int>>& a) {
	vector<pii> on, off;
	for(int x : {i, i+1})
		for(int y : {j, j+1})
			if(a[x][y])
				on.pb({x+1, y+1});
			else off.pb({x+1, y+1});
	if(!sz(on)) return;
	if(sz(on) == 4) {
		resp.pb({i+1, j+1, i+1, j+2, i+2, j+1});
		a[i][j] = a[i+1][j] = a[i][j+1] = 0;
		solve(i, j, a);
	} else if(sz(on) == 3) {
		int ptr = 0;
		array<int,6> col;
		for(pii opa : on) {
			a[opa.ff-1][opa.ss-1] ^= 1;
			col[ptr] = opa.ff, col[ptr+1] = opa.ss;
			ptr += 2;
		}
		resp.pb(col);
	} else if(sz(on) == 2) {
		int ptr = 2;
		array<int,6> col;
		col[0] = on[0].ff, col[1] = on[0].ss;
		a[on[0].ff-1][on[0].ss-1] ^= 1;
		for(pii opa : off) {
			a[opa.ff-1][opa.ss-1] ^= 1;
			col[ptr] = opa.ff, col[ptr+1] = opa.ss;
			ptr += 2;
		}
		resp.pb(col);
		solve(i, j, a);
	} else {
		int ptr = 2;
		array<int,6> col;
		col[0] = on[0].ff, col[1] = on[0].ss;
		a[on[0].ff-1][on[0].ss-1] ^= 1;

		int cnt = 0;
		for(pii opa : off) {
			a[opa.ff-1][opa.ss-1] ^= 1;
			col[ptr] = opa.ff, col[ptr+1] = opa.ss;
			ptr += 2;
			if(++cnt == 2) break;
		}
		resp.pb(col);
		solve(i, j, a);
	}
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		resp.clear();
		int n, m; scanf("%d %d", &n, &m);
		bool ok = 1;
		if(n < m)
			ok = 0;
		vector<vector<int>> a(n, vector<int>(m));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				char c; scanf(" %c", &c);
				a[i][j] = c-'0';
			}
		}
		if(!ok) {
			vector<vector<int>> b(m, vector<int>(n));
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					b[j][i] = a[i][j];
				}
			}
			a.assign(m, vector<int>(n));
			swap(n, m);
			a = b;
		}
		if(n == 2 && m == 2) {
			solve(0, 0, a);
				printf("%d\n", sz(resp));
			for(auto x : resp) {
				for(int y : x)
					printf("%d ", y);
				printf("\n");
			}
			continue;
		}

		for(int i = 0; i < n-1; i++) {
			for(int j = 0; j < m-1; j += (j<m-3||(m%2)==0?2:1)) {
				if(a[i][j] || a[i][j+1]) {
					array<int,6> ans; int ptr = 0;
					if(a[i][j])
						ans[0] = i+1, ans[1] = j+1, ptr = 2, a[i][j] ^= 1;
					if(a[i][j+1])
						ans[ptr] = i+1, ans[ptr+1] = j+2, ptr += 2, a[i][j+1] ^= 1;
					ans[ptr] = i+2, ans[ptr+1] = j+1, ptr += 2, a[i+1][j] ^= 1;
					if(ptr < 6)
						ans[ptr] = i+2, ans[ptr+1] = j+2, ptr += 2, a[i+1][j+1] ^= 1;
					resp.pb(ans);
				}
			}
		}
		for(int j = 0; j < m-2; j++) {
			if(a[n-1][j]) {
				resp.pb({n-1, j+1, n-1, j+2, n, j+1});
				resp.pb({n-1, j+1, n-1, j+2, n, j+2});
				a[n-1][j] = 0;
				a[n-1][j+1] ^= 1;
			}
		}
		solve(n-2, m-2, a);
		printf("%d\n", sz(resp));
		if(ok) {
			for(auto x : resp) {
				for(int y : x)
					printf("%d ", y);
				printf("\n");
			}
		} else {
			for(auto x : resp) {
				printf("%d %d %d %d %d %d\n", x[1], x[0], x[3], x[2], x[5], x[4]);
			}
		}
	}
}
