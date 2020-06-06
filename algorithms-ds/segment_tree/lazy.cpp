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

ll nums[maxn], tree[4*maxn];

void build(int node, int l, int r) {
	if(l == r) {
		tree[node] = nums[l];
	}
	else {
		int mid = (l+r) >> 1;
		build(2*node, l, mid);
		build(2*node+1, mid+1, r);

		tree[node] = 0; 
	}
}

void update(int node, int l, int r, int a, int b, int val) {
	if(l > b || r < a) return;
	if(l >= a && r <= b) {
		// db(node);
		tree[node] += 1ll*val;
		return;
	}
	// db(l); db(r);
	// assert(node < 100000);
	int mid = (l+r) >> 1;
	update(2*node, l, mid, a, b, val);
	update(2*node+1, mid+1, r, a, b, val);
}

ll query(int node, int l, int r, int pos) {
	if(l == r) return tree[node];
	int mid = (l+r) >> 1;
	if(pos <= mid) return tree[node] + query(2*node, l, mid, pos);
	else return tree[node] + query(2*node+1, mid+1, r, pos);
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	read(nums,1,n+1);
	build(1,1,n);
	while(q--) {
		int type; scanf("%d", &type);
		if(type == 1) {
			int a, b, u;
			scanf("%d %d %d", &a, &b, &u);
			update(1,1,n,a,b,u);
		}
		else {
			int pos; scanf("%d", &pos);
			printf("%lld\n", query(1,1,n,pos));
		}
	}
}
