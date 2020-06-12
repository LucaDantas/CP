#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
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
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 2e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int a[maxn];
ll tree[4*maxn], lazy[4*maxn];

void build(int node, int i, int j) {
	if(i == j) tree[node] = a[i];
	else {
		int m = (i+j) >> 1;
		build(2*node, i, m);
		build(2*node+1, m+1, j);
		tree[node] = min(tree[2*node], tree[2*node+1]);
	}
}

void flush(int node, int i, int j) {
	if(!lazy[node]) return;
	if(i != j) {
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}
	tree[node] += lazy[node];
	lazy[node] = 0;
}

void update(int node, int i, int j, int l, int r, int val) {
	flush(node, i, j);
	if(i > r || j < l) return;
	if(i >= l && j <= r) lazy[node] += val, flush(node, i, j); // Need to flush for the parent to see
	else {
		int m = (i+j) >> 1;
		update(2*node, i, m, l, r, val);
		update(2*node+1, m+1, j, l, r, val);
		tree[node] = min(tree[2*node], tree[2*node+1]);
	}
}

ll query(int node, int i, int j, int l, int r) {
	flush(node, i, j);
	if(i > r || j < l) return inf;
	if(i >= l && j <= r) return tree[node];
	int m = (i+j) >> 1;
	return min(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
}

int main(){
	int n, q;
	scanf("%d", &n);
	read(a,1,n+1);
	build(1,1,n);
	scanf("%d", &q);
	while(q--) {
		int l ,r; scanf("%d %d", &l, &r); l++, r++;
		if(cin.peek() == '\n') {
			if(l <= r) cout << query(1,1,n,l,r) << '\n';
			else cout << min(query(1,1,n,l,n), query(1,1,n,1,r)) << '\n';
		}
		else {
			int val; scanf("%d", &val);
			if(l <= r) update(1,1,n,l,r,val);
			else update(1,1,n,1,r,val), update(1,1,n,l,n,val);
		}
	}
}
