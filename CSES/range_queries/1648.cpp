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
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 3e5 + 100;

int a[maxn];
ll tree[4*maxn];

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = a[i];
		return;
	}
	int mid = (i+j) >> 1;
	
	build(2*node, i, mid);
	build(2*node+1, mid+1, j);
	
	tree[node] = tree[2*node] + tree[2*node+1];
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		tree[node] = val;
		a[pos] = val;
		return;
	}
	
	int mid = (i+j) >> 1;
	
	if(pos <= mid)
		update(2*node, i, mid, pos, val);
	else
		update(2*node+1, mid+1, j, pos, val);
		
	tree[node] = tree[2*node] + tree[2*node+1]; 
}

ll query(int node, int i, int j, int l, int r) {
	if(i > r || j < l)
		return 0;
	
	if(i >= l && j <= r)
		return tree[node];
		
	int mid = (i+j) >> 1;
	
	ll left = query(2*node, i, mid, l, r);
	ll right = query(2*node+1, mid+1, j, l, r);
	
	return left + right;
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	
	rep(i,1,n+1)
		scanf("%d", &a[i]);
	
	build(1, 1, n);
	
	rep(i,0,q) {
		int type; scanf("%d", &type);
		if(type == 1) {
			int k, u;
			scanf("%d %d", &k, &u);
			update(1, 1, n, k, u);
		}
		else {
			int x, y;
			scanf("%d %d", &x, &y);
			printf("%lld\n", query(1, 1, n, x, y));
		}
	}
}
