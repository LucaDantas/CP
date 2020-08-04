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

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e5 + 10;

struct Matrix
{
	vector<vector<uint32_t>> mat;

	Matrix(int n) : mat(n, vector<uint32_t>(n)) {}

	Matrix() {}

	Matrix& operator*(const Matrix& a) {
		int n = sz(mat);

		static Matrix c;
		c.mat.assign(n, vector<uint32_t>(n));
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < n; k++)
					c.mat[i][j] += mat[i][k] * a.mat[k][j];

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

Matrix power(Matrix b, long long e) {
	int n = sz(b.mat);
	Matrix ans(n);
	rep(i,0,n) ans.mat[i][i] = 1;

	while(e) {
		if(e&1)
			ans = ans * b;
		b = b * b;
		e >>= 1;
	}

	return ans;
}

// where can the knight go ->
// we planify to make it a 64x64 matrix

const int dx[] = {1, -1, 2, -2, 1, -1, 2, -2};
const int dy[] = {2, 2, 1, 1, -2, -2, -1, -1};

int pos(int x, int y) {
	return x + 8*y;
}

int main() {
	fast;
	int k; cin >> k;
	Matrix b(8), a(65);
	rep(x,0,8) {
		rep(y,0,8) {
			rep(i,0,8) {
				int n_x = x + dx[i], n_y = y + dy[i];
				if(n_x < 8 && n_x >= 0 && n_y < 8 && n_y >= 0)
					a.mat[pos(x, y)][pos(n_x, n_y)] = 1;
			}
		}
	}
	rep(i,0,65) a.mat[64][i] = 1;
	
	cout << power(a, k+1).mat[64][0] << '\n';
}
