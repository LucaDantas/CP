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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

template<typename T> T rnd(T v) {
  T k;
  k = (T) rng();
  return (T) (((k % v) + v) % v);
}

struct Treap
{
	struct Node
	{
		int pri, val, tam;
		ll soma;
		Node *l, *r;
		Node() {}
		Node(int _val) : pri(rnd(0x3f3f3f3f)), val(_val), tam(1), soma(_val), l(NULL), r(NULL) {}
	} *root;

	Treap() : root(NULL) {}

	int size(Node *node){return node==NULL?0:node->tam;}
	ll sum(Node *node){return node==NULL?0:node->soma;}
	void upd(Node *node){
		if(node == NULL) return;
		node->tam = size(node->l) + size(node->r) + 1;
		node->soma = sum(node->l) + sum(node->r) + node->val;
	}

	void split(Node *node, int v, Node *&a, Node *&b) {
		if(node == NULL) {a = b = NULL; return;}
		if(node->val <= v) {
			split(node->r, v, node->r, b);
			a = node; upd(a);
		} else {
			split(node->l, v, a, node->l);
			b = node; upd(b);
		}
	}

	void remove_last(Node *&node) {
		if(node==NULL) return;
		if(node->r==NULL) {
			node = node->l; return;
		}
		remove_last(node->r);
		upd(node);
	}

	Node* merge(Node* l, Node* r) {
		if(!l || !r) return l?l:r;
		if(l->pri > r->pri) {
			l->r = merge(l->r, r);
			upd(l); return l;
		}
		r->l = merge(l, r->l);
		upd(r); return r;
	}

	void insert(int val) {
		Node *a, *b;
		Node *c = new Node(val);
		split(root, val, a, b);
		
		root = merge(a, c);
		root = merge(root, b);
	}

	void erase(int val) {
		Node *a, *b;
		split(root, val, a, b);
		remove_last(a);
		root = merge(a, b);
	}

	ll massa(int k) {
		return massa(root, k);
	}

	ll massa(Node* node, int k) {
		if(!node) return 0;
		if(size(node->r) < k) {
			return sum(node->r) + node->val + massa(node->l, k - size(node->r) - 1);
		}
		return massa(node->r, k);
	}

	void print() {
		print(root); printf("\n");
	}

	void print(Node* node) {
		if(!node) return;
		print(node->l);
		printf("%d ", node->val);
		print(node->r);
	}
} treap;

int main() {
	multiset<int> a, b;
	int n; scanf("%d", &n);
	ll soma = 0;
	int dob = 0;
	while(n--) {
		int t, val; scanf("%d %d", &t, &val);
		soma += val;
		dob += t * (val > 0? 1 : -1);
		if(t) {
			if(val < 0)
				a.erase(a.find(-val));
			else
				a.insert(val);
		} else {
			if(val < 0)
				b.erase(b.find(-val));
			else
				b.insert(val);
		}
		if(val < 0) {
			treap.erase(-val);
		} else {
			treap.insert(val);
		}

		if(a.empty() && b.empty()) {
			puts("0"); continue;
		}

		ll ans = soma + treap.massa(dob);

		if(b.empty() || *b.rbegin() < *a.begin()) {
			ans -= *a.begin();
			if(!b.empty()) ans += *b.rbegin();
		}

		printf("%lld\n", ans);
	}
}
