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
constexpr int maxn = 3e5 + 10;
constexpr int mod = 1000000007;

int sum[maxn], dif[maxn];
char s[maxn];

int V(char c) { if(c == '+') return 1; return -1; }

int itv(int l, int r) { return sum[r] - sum[l-1]; }

struct MergeSortTree {
	// vector para cada nó da árvore
	vector<pii> tree[4*maxn];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[node].push_back({dif[l], l});
			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		int a = 2*node, b = 2*node+1;

		// a função merge() junta dois vectors em um só, deixando o vector final ordenado
		// para mais informações sobre esta funçao, confira a referência do C++
		merge(tree[a].begin(), tree[a].end(), tree[b].begin(), tree[b].end(), back_inserter(tree[node]));
	}

	int query(int node, int l, int r, int a, int b, int x)
	{
		// estamos fora do intervalo
		if (l > b || r < a) return -1;

		// tree[node].end() aponta após a ultima posição do vector
		// logo, se subtrairmos deste ponteiro o primeiro iterador > x no vector, 
		// encontraremos a resposta para este nó
		if (l >= a && r <= b) {
			auto it = lower_bound(all(tree[node]), pii(x, 0));
			if(it != tree[node].end() && it->first == x)
				return it->second;
			return -1;
		}

		int mid = (l+r)>>1;

		// fazemos a recursão para os filhos do nó
		return max(query(2*node, l, mid, a, b, x),query(2*node+1, mid+1, r, a, b, x));
	}
} seg;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, q; scanf("%d %d", &n, &q);
		scanf(" %s", s);
		
		for(int i = 1; i <= n; i++) {
			sum[i] = sum[i-1] + V(s[i-1]) * ((i&1) ? -1 : 1);
		}
		
		for(int i = 1; i <= n; i++)
			dif[i] = itv(i+1, n)-itv(1, i-1);
				// , db(i, sum[i], dif[i]);

		seg.build(1, 1, n);

		for(int tt = 0; tt < q; tt++) {
			int l, r, val; scanf("%d %d", &l, &r);
			val = itv(l, r);
			
			if(val == 0) { puts("0"); continue; }
			
			printf("%d\n", 1 + (r-l)%2);
			
			if((r-l)%2) printf("%d ", r), --r, val -= V(s[r]) * ((r&1) ? 1 : -1);

			int bota = -itv(r+1, n) + sum[l-1];
			bota = -bota;

			// db(val, bota, l, r);

			printf("%d\n", seg.query(1, 1, n, l, r, bota));
		}

		for(int i = 0; i <= 4*n; i++)
			seg.tree[i].clear();
	}
}
