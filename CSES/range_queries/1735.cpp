#include <bits/stdc++.h>
using namespace std;

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
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%lld", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 2e5 + 100;

ll a[maxn], tree[4*maxn], lazy[4*maxn][2];

// Lazy 0 is assignment and Lazy 1 is addition

void build(int node, int i, int j) {
	if(i == j) tree[node] = a[i];
	else {
		int m = (i+j) >> 1;
		build(2*node, i, m);
		build(2*node+1, m+1, j);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
}

void flush(int node, int i, int j) {
	if(!lazy[node][0] && !lazy[node][1]) return;
	if(i != j) {
		if(lazy[node][0]) {
			lazy[2*node][1] = lazy[2*node+1][1] = 0;
			lazy[2*node][0] = lazy[2*node+1][0] = lazy[node][0];
		}
		else {
			if(lazy[2*node][0]) lazy[2*node][0] += lazy[node][1];
			else lazy[2*node][1] += lazy[node][1];
			if(lazy[2*node+1][0]) lazy[2*node+1][0] += lazy[node][1];
			else lazy[2*node+1][1] += lazy[node][1];
		}
	}
	if(lazy[node][0]) {
		tree[node] = 1ll*(j-i+1)*lazy[node][0];
		lazy[node][0] = 0;
	}
	else {
		tree[node] += 1ll*(j-i+1)*lazy[node][1];
		lazy[node][1] = 0;
	}
}

void update(int node, int i, int j, int l, int r, int val, int k) {
	flush(node, i, j);
	if(i > r || j < l) return;
	if(i >= l &&  j <= r) {
		if(k == 0) { // assignment
			lazy[node][0] = val;
			lazy[node][1] = 0;
		}
		else { // addition
			if(lazy[node][0]) lazy[node][0] += val;
			else lazy[node][1] += val;
		}
		flush(node, i, j);
	}
	else {
		int m = (i+j) >> 1;
		update(2*node, i, m, l, r, val, k);
		update(2*node+1, m+1, j, l, r, val, k);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
}

ll query(int node, int i, int j, int l, int r) {
	flush(node, i, j);
	if(i > r || j < l) return 0;
	// db(tree[node]);
	if(i >= l && j <= r) return tree[node];
	int m = (i+j) >> 1;
	return query(2*node, i, m, l, r) + query(2*node+1, m+1, j, l, r);
}

int main(){
	int n, q; scanf("%d %d", &n, &q);
	read(a,1,n+1);
	build(1,1,n);
	while(q--) {
		int t, l, r; scanf("%d %d %d", &t, &l, &r);
		if(t == 1) {
			int x; scanf("%d", &x);
			update(1,1,n,l,r,x,1);
		}
		if(t == 2) {
			int x; scanf("%d", &x);
			update(1,1,n,l,r,x,0);
		}
		if(t == 3) {
			printf("%lld\n", query(1,1,n,l,r));
		}
	}
}
