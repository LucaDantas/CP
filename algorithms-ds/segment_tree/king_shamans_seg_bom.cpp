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

const int maxn = 2e5+10, inf = 0x3f3f3f3f, maxv = 1e9+10;

int a[maxn], tree[4*maxn], n;

ll bit[maxn];

void upd_bit(int x, int v) {
	for(; x <= n; x += x&-x)
		bit[x] += v;
}

ll query(int x) {
	ll ret = 0;
	for(; x > 0; x -= x&-x)
		ret += bit[x];
	return ret;
}

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = a[i];
		return;
	}
	int m = (i+j) >> 1;
	build(2*node, i, m);
	build(2*node+1, m+1, j);
	tree[node] = max(tree[2*node], tree[2*node+1]);
}

void update(int node, int i, int j, int pos, int v) {
	if(i == j) {
		tree[node] = v;
		return;
	}
	int m = (i+j) >> 1;
	if(pos <= m) update(2*node, i, m, pos, v);
	else update(2*node+1, m+1, j, pos, v);
	tree[node] = max(tree[2*node], tree[2*node+1]);
}

int find(int node, int i, int j, int l, int v) {
	if(j < l) return inf;
	if(tree[node] < v) return inf;
	if(i == j) return i;

	int m = (i+j) >> 1;

	int p1 = find(2*node, i, m, l, v);
	if(p1 == inf) return find(2*node+1, m+1, j, l, v);
	else return p1;
}

int main(){
	int q;
	scanf("%d %d", &n, &q);

	rep(i,1,n+1) scanf("%d", a + i), upd_bit(i, a[i]);
	build(1,1,n);

	while(q--) {
		int p, x;
		scanf("%d %d", &p, &x);
		upd_bit(p, -a[p]);
		upd_bit(p, x);
		update(1,1,n,p,x);
		a[p] = x;

		int prox = 0, ans = -1;

		while(1) {
			ll k = query(prox); if(k > maxv) break;
			prox = find(1,1,n,prox+1,k);
			if(prox == inf) break;
			if(query(prox-1) == a[prox]) {
				ans = prox; break;
			}
		}
		printf("%d\n", ans);
	}
}
