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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

char s[maxn];
// string s;

const char vowel[] = {'A', 'E', 'I', 'O', 'U'};

int mul(int a, int b) {
	return (int)(1ll * a * b % mod);
}

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

struct Node {
	vector<vi> mat;
	Node() {}
	
	void quest() {
		mat = {{19, 6},{7, 20}};
	}
	
	void feliz() {
		mat = {{1, 1},{0, 0}};
	}

	void triste() {
		mat = {{0, 0},{1, 1}};
	}

	void flip() {
		mat = {{0, 1},{1, 0}};
	}

	void nada() {
		mat = {{1, 0},{0, 1}};
	}

	Node& operator*(const Node& a) {
		static Node c;
		int n = sz(a.mat);
		c.mat.assign(n, vi(n));
		rep(i,0,n)
			rep(j,0,n)
				rep(k,0,n)
					add_self(c.mat[i][j], mul(mat[i][k], a.mat[k][j]));
		return c;
	}
} tree[4*maxn];

void build(int node, int i, int j) {
	if(i == j) {
		rep(k,0,5) {
			if(s[i] == vowel[k]) {tree[node].flip(); return;}
		}
		if(s[i] == 'H') {tree[node].feliz(); return;}
		if(s[i] == 'S' || s[i] == 'D') {tree[node].triste(); return;}
		if(s[i] == '?') {tree[node].quest(); return;}
		tree[node].nada(); return;
	}
	int m = (i+j) >> 1;
	build(2*node, i, m); build(2*node+1, m+1, j);

	tree[node] = tree[2*node+1] * tree[2*node];
}

void update(int node, int i, int j, int pos) {
	if(i == j) {
		rep(k,0,5) {
			if(s[i] == vowel[k]) {tree[node].flip(); return;}
		}
		if(s[i] == 'H') {tree[node].feliz(); return;}
		if(s[i] == 'S' || s[i] == 'D') {tree[node].triste(); return;}
		if(s[i] == '?') {tree[node].quest(); return;}
		tree[node].nada(); return;
	}

	int m = (i+j) >> 1;
	if(pos <= m) update(2*node, i, m, pos);
	else update(2*node+1, m+1, j, pos);

	tree[node] = tree[2*node+1] * tree[2*node];
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	scanf(" %s", s);

	build(1,0,n-1);

	printf("%d\n", tree[1].mat[0][0]);

	while(q--) {
		int pos; char val; scanf("%d %c", &pos, &val);
		s[pos-1] = val;
		update(1,0,n-1,pos-1);
		printf("%d\n", tree[1].mat[0][0]);
	}
}