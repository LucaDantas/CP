#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin >> v[i];
// #define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%lld", &v[i]);
// #define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 2e5 + 100, inf = 0x7fffffffffffff;

const int bad[] = {0, -inf, inf, inf, 0, 0};

int a[maxn];

// 1 - max
// 2 - min
// 3 - and
// 4 - xor
// 5 - or

int tree[4*maxn][6];

int combine(int x, int y, int k) {
	if(k == 1) return max(x,y);
	if(k == 2) return min(x,y);
	if(k == 3) return x&y;
	if(k == 4) return x^y;
	if(k == 5) return x|y;
	return 0;
}

void build(int node, int i, int j) {
	if(i == j) {
		rep(k,1,6) tree[node][k] = a[i];
		return;
	}
	int m = (i+j) >> 1;
	build(2*node, i, m);
	build(2*node+1, m+1, j);
	rep(k,1,6) tree[node][k] = combine(tree[2*node][k], tree[2*node+1][k], k);
}

// K determines the type of the query:
// 1 - max
// 2 - min
// 3 - and
// 4 - xor
// 5 - or
int query(int node, int i, int j, int l, int r, int k) {
	if(i > r || j < l) return bad[k];
	if(i >= l && j<= r) return tree[node][k];
	int m = (i+j) >> 1;
	return combine(query(2*node, i, m, l, r, k), query(2*node+1, m+1, j, l, r, k),k);
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		rep(k,1,6) tree[node][k] = val;
		return;
	}
	int m = (i+j) >> 1;
	if(pos <= m) update(2*node, i, m, pos, val);
	else update(2*node+1, m+1, j, pos, val);
	rep(k,1,6) tree[node][k] = combine(tree[2*node][k], tree[2*node+1][k], k);
}

int find_min(int node, int i, int j, int l, int r) {
	if(i == j) return i;
	int m = (i+j) >> 1;
	if(query(2*node,i,m,l,r,2) <= query(2*node+1, m+1, j, l, r, 2))
		return find_min(2*node, i, m, l, r);
	else
		return find_min(2*node+1,m+1,j,l,r);
}

int find_max(int node, int i, int j, int l, int r) {
	if(i == j) return i;
	int m = (i+j) >> 1;
	if(query(2*node,i,m,l,r,1) >= query(2*node+1, m+1, j, l, r, 1))
		return find_max(2*node, i, m, l, r);
	else
		return find_max(2*node+1,m+1,j,l,r);
}

int32_t main(){
	FAST;
	int n, q;
	cin >> n >> q;
	// scanf("%lld %lld", &n, &q);
	// scanf("%d %d", &n, &q);
	read(a,1,n+1);
	build(1,1,n);
	while(q--) {
		char type;
		cin >> type;
		int l, r; cin >> l >> r;
		// int l, r; scanf("%lld %lld", &l, &r);
		// int l, r; scanf("%d %d", &l, &r);
		if(type == 'a') {
			int AND = query(1,1,n,l,r,3);
			int MIN = query(1,1,n,l,r,2);
			if(AND == MIN) {
				int pos = find_min(1,1,n,l,r);
				if((query(1,1,n,l,pos-1,3)&query(1,1,n,pos+1,r,3)) == MIN) cout <<  MIN << '\n';
				// if((query(1,1,n,l,pos-1,3)&query(1,1,n,pos+1,r,3)) == MIN) printf("%lld\n", MIN);
				else cout << "-1\n";
				// else printf("-1\n");
			}
			else cout << "-1\n";
			// else printf("-1\n");
		}
		if(type == 'o') {
			int OR = query(1,1,n,l,r,5);
			int MAX = query(1,1,n,l,r,1);
			if(OR == MAX) {
				int pos = find_max(1,1,n,l,r);
				if((query(1,1,n,l,pos-1,5)|query(1,1,n,pos+1,r,5)) == MAX) cout << MAX << '\n';
				// if((query(1,1,n,l,pos-1,5)|query(1,1,n,pos+1,r,5)) == MAX) printf("%lld\n", MAX);
				else cout << "-1\n";
				// else printf("-1\n");
			}
			else cout << "-1\n";
			// else printf("-1\n");
		}
		if(type == 'x') {
			int XOR = query(1,1,n,l,r,4);
			int MAX = query(1,1,n,l,r,1);
			if(XOR == 0) cout << MAX << '\n';
			// if(XOR == 0) printf("%lld\n", MAX);
			else cout << "-1\n";
			// else printf("-1\n");
		}
		if(type == 'u') {
			update(1,1,n,l,r);
		}
	}
}
