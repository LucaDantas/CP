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
constexpr int mod = 1000000007;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T> T rnd(T v) {
	return (T) (rng() % v);
}

struct Treap {
	struct Node {
		int alt, pri, maior, tam;
		Node *l, *r;
		Node() {}
		Node(int v) : alt(v), pri(rnd(inf)), maior(v), tam(1), l(NULL), r(NULL) {}
	} *root;

	Treap() : root(NULL) {}

	int size(Node *node) {return node==NULL?0:node->tam;}
	int mx(Node *node) {return node==NULL?0:node->maior;}
	void upd(Node *node) {
		if(node) {
			node->tam = size(node->l) + size(node->r) + 1;
			node->maior = max({node->alt, mx(node->l), mx(node->r)});
		}
	}

	void split(Node* node, int pos, Node *&a, Node *&b) {
		if(node==NULL) {a = b = NULL; return;}
		if(size(node->l) < pos) {
			split(node->r, pos - size(node->l) - 1, node->r, b);
			a = node; upd(a);
		} else {
			split(node->l, pos, a, node->l);
			b = node; upd(b);
		}
	}

	Node* merge(Node* l, Node* r) {
		if(!l || !r) return l==NULL?r:l;
		if(l->pri >= r->pri) {
			l->r = merge(l->r, r);
			upd(l); return l;
		}
		r->l = merge(l, r->l);
		upd(r); return r;
	}

	void insert(int val, int pos) {
		Node *a, *b;
		Node *c = new Node(val);
		split(root, pos, a, b);
		root = merge(a, c);
		root = merge(root, b);
	}

	int ultimo(Node* node) {
		return node->r==NULL?node->alt:ultimo(node->r);
	}

	int top(Node *node, int val) {
		if(mx(node->r) <= val) {
			if(node->alt > val) return size(node->l)+1;

			assert(node->l);
			return top(node->l, val);
		}
		return size(node->l) + 1 + top(node->r, val);
	}

	int query(int l, int d) {
		Node *a, *b;
		
		split(root, l, a, b);

		if(size(a) <= 1) {
			root = merge(a, b);
			return 0;
		}

		int ult = ultimo(a);

		if(mx(a) <= d + ult) {
			root = merge(a, b);
			return 0;
		}

		int ans =  top(a, d + ult);
		root = merge(a, b);
		return ans;
	}

} treap;

int main() {
	fast;
	int n; cin >> n;
	rep(i,0,n) {
		int v; cin >> v;
		treap.insert(v, i);
	}

	int q; cin >> q;
	while(q--) {
		int a, b, op; cin >> op >> a >> b;

		if(op == 0) treap.insert(b, a);
		else cout << treap.query(a, b) << '\n';
	}
}
