#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,a,b) for(int i=(a); i>=(b); i--)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

// std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int maxn = 2e5+10, maxv = 1e9+10;

int a[maxn], tree[4*maxn];

ll bit[maxn]; // we need long long to save the sums

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = a[i];
		return;
	}
	int m = (i+j) >> 1;
	build(2*node,i,m);
	build(2*node+1,m+1,j);
	tree[node] = max(tree[2*node], tree[2*node+1]);
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		tree[node] = val;
		return;
	}
	int m = (i+j) >> 1;
	if(pos <= m) update(2*node,i,m,pos,val);
	else update(2*node+1,m+1,j,pos,val);
	tree[node] = max(tree[2*node],tree[2*node+1]);
}

bool done;

int get(int node, int i, int j, int val) {
	if(i == j) return i;
	int m = (i+j) >> 1;
	if(tree[2*node] >= val) return get(2*node, i, m, val);
	else return get(2*node+1, m+1, j, val);
}

int busca(int node, int i, int j, int l, int r, int val) {
	if(done || i > r || j < l) return maxv;
	
	if(i >= l && j <= r) {
		if(tree[node] < val) return maxv;
		done = 1;
		return get(node, i, j, val);
	}
	
	int m = (i+j) >> 1;

	int p1 = busca(2*node, i, m, l, r, val);
	int p2 = busca(2*node+1, m+1, j, l, r, val);

	return min(p1, p2);
}

void upd_bit(int x, int v) {
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

ll query(int x) {
	ll ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);

	read(a,1,n+1);

	build(1,1,n); // build seg
	rep(i,1,n+1) upd_bit(i,a[i]); // build bit

	while(q--) {
		int pos, x;
		scanf("%d %d", &pos, &x);

		update(1,1,n,pos,x);

		upd_bit(pos,-a[pos]);
		upd_bit(pos,x);
		a[pos] = x;

		if(!a[1]) {
			puts("1");
			continue;
		}

		int ans = -1;
		pos = 1;
		ll sum = a[1];

		while(sum <= maxv) {
			done = 0;

			int p = busca(1,1,n,pos+1,n,sum);
			if(p == maxv) break;

			if(query(p-1) == a[p]) {
				ans = p; break;
			}

			sum = query(p);
			pos = p;
		}

		printf("%d\n", ans);
	}
}
