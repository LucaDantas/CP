#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
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

const int maxn = 2e5 + 100;

int a[maxn];

ll tree[4*maxn];
pll lazy[4*maxn]; // first -> first value in the interval / second -> number of additions in that segment
                  // can also be taken as the quocient by which the values increases (razao da PA)

void build(int node, int i, int j) {
	if(i == j) tree[node] = a[i];
	else {
		int m = (i+j) >> 1;
		build(2*node, i, m);
		build(2*node+1, m+1, j);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
}

void flush(int node, int l, int r) {
	if(l != r) { // If it has some children we flush the lazy to them
		int m = (l+r) >> 1;
		lazy[2*node].ff += lazy[node].ff;
		lazy[2*node].ss += lazy[node].ss;
		lazy[2*node+1].ff += lazy[node].ff + lazy[node].ss*(m-l+1); // Adicionamos ao primeiro do
		// segundo grupo o valor do primeiro geral + numero de elementos do primeiro grupo*razao
		lazy[2*node+1].ss += lazy[node].ss;
	}
	// Update the value in the tree and reset the lazy
	int s = r-l+1; // tamanho do intervalo
	tree[node] += 1ll*s*lazy[node].ff + 1ll*s*(s-1)*lazy[node].ss/2;
	lazy[node] = mp(0ll,0ll);
}

void update(int node, int i, int j, int l, int r) {
	flush(node, i, j);
	if(i > r || j < l) return;
	if(i >= l && j <= r) {
		lazy[node].ff += i-l+1;
		lazy[node].ss++;
		flush(node, i, j); // We have to flush it now to update the value in tree[node]
		                   // and for the parent to see it
		return;
	}
	int m = (i+j) >> 1;
	update(2*node, i, m, l, r);
	update(2*node+1, m+1, j, l, r);
	tree[node] = tree[2*node]+tree[2*node+1];
}

ll query(int node, int i, int j, int l, int r) {
	flush(node, i, j);
	if(i > r || j < l) return 0;
	if(i >= l && j <= r) return tree[node];
	int m = (i+j) >> 1;
	return query(2*node, i, m, l, r) + query(2*node+1, m+1, j, l, r);
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	read(a,1,n+1);
	build(1,1,n);
	while(q--) {
		int t, l, r;
		scanf("%d %d %d", &t, &l, &r);
		if(t == 1) {
			update(1,1,n,l,r);
		}
		else {
			printf("%lld\n", query(1,1,n,l,r));
		}
	}
}
