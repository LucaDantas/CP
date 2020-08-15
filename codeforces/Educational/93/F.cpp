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
constexpr int maxn = 1e6 + 10;
constexpr int mod = 1000000007;

char s[maxn];

int pref[2][maxn];

struct SegmentTree
{
	int tree[4*maxn], val[maxn];

	void build(int node, int i, int j) {
		if(i == j) {
			tree[node] = val[i];
		} else {
			int m = (i+j) >> 1;
			build(2*node, i, m);
			build(2*node+1, m+1, j);
			tree[node] = max(tree[2*node], tree[2*node+1]);
		}
	}

	int query(int node, int i, int j, int pos, int k) {
		if(j < pos || tree[node] < k) return -1;
		if(i == j) return i;
		int m = (i+j) >> 1;
		int esq = query(2*node, i, m, pos, k);
		if(esq == -1) return query(2*node+1, m+1, j, pos, k);
		return esq;
	}
} seg;

int main() {
	int n; scanf("%d", &n);
	scanf(" %s", s);

	pref[0][0] = (s[0] == '0');
	pref[1][0] = (s[0] == '1');
	rep(i,1,n) {
		pref[0][i] = pref[0][i-1] + (s[i] == '0');
		pref[1][i] = pref[1][i-1] + (s[i] == '1');
	}

	auto intv = [&](const int& a, const int& b, int k) {
		if(a) return pref[k][b] - pref[k][a-1];
		return pref[k][b];
	};
	rep(i,0,n) {
		int l = i, r = n-1, best = -1;
		while(l <= r) {
			int m = (l+r) >> 1;
			if((!intv(i, m, 0)) || (!intv(i, m, 1)))
				best = m, l = m+1;
			else
				r = m-1;
		}
		seg.val[i] = best - i + 1;
	}

	seg.build(1, 0, n-1);

	rep(k,1,n+1) {
		int ans = 0, pos = 0;
		while(1) {
			int qr = seg.query(1, 0, n-1, pos, k);
			if(qr == -1) break;
			ans++;
			pos = qr+k;
		}
		printf("%d ", ans);
	}
	printf("\n");
}