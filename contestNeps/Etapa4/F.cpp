#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const multiset<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
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

int val[maxn];

multiset<int> freq;

struct SegmentTree
{
	int tree[4*maxn], lazy[4*maxn];
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = 1);
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = 1;
	}
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;
		if(i != j)
			lazy[2*node+1] = lazy[2*node] = lazy[node];
		tree[node] = lazy[node];
		lazy[node] = 0;
	}
	void upd(int node, int i, int j, int l, int r, int c) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r && tree[node] != -1) {
			if(tree[node] == c) return;
			
			freq.erase(freq.find(val[tree[node]]));
			val[tree[node]] -= j-i+1;
			freq.insert(val[tree[node]]);

			freq.erase(freq.find(val[c]));
			val[c] += j-i+1;
			freq.insert(val[c]);

			lazy[node] = c;
			flush(node, i, j);
		} else {
			int m = (i+j) >> 1;
			upd(2*node, i, m, l, r, c);
			upd(2*node+1, m+1, j, l, r, c);
			tree[node] = (tree[2*node]==tree[2*node+1]?tree[2*node]:-1);
		}
	}
} seg;

int main() {
	int n, q; scanf("%d %d", &n, &q);
	freq.insert(n);
	for(int i = 2; i <= n; i++)
		freq.insert(0);
	val[1] = n;
	seg.build(1, 1, n);
	while(q--) {
		int t; scanf("%d", &t);
		if(t == 1) {
			int l, r, x; scanf("%d %d %d", &l, &r, &x);
			seg.upd(1, 1, n, l, r, x);
		}
		else if(t == 3) printf("%d\n", *freq.rbegin());
		else {
			int x; scanf("%d", &x);
			printf("%d\n", val[x]);
		}
	}
}
