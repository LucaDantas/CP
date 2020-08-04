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
void debug() { cerr << '\n'; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
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

void min_self(ll& a, ll b) {
	a = min(a, b);
}

struct Matrix
{
	vector<vector<ll>> mat;

	Matrix(int n) : mat(n, vector<ll>(n, inf)) {}

	Matrix() {}

	Matrix& operator*(const Matrix& a) {
		int n = sz(mat);

		static Matrix c;
		c.mat.assign(n, vector<ll>(n, inf));
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < n; k++)
					min_self(c.mat[i][j], mat[i][k] + a.mat[k][j]);

		return c;
	}

	friend ostream& operator<<(ostream &os, const Matrix& v) { 
		int n = sz(v.mat), m = sz(v.mat[0]);
		for(int i = 0; i < n; i++) {
			os << '['; string sep = "";
			for(int j = 0; j < m; j++) {
				os << sep << v.mat[i][j], sep = ", ";
			}
			os << "]\n";
		}
		return os;
	}
};

Matrix power(Matrix b, int e) {
	Matrix ans = b;

	while(e) {
		if(e&1)
			ans = ans * b;
		b = b * b;
		e >>= 1;
	}

	return ans;
}

ll min(Matrix a) {
	ll ans = inf;
	for(auto i : a.mat)
		for(auto j : i)
			min_self(ans, j);
	return ans;
}

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	Matrix base(n);
	while(m--) {
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		base.mat[a-1][b-1] = c;
	}
	ll ans = min(power(base, k-1));
	if(ans >= 4e18l) puts("IMPOSSIBLE");
	else printf("%lld\n", ans);
}
