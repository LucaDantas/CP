#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
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
constexpr int MAXN = 1e5 + 10;
constexpr int mod = 1000000007;

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

struct mat {
	vector<vector<int>> m;
	mat(int n) {
		m.resize(n,vector<int>(n));
	}
	mat operator* (const mat& b) {
		int n = sz(m);
		mat c = mat(n);
		rep(i,0,n)
			rep(j,0,n)
				rep(k,0,n)
					add_self(c.m[i][j], 1ll*m[i][k]*b.m[k][j]%mod);
		return c;
	}
};

mat expo(mat a, ll e) {
	int n = sz(a.m);
	mat s = mat(n);
	rep(i,0,n) s.m[i][i] = 1;
	while(e) {
		if(e&1)
			s = s*a;
		a = a*a;
		e >>= 1; 
	}
	return s;
}

int main() {
	int n; ll e; scanf("%d %lld", &n, &e);

	mat a = mat(n);
	rep(i,0,n) rep(j,0,n) scanf("%d", &a.m[i][j]);

	mat c = expo(a,e);

	int ans = 0;
	rep(i,0,n) rep(j,0,n) add_self(ans, c.m[i][j]);
	printf("%d\n", ans);
}
